#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include <QObject>
#undef Bool
#undef CursorShape
#undef Expose
#undef KeyPress
#undef KeyRelease
#undef FocusIn
#undef FocusOut
#undef FontChange
#undef None
#undef Status
#undef Unsorted
#include <algorithm>
#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <X11/Xlib.h>
#include <X11/extensions/Xfixes.h>

class Clipboard : public QObject{
Q_OBJECT
private:
  Display *_x11_display;
  Window _x11_window;
  std::vector<std::string> _history;
  Atom _CLIPBOARD_ATOM, _PROPERTY_ATOM, _UTF8_ATOM, _TARGETS_ATOM, _XA_ATOM, _XA_STRING, _TEXT_ATOM;
  void listenSelectionChange();
  void get_selection();
  void set_selection(std::string);
  void startListening();
  std::vector<std::thread> _threads;
  std::mutex sout_mutex;
  bool _listen;
public:
  Clipboard();
  ~Clipboard();
  std::string getHistoryItem(int);
  void copyFromHistory(int);

signals:
  void itemAdded(int);
};

#endif