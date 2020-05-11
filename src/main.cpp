#include "Graphics.h"

int main(int argc, char **argv) {
  std::string help_text =
      "This program keeps track of clipboard history.\n"
      "It has 3 flags: \nUse `-h` to print this help message\n"
      "Use `-hp [FILEPATH]` to change history file path. Default path is "
      "`history.txt` in current working directory\n"
      "Use `-ec` to enable experimental copy feature (this may not working as "
      "intended sometimes).\n";
  std::string history_path = "history.txt";
  bool enable_copy = false;

  // Parse arguments
  for (int i = 1; i < argc; i++) {
    if (std::string(argv[i]) == "-h") {
      std::cout << help_text;
      exit(0);
    } else if (std::string(argv[i]) == "-hp" && (i + 1) < argc) {
      history_path = std::string(argv[++i]);
    } else if (std::string(argv[i]) == "-ec") {
      enable_copy = true;
    } else {
      std::cout << help_text;
      exit(0);
    }
  }

  // Run application
  QApplication app(argc, argv);
  std::cout << "History path: " << history_path << std::endl;
  std::cout << "Copy " << (enable_copy ? "enabled" : "disabled") << std::endl;
  ClipboardGUI window(history_path, enable_copy);
  window.show();
  return app.exec();
}