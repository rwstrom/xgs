cmake_minimum_required(VERSION 3.6)

add_library(debugger Debugger.cc)
target_compile_features(debugger PUBLIC cxx_std_17)
target_include_directories(debugger PRIVATE ${Boost_INCLUDE_DIR})
