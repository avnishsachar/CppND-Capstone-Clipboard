// #include "Clipboard.h"

// int main()
// {
//   std::cout << "Started your awesome Clipboard Manager\n";
//   Clipboard cb;
//   return 0;
// }
#include "Graphics.h"
#include <QApplication>
int main(int argc, char **argv) {
  QApplication app(argc, argv);

  ClipboardGUI window;
  //  QWidget window;
  //  window.setFixedSize(100, 50);

  //  QPushButton *button = new QPushButton("Hello World", &window);
  //  button->setGeometry(10, 10, 80, 30);

  window.show();
  return app.exec();
}