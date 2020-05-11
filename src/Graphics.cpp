#include "Graphics.h"

ClipboardGUI::ClipboardGUI(std::string history_path, bool enable_copy,
                           QWidget *parent)
    : QWidget(parent), _width(300), _height(500), _history_path(history_path),
      _enable_copy(enable_copy) {
  /*
   * Builds GUI of ClipBoardNaive application
   *
   * history_path : path to file to write clipboard history.
   * enable_copy : Enable experimental copy feature.
   */

  // Set size of the window
  setFixedSize(_width, _height);

  // Create write history button
  _history_button = new QPushButton("Write history to file", this);
  int _button_padding = 16;
  int _button_width = _width - 2 * _button_padding;
  int _button_height = 48;
  _history_button->setGeometry(16, _button_padding, _button_width,
                               _button_height);
  connect(_history_button, SIGNAL(pressed()), this,
          SLOT(handleHistoryButton()));

  // Create ListView
  _clipboard_list = new QListWidget(this);
  _clipboard_list->setUniformItemSizes(true);
  int list_x = 0;
  int list_y = 2 * _button_padding + _button_height;
  int list_width = _width - list_x;
  int list_height = _height - list_y;
  _clipboard_list->setGeometry(list_x, list_y, list_width, list_height);
  _clipboard;
  connect(&_clipboard, &Clipboard::itemAdded, this, &ClipboardGUI::addItem);
};

void ClipboardGUI::addItem(int x) {
  /*
   * Add item to ClipboardGUI, this catches itemAdded signal of Clipboard
   */
  addClipboardItem(_clipboard.getHistoryItem(x), x);
}

void ClipboardGUI::copyItem(int x) {
  /*
   * Copy (Experimental) or save (append to history file) item in given index
   */
  if (_enable_copy) {
    _clipboard.copyFromHistory(x);
  } else {
    std::ofstream outfile(_history_path, std::ios_base::app);
    outfile << "Item at index " << std::to_string(x) << ":" << std::endl;
    outfile << _clipboard.getHistoryItem(x) << std::endl
            << "*-*-*-*-*-*-*-*-*-*" << std::endl;
    outfile.close();
  }
}

void ClipboardGUI::handleHistoryButton() {
  /*
   * Writes history to file, this catches pressed() signal of _history_button
   */
  std::ofstream outfile(_history_path);
  for (int i = 0; i < _clipboard_items.size(); i++) {
    outfile << _clipboard.getHistoryItem(i) << std::endl;
  }
  outfile.close();
}
void ClipboardGUI::addClipboardItem(std::string item_data, int index) {
  /*
   * Add Clipboard item to GUI
   */
  ClipboardItem *item =
      new ClipboardItem(this, _width, 64, index, item_data, _enable_copy);
  _clipboard_items.push_back(item);
  QListWidgetItem *item_widget = new QListWidgetItem(_clipboard_list);
  item_widget->setSizeHint(item->size());
  _clipboard_list->addItem(item_widget);
  _clipboard_list->setItemWidget(item_widget, item);
  connect(item, &ClipboardItem::copyButtonPressed, this,
          &ClipboardGUI::copyItem);
};

void ClipboardGUI::closeEvent(QCloseEvent *evt) {
  /*
   * Overrides closeEvent and forces program to exit
   */
  std::cout.flush();
  std::cout << "Closing\n";
  evt->accept();
  exit(0);
}

// Background colors of items
const QColor ClipboardItem::_ODD_BG = QColor("#b3e5fc");
const QColor ClipboardItem::_EVEN_BG = QColor("#e6ffff");

ClipboardItem::ClipboardItem(QWidget *parent, int width, int height, int index,
                             std::string item_data, bool enable_copy)
    : QWidget(parent), _width(width), _height(height), _index(index),
      _item_data(item_data), _enable_copy(enable_copy) {
  /*
   * Builds and binds new Clipboard item
   *
   * width : Item width
   * height : Item height
   * index : Clipboard history index
   * item_data : Clipboard item text
   * enable_copy : Enable experimental copy instead of  save feature
   */

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

  // Set text of Clipboard item
  _item_label = new QLabel(this);
  _item_label->setText(QString(_item_data.c_str()));
  _item_label->setGeometry(_PADDING_X, _PADDING_Y, label_width,
                           _height - 2 * _PADDING_Y);

  _copy_button = new QPushButton("", this);
  _copy_button->setGeometry(label_width + 2 * _PADDING_X,
                            (_height - button_height) / 2, button_width,
                            button_height);
  if (_enable_copy) {
    _copy_button->setIcon(QIcon("../resources/outline_file_copy_black_24dp"));
  } else {
    _copy_button->setIcon(QIcon("../resources/outline_save_black_18dp.png"));
  }
  connect(_copy_button, SIGNAL(pressed()), this, SLOT(handleCopyButton()));
};

void ClipboardItem::handleCopyButton() {
  /*
   * Catch save or copy button press and take action for this item.
   */

  emit copyButtonPressed(_index);
}
