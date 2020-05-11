#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <X11/Xlib.h>
#include <X11/extensions/Xfixes.h>

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

#include "Clipboard.h"
#include <QApplication>
#include <QCloseEvent>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QObject>
#include <QPalette>
#include <QPushButton>
#include <QString>
#include <QWidget>
#include <fstream>
#include <iostream>
#include <memory>

class ClipboardItem : public QWidget {
  Q_OBJECT
public:
  ClipboardItem(QWidget *parent, int width = 200, int height = 100,
                int index = 0, std::string item_data = "",
                bool enable_copy = false);
  // void setItemData(std::string);
  // std::string getItemData();
private:
  // Constant static design parameters
  const static int _PADDING_X = 16;
  const static int _PADDING_Y = 8;
  const static QColor _ODD_BG;
  const static QColor _EVEN_BG;

  int _width, _height, _index;
  std::string _item_data;
  QPushButton *_copy_button;
  QLabel *_item_label;
  bool _enable_copy;
private slots:
  void handleCopyButton();
signals:
  void copyButtonPressed(int);
};

class ClipboardGUI : public QWidget {
  Q_OBJECT
public:
  ClipboardGUI(std::string history_path = "history.txt",
               bool enable_copy = false, QWidget *parent = 0);
  void addClipboardItem(std::string, int);

private:
  int _width, _height;
  QListWidget *_clipboard_list;                  // List widget
  QPushButton *_history_button;                  // Write to history button
  std::vector<ClipboardItem *> _clipboard_items; // ClipboardItem vector
  Clipboard _clipboard;                          // Clipboard object
  std::string _history_path;                     // History text save path
  bool _enable_copy;              // Enable experimental copy flag
  void closeEvent(QCloseEvent *); // Override closeEvent of QWidget

  // Public and private Qt slots, see source file for documentation
public slots:
  void addItem(int);
  void copyItem(int);
private slots:
  void handleHistoryButton();
};

#endif // GRAPHICS_H