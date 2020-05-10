#include "Graphics.h"

int main(int argc, char **argv) {
  std::string help_text = "This program keeps track of clipboard history.\n"
  "It has 2 flags: \nUse `-hp [FILEPATH]` to change history file path.\n"
  "Use `-ec` to enable experimental copy feature (this may not working as intended sometimes).\n";
  std::string history_path = "history.txt";
  bool enable_copy = false;
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
  
  QApplication app(argc, argv);
  std::cout << "History path: " << history_path << std::endl;
  std::cout << "Copy " << (enable_copy ? "enabled" : "disabled") << std::endl;
  ClipboardGUI window(history_path, enable_copy);
  window.show();
  return app.exec();
}