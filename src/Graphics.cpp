#include "Graphics.h"

ClipboardGUI::ClipboardGUI(QWidget *parent)
    : QWidget(parent), _width(300), _height(500) {
  // Set size of the window
  setFixedSize(_width, _height);  

  // Create ListView
  _clipboard_list = new QListWidget(this);
  _clipboard_list->setUniformItemSizes(true);
  _clipboard_list->setGeometry(0, 0, _width, _height);
  
  for (int i = 0; i < 3;) {
    ClipboardItem* item = new ClipboardItem(this, _width, 64, i++, "Deneme " + std::to_string(i));
    addClipboardItem(item);
  }
};

void ClipboardGUI::addClipboardItem(ClipboardItem*& item) {
    QListWidgetItem* item_widget = new QListWidgetItem(_clipboard_list);
    item_widget->setSizeHint(item->size());
    _clipboard_list->addItem(item_widget);
    _clipboard_list->setItemWidget(item_widget, item);
};

const QColor ClipboardItem::_ODD_BG = QColor("#b3e5fc");
const QColor ClipboardItem::_EVEN_BG = QColor("#e6ffff");

ClipboardItem::ClipboardItem(QWidget* parent, int width, int height, int index,
                             std::string item_data)
    : QWidget(parent), _width(width), _height(height), _index(index),
      _item_data(item_data) {
  // Set size
  setFixedSize(_width, _height);
  
  // Set backgroud color
  QPalette pal = palette();
  // set black background
  pal.setColor(QPalette::Base, _index % 2 == 0 ? _EVEN_BG : _ODD_BG);
  this->setAutoFillBackground(true);
  this->setPalette(pal);
  
  int button_width = 28;
  int button_height = 28;
  int label_width = _width - button_width - 3 * _PADDING_X;
  
  _item_label = new QLabel(this);
  _item_label->setText(QString(_item_data.c_str()));
  _item_label->setGeometry(_PADDING_X, _PADDING_Y, label_width, _height - 2 * _PADDING_Y);

  _copy_button = new QPushButton("", this);
  _copy_button->setGeometry(label_width + 2 * _PADDING_X, (_height - button_height) / 2, button_width, button_height);
  _copy_button->setIcon(QIcon("../resources/outline_file_copy_black_24dp"));
};
