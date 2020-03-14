cmake_minimum_required(VERSION 3.6)



#This needs to come before project command
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "Minimum OS X deployment version")

project(xgs VERSION 0.60)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#Set C++ standard globally
set(CMAKE_CXX_STANDARD 17)
#Don't rely on compiler specific extensions.
set( CMAKE_CXX_EXTENSIONS OFF )

add_executable(xgs emulator/main.cc)

add_definitions(-DVERSION_MAJOR=${xgs_VERSION_MAJOR} 
                -DVERSION_MINOR=${xgs_VERSION_MINOR}
                -DENABLE_DEBUGGER )

if(MSVC)
    add_definitions(/W4)
else()
    add_definitions(-Wall)
endif()
                
# Test endianness of the target system
INCLUDE (${CMAKE_ROOT}/Modules/TestBigEndian.cmake)

TEST_BIG_ENDIAN(WORDS_BIGENDIAN)
if(WORDS_BIGENDIAN)
    add_definitions(-DBIGENDIAN)
endif()

# Check for Raspberry Pi
if(BCMHOST)
    add_definitions(-DRPI)
    include_directories(/opt/vc/include)
    target_link_libraries(xgs
        /opt/vc/lib/libbcm_host.so
        /opt/vc/lib/libbrcmGLESv2.so
        /opt/vc/lib/libbrcmEGL.so
    )
else()
    set(OpenGL_GL_PREFERENCE GLVND) #needed for some linux systems
    find_package(OpenGL REQUIRED)
endif()

# Boost setup
option(Boost_USE_STATIC_LIBS "Use boost static libs" OFF) 
option(Boost_USE_STATIC_RUNTIME "Use boost static runtime" OFF)
set(Boost_USE_MULTITHREADED ON)

find_package(Boost 1.60.0 REQUIRED COMPONENTS program_options)


option(USING_VCPKG_SDL "SDL dependencies installed by vcpkg" OFF)
if(USING_VCPKG_SDL)
    find_package(SDL2 CONFIG REQUIRED)
    find_package(sdl2-ttf CONFIG REQUIRED)
    target_link_libraries(xgs SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_ttf)
    get_target_property(SDL2_INCLUDE_DIRS SDL2::SDL2 INTERFACE_INCLUDE_DIRECTORIES)
else()
    find_package(SDL2 REQUIRED)
endif()

include_directories(${PROJECT_SOURCE_DIR} 
                    ${SDL2_INCLUDE_DIRS} 
                    ${Boost_INCLUDE_DIR})

add_subdirectory(adb)
add_subdirectory(debugger)
add_subdirectory(disks)
add_subdirectory(doc)
add_subdirectory(emulator)
add_subdirectory(M65816)
add_subdirectory(mega2)
add_subdirectory(vgc)

add_subdirectory(third_party/galogen)
add_subdirectory(imgui)

target_link_libraries(xgs   emulator #gcc needs this to be first
                            adb
                            debugger 
                            doc 
                            disks  
                            M65816 
                            mega2 
                            vgc 
                            imgui 
                            gl_extension_loader 
                            ${Boost_LIBRARIES} 
                            ${SDL2_LIBRARIES})

#additional linking needed for std::filesystem with clang and gcc
if(UNIX)
    if(CMAKE_COMPILER_IS_GNUCC AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9)
        message("GCC: Linking to stdc++fs")
        target_link_libraries(xgs stdc++fs) 
    endif()
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7)
            message("Clang: linking to c++experimental")
            target_link_libraries(xgs c++experimental) 
        elseif(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9)
            message("Clang: linking to c++fs")
            target_link_libraries(xgs c++fs) 
        endif()
    endif()
endif(UNIX)

