cmake_minimum_required(VERSION 3.6)

add_library(emulator Device.cc Emulator.cc GUI.cc System.cc Video.cc shader_utils.cc)
target_compile_features(emulator PUBLIC cxx_std_17)
target_include_directories(emulator PRIVATE ../third_party/glm 
                                            ../third_party/galogen/generated_files)

target_link_libraries(emulator Boost::program_options)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if(UNIX)
    if(CMAKE_COMPILER_IS_GNUCC AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9)
        message("GCC: Linking to stdc++fs")
        target_link_libraries(emulator PUBLIC stdc++fs) #<filesystem>
    endif()
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        message("Clang: Linking...")
        if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7)
            message("c++experimental")
            target_link_libraries(emulator PUBLIC c++experimental) 
        elseif(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9)
            message("c++fs")
            target_link_libraries(emulator PUBLIC c++fs) 
        endif()
    endif()
endif(UNIX)
