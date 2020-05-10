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
  // X11 connection variables
  Display *_x11_display;
  Window _x11_window;
  std::vector<std::string> _history; // Clipboard history vector
  // X11 Atoms
  Atom _CLIPBOARD_ATOM, _PROPERTY_ATOM, _UTF8_ATOM, _TARGETS_ATOM, _XA_ATOM, _XA_STRING, _TEXT_ATOM;
  // Private methods see source file for documentation
  void listenSelectionChange();
  void get_selection();
  void set_selection(std::string);
  void startListening();
  // Background threads
  std::vector<std::thread> _threads;
  std::mutex sout_mutex; // Listen variable mutex
  bool _listen; // Listen changes variable
public:
  Clipboard();
  ~Clipboard();
  // Public methods see source file for documentation
  std::string getHistoryItem(int);
  void copyFromHistory(int);

signals:
  void itemAdded(int);
};

#endif