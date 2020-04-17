cmake_minimum_required(VERSION 3.6)

add_library(imgui imgui.h imgui.cpp imgui_draw.cpp imgui_widgets.cpp)
target_include_directories(imgui INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
#include_directories(${CMAKE_CURRENT_SOURCE_DIR})
