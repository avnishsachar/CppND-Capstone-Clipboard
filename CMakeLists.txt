cmake_minimum_required(VERSION 3.5)

project(MyProject)
add_definitions(-std=c++17)
find_package(X11 REQUIRED)

# Widgets finds its own dependencies.
find_package(Qt5Widgets REQUIRED)

if (X11_FOUND)
    include_directories(${X11_INCLUDE_DIR} ${X11_Xfixes_INCLUDE_PATH})
    link_libraries(${X11_LIBRARIES} ${X11_Xfixes_LIB})
endif(X11_FOUND)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

file(GLOB project_SRCS src/*.h src/*.cpp)

add_executable(ClipBoardNaive ${project_SRCS})

qt5_use_modules(ClipBoardNaive Widgets)
