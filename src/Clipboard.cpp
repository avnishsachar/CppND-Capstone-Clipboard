#include "Clipboard.h"
#include <assert.h>
#include <limits.h>

Clipboard::Clipboard() {
  /*
   * Initialize X11 related objects and starts listening selection change
   */
  _x11_display = XOpenDisplay(NULL);
  unsigned long color = BlackPixel(_x11_display, DefaultScreen(_x11_display));
  _x11_window =
      XCreateSimpleWindow(_x11_display, DefaultRootWindow(_x11_display), 0, 0,
                          1, 1, 0, color, color);
  _CLIPBOARD_ATOM = XInternAtom(_x11_display, "CLIPBOARD", False);
  _PROPERTY_ATOM = XInternAtom(_x11_display, "XSEL_DATA", False);
  _UTF8_ATOM = XInternAtom(_x11_display, "UTF8_STRING", False);
  _TARGETS_ATOM = XInternAtom(_x11_display, "TARGETS", False);
  _TEXT_ATOM = XInternAtom(_x11_display, "TEXT", 0);
  _XA_ATOM = 4;
  _XA_STRING = 31;
  _listen = true;
  _threads.emplace_back(std::thread(&Clipboard::listenSelectionChange, this));
}

std::string Clipboard::getHistoryItem(int i) {
  // Safely returns item from _history vector
  return i < _history.size() ? _history[i] : "";
}

void Clipboard::get_selection() {
  /*
   * Reads text from new X11 selection, i.e. catches recently copied text.
   */
  unsigned long ressize, restail;
  int resbits;
  XEvent event;
  XConvertSelection(_x11_display, _CLIPBOARD_ATOM, _UTF8_ATOM, _PROPERTY_ATOM,
                    _x11_window, CurrentTime);
  while (true) {
    XNextEvent(_x11_display, &event);
    if (event.type == SelectionNotify &&
        event.xselection.selection == _CLIPBOARD_ATOM) {
      if (event.xselection.property) {
        char *result;
        XGetWindowProperty(_x11_display, _x11_window, _PROPERTY_ATOM, 0,
                           LONG_MAX / 4, False, AnyPropertyType, &_UTF8_ATOM,
                           &resbits, &ressize, &restail,
                           (unsigned char **)&result);
        _history.emplace_back(result);
        // std::lock_guard<std::mutex> uLock(sout_mutex);
        std::cout << _history.size() << " - " << result << "\n-------------\n";
        emit itemAdded(_history.size() - 1);
        XFree(result);
      }
      break;
    }
  }
}

void Clipboard::set_selection(std::string text) {
  /*
   * (Experimental) Set text to X11 selection, may block selection requests
   */
  sout_mutex.lock();
  _listen = false;
  sout_mutex.unlock();
  int size = text.size() + 1;
  XEvent event;
  XSetSelectionOwner(_x11_display, _CLIPBOARD_ATOM, _x11_window, 0);
  if (XGetSelectionOwner(_x11_display, _CLIPBOARD_ATOM) != _x11_window) {
    sout_mutex.lock();
    _listen = true;
    sout_mutex.unlock();
    return;
  }
  while (true) {
    XNextEvent(_x11_display, &event);
    std::cout << "Got event\n";
    switch (event.type) {
    case SelectionRequest: {
      if (event.xselectionrequest.selection != _CLIPBOARD_ATOM)
        break;
      XSelectionRequestEvent *xsr = &event.xselectionrequest;
      XSelectionEvent ev = {0};
      int R = 0;
      ev.type = SelectionNotify, ev.display = xsr->display,
      ev.requestor = xsr->requestor, ev.selection = xsr->selection,
      ev.time = xsr->time, ev.target = xsr->target, ev.property = xsr->property;
      if (ev.target == _TARGETS_ATOM) {
        std::cout << "Targets requested\n";
        R = XChangeProperty(ev.display, ev.requestor, ev.property, _XA_ATOM, 32,
                            PropModeReplace, (unsigned char *)&_XA_STRING, 1);
      } else if (ev.target == _XA_STRING || ev.target == _TEXT_ATOM) {
        std::cout << "String or Text requested\n";
        R = XChangeProperty(
            ev.display, ev.requestor, ev.property, _XA_STRING, 8,
            PropModeReplace,
            reinterpret_cast<unsigned char *>(const_cast<char *>(text.c_str())),
            size);
      } else if (ev.target == _UTF8_ATOM) {
        std::cout << "UTF8 requested\n";
        R = XChangeProperty(
            ev.display, ev.requestor, ev.property, _UTF8_ATOM, 8,
            PropModeReplace,
            reinterpret_cast<unsigned char *>(const_cast<char *>(text.c_str())),
            size);
      } else {
        std::cout << "No match\n";
        ev.property = None;
      }
      if ((R & 2) == 0) {
        std::cout << "Sending event, ";
        XSendEvent(_x11_display, ev.requestor, 0, 0, (XEvent *)&ev);
        std::cout << "Sended event\n";
      }
      std::cout << "Breaking the SelectionRequestCase\n-------------\n";
      break;
    }
    case SelectionClear: {
      std::cout << "SelectionClear requested\n-------------\n";
      sout_mutex.lock();
      _listen = true;
      sout_mutex.unlock();
      return;
    }
    }
  }
}

void Clipboard::copyFromHistory(int i) {
  /*
   * Copies item in history to X11 selection
   */
  std::cout << "Will copy : " << (i < _history.size() ? _history[i] : "")
            << "\n-------------\n";
  _threads.emplace_back(std::thread(&Clipboard::set_selection, this,
                                    (i < _history.size() ? _history[i] : "")));
}

void Clipboard::listenSelectionChange() {
  /*
   * Listens X11 SelectionOwner change via XFixes extension, and triggers
   * get_selection on change.
   */
  int event_base, error_base;
  XEvent on_change_event;

  assert(XFixesQueryExtension(_x11_display, &event_base, &error_base));
  XFixesSelectSelectionInput(_x11_display, DefaultRootWindow(_x11_display),
                             _CLIPBOARD_ATOM,
                             XFixesSetSelectionOwnerNotifyMask);

  while (true) {
    if (_listen) {
      XNextEvent(_x11_display, &on_change_event);
      Window owner = XGetSelectionOwner(_x11_display, _CLIPBOARD_ATOM);
      if (on_change_event.type == event_base + XFixesSelectionNotify &&
          ((XFixesSelectionNotifyEvent *)&on_change_event)->selection ==
              _CLIPBOARD_ATOM) {
        get_selection();
      }
    }
  }
}

Clipboard::~Clipboard() {
  /*
   * Joins background threads and destroys X11 connection
   */
  std::for_each(_threads.begin(), _threads.end(),
                [](std::thread &t) { t.join(); });
  XDestroyWindow(_x11_display, _x11_window);
  XCloseDisplay(_x11_display);
}
