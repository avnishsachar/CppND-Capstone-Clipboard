 # CPPND: Capstone Clipboard Repo

This is my Clipboard repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

In this project, I aim to create an application __for Linux__ which allows to keep track of ClipBoard history for later usage. 
Current state of the program has several features below:
- It can accept 3 command line flags:
```
This program keeps track of clipboard history.
It has 3 flags: 
Use `-h` to print this help message
Use `-hp [FILEPATH]` to change history file path. Default path is `history.txt` in current working directory
Use `-ec` to enable experimental copy feature (this may not working as intended sometimes).
```
- It catches and stores every item copied from any application, and shows it in history. (1 in [Screenshot](#Screenshot))
- It may dump clipboard history to given text file. (2 in [Screenshot](#Screenshot))
- It may append specific item in history to given text file. (3 in [Screenshot](#Screenshot))
- _(Experimental)_ It may copy specific item to clipboard, this may block clipboard sometimes.

## Screenshot

![alt text](resources/sssmall.png "Application screenshot")

## File structure 
```
├── CMakeLists.txt  # CMake file
├── README.md       # Readme file
├── resources 
│   ├── outline_file_copy_black_24dp.png # Copy icon, it is used in experimental copy button
│   ├── outline_save_black_18dp.png      # Save icon, it is used in save item to file button
│   └── sssmall.png # Screenshot of working application
└── src
    ├── Clipboard.h     # Clipboard history logic header
    ├── Clipboard.cpp   # Clipboard history logic source
    ├── Graphics.h      # Clipboard GUI logic header
    ├── Graphics.cpp    # Clipboard GUI logic source
    └── main.cpp        # main argument parser and runner of application
```
## Dependencies for Running Locally
The project aims to run on Linux, hence other platform-specific instructions are omitted. 
* cmake >= 3.5
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * ~Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)~
  * ~Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)~
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * ~Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)~
  * ~Windows: recommend using [MinGW](http://www.mingw.org/)~
* Xlib11
  * Linux: Install `libx11-dev`. For Ubuntu simply use `sudo apt install libx11-dev`
* Qt
  * Linux: Install QT5. For Ubuntu simply use `sudo apt-get -y install qt5-default`
## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./ClipBoardNaive`.

## Rubric

__README (All Rubric Points REQUIRED)__

|DONE | CRITERIA | MEETS SPECIFICATIONS| WHERE |
|-- | -- | --| -- |
| :heavy_check_mark: | A README with instructions is included with the project |The README is included with the project and has instructions for building/running the project. If any additional libraries are needed to run the project, these are indicated with cross-platform installation instructions. You can submit your writeup as markdown or pdf.| |
| :heavy_check_mark: | The README indicates which project is chosen. | The README describes the project you have built. The README also indicates the file and class structure, along with the expected behavior or output of the program. | |
| :heavy_check_mark: | The README includes information about each rubric point addressed. | The README indicates which rubric points are addressed. The README also indicates where in the code (i.e. files and line numbers) that the rubric points are addressed. | |

__Compiling and Testing (All Rubric Points REQUIRED)__

|DONE | CRITERIA | MEETS SPECIFICATIONS| WHERE |
|-- | -- | --| -- |
| :heavy_check_mark: | The submission must compile and run. | The project code must compile and run without errors. We strongly recommend using cmake and make, as provided in the starter repos. If you choose another build system, the code must compile on any reviewer platform. |

__Loops, Functions, I/O__

|DONE | CRITERIA | MEETS SPECIFICATIONS| WHERE |
|-- | -- | --| -- |
| :heavy_check_mark: | The project demonstrates an understanding of C++ functions and control structures.| A variety of control structures are used in the project. The project code is clearly organized into functions.| Every *.cpp file |
| :heavy_check_mark: | The project reads data from a file and process the data, or the program writes data to a file. | The project reads data from an external file or writes data to a file as part of the necessary operation of the program.| `ClipboardGUI::copyItem and `ClipboardGUI::handleHistoryButton` Graphics.cpp  |
| :heavy_check_mark: | The project accepts user input and processes the input.|The project accepts input from a user as part of the necessary operation of the program.|  main.cpp parses command line arguments, also `Graphics accepts mouse clicks |

__Object Oriented Programming__

|DONE | CRITERIA | MEETS SPECIFICATIONS| WHERE |
|-- | -- | --| -- |
| :heavy_check_mark: | The project uses Object Oriented Programming techniques. | The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks. | All *.cpp and *.h files |
| :heavy_check_mark: | Classes use appropriate access specifiers for class members. | All class data members are explicitly specified as public, protected, or private.| All *.cpp and *.h files |
| :heavy_check_mark: | Class constructors utilize member initialization lists. | All class members that are set to argument values are initialized through member initialization lists.| All *.cpp and *.h files |
| :heavy_check_mark: | Classes abstract implementation details from their interfaces. | All class member functions document their effects, either through function names, comments, or formal documentation. Member functions do not change program state in undocumented ways.| All *.cpp and *.h files |
| :heavy_check_mark: | Classes encapsulate behavior. | Appropriate data and functions are grouped into classes. Member data that is subject to an invariant is hidden from the user. State is accessed via member functions.| All *.cpp and *.h files |
| :heavy_check_mark: | Classes follow an appropriate inheritance hierarchy. | Inheritance hierarchies are logical. Composition is used instead of inheritance when appropriate. Abstract classes are composed of pure virtual functions. Override functions are specified.| `ClipboardGUI` is contains `Clipboard` (composition), `ClipboardGUI` inherits `QWidget` and overrides `closeEvent` |
| :heavy_check_mark: | Overloaded functions allow the same function to operate on different parameters. | One function is overloaded with different signatures for the same function name. | Instead of overloading, I used default arguments in constructors, hence same function name may be called with different arguments. |
|  | Derived class functions override virtual base class functions. |One member function in an inherited class overrides a virtual base class member function.| |
|  | Templates generalize functions in the project. | One function is declared with a template that allows it to accept a generic parameter.| |

__Memory Management__

|DONE | CRITERIA | MEETS SPECIFICATIONS| WHERE |
|-- | -- | --| -- |
|  | The project makes use of references in function declarations. | At least two variables are defined as references, or two functions use pass-by-reference in the project code.| |
|  | The project uses destructors appropriately. | At least one class that uses unmanaged dynamically allocated memory, along with any class that otherwise needs to modify state upon the termination of an object, uses a destructor. | |
|  | The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate. | The project follows the Resource Acquisition Is Initialization pattern where appropriate, by allocating objects at compile-time, initializing objects when they are declared, and utilizing scope to ensure their automatic destruction.| |
|  | The project follows the Rule of 5. | For all classes, if any one of the copy constructor, copy assignment operator, move constructor, move assignment operator, and destructor are defined, then all of these functions are defined.| |
|  | The project uses move semantics to move data, instead of copying it, where possible. | For classes with move constructors, the project returns objects of that class by value, and relies on the move constructor, instead of copying the object. | |
|  | The project uses smart pointers instead of raw pointers. | The project uses at least one smart pointer: unique_ptr, shared_ptr, or weak_ptr. The project does not use raw pointers.| |

__Concurrency__

|DONE | CRITERIA | MEETS SPECIFICATIONS| WHERE |
|-- | -- | --| -- |
| :heavy_check_mark: | The project uses multithreading. | The project uses multiple threads in the execution.| `Clipboard` object runs operations in background, see Clipboard.cpp |
|  | A promise and future is used in the project. | A promise and future is used to pass data from a worker thread to a parent thread in the project code.| |
| :heavy_check_mark: | A mutex or lock is used in the project. | A mutex or lock (e.g. std::lock_guard or `std::unique_lock) is used to protect data that is shared across multiple threads in the project code.| `Clipboard` object uses mutex on `_listen` variable, see Clipboard.cpp |
|  | A condition variable is used in the project. | A std::condition_variable is used in the project code to synchronize thread execution.| |

## References

* This great documentation of X11 https://tronche.com/gui/x/xlib/
* Icons : https://material.io/resources/icons
* Qt documentation: https://doc.qt.io/
* Other X11 and Clipboard related issues:  
* https://www.jwz.org/doc/x-cut-and-paste.html
* https://www.freedesktop.org/wiki/Specifications/ClipboardsWiki/
* https://github.com/exebook/x11clipboard
* https://stackoverflow.com/questions/8755471/x11-wait-for-and-get-clipboard-text