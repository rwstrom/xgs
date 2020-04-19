cmake_minimum_required(VERSION 3.6)

add_library(emulator Device.cc Emulator.cc System.cc Video.cc)

target_include_directories(emulator PRIVATE ../third_party)



