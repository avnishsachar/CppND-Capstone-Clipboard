#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include <X11/Xlib.h>
#include <X11/extensions/Xfixes.h>
#include <algorithm>
#include <condition_variable>
#include <deque>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class Clipboard {
private:
  Display *_x11_display;
  Window _x11_window;
  std::vector<std::string> _history;
  Atom _CLIPBOARD_ATOM, _PROPERTY_ATOM, _UTF8_ATOM;
  void listenSelectionChange();
  void get_selection();
  std::vector<std::thread> _threads;

public:
  Clipboard();
  ~Clipboard();
};

#endif