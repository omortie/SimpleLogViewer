cmake_minimum_required(VERSION 3.19)
project(LogViewer)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 20)

add_executable(LogViewer main.cpp logviewer.cpp)
target_link_libraries(LogViewer Qt5::Core Qt5::Widgets)
