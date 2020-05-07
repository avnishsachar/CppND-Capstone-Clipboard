#include "Clipboard.h"
#include <assert.h>
#include <limits.h>

Clipboard::Clipboard() {
  _x11_display = XOpenDisplay(NULL);
  unsigned long color = BlackPixel(_x11_display, DefaultScreen(_x11_display));
  _x11_window =
      XCreateSimpleWindow(_x11_display, DefaultRootWindow(_x11_display), 0, 0,
                          1, 1, 0, color, color);
  _CLIPBOARD_ATOM = XInternAtom(_x11_display, "CLIPBOARD", False);
  _PROPERTY_ATOM = XInternAtom(_x11_display, "XSEL_DATA", False);
  _UTF8_ATOM = XInternAtom(_x11_display, "UTF8_STRING", False);
  _threads.emplace_back(std::thread(&Clipboard::listenSelectionChange, this));
}

void Clipboard::get_selection() {
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
        std::cout << _history.size() << " - " << result << "\n-------------"
                  << std::endl;
        XFree(result);
      }
      break;
    }
  }
}

Clipboard::~Clipboard() {
  // TODO: Try to trigger
  // std::cout << "Printing history before exit\n";
  // for (auto e : _history) {
  //   std::cout << e << std::endl;
  // }
  std::for_each(_threads.begin(), _threads.end(),
                [](std::thread &t) { t.join(); });
  XDestroyWindow(_x11_display, _x11_window);
  XCloseDisplay(_x11_display);
}

void Clipboard::listenSelectionChange() {
  int event_base, error_base;
  XEvent on_change_event;

  assert(XFixesQueryExtension(_x11_display, &event_base, &error_base));
  XFixesSelectSelectionInput(_x11_display, DefaultRootWindow(_x11_display),
                             _CLIPBOARD_ATOM,
                             XFixesSetSelectionOwnerNotifyMask);

  while (true) {
    XNextEvent(_x11_display, &on_change_event);

    if (on_change_event.type == event_base + XFixesSelectionNotify &&
        ((XFixesSelectionNotifyEvent *)&on_change_event)->selection ==
            _CLIPBOARD_ATOM) {
      get_selection();
    }
  }
}
