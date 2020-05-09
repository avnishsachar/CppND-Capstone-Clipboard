#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QString>
#include <QWidget>
#include <QPalette>

class ClipboardItem : public QWidget {
public:
  ClipboardItem(QWidget *parent, int width = 200, int height = 100,
                int index = 0, std::string item_data = "");
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
  // QPushButton* _delete_button;
};

class ClipboardGUI : public QWidget {
public:
  ClipboardGUI(QWidget *parent = 0);
  void addClipboardItem(ClipboardItem *&);

private:
  int _width, _height;
  QListWidget *_clipboard_list;
};

#endif // GRAPHICS_H