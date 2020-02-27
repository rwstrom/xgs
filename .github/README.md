
XGS-rws ![Ubuntu/OSX Build CI](https://github.com/rwstrom/xgs/workflows/Ubuntu/OSX%20Build%20CI/badge.svg)
===

This is a fork of [XGS ](https://github.com/jmthompson/xgs). A Linux-based Apple IIGS emulator.


# About This Version

Changes have been made so it compiles on windows, linux, and macOSX 10.15.

# Compiling

To compile this code you will need

- CMake
- c++17 capable compiler
- The Boost format and program_options libraries
- SDL2
- SDL2_ttf

To build XGS, from the source directory run:

```
mkdir build
cd build
cmake ..
make 
```

The binary will be compiled to build/xgs.

# Usage

Before starting XGS for the first time you'll need to create the XGS home directory
and copy some files into it.

First, from the source directory run:

```
mkdir ~/.xgs
cp fonts/xgs{4,8}0.fnt ~/.xgs/
```

You'll need an Apple IIGS ROM file (either v01 or v03 will work):

```
cp PATH_TO_YOUR_ROM_FILE ~/.xgs/xgs.rom
```

Now you can start XGS as follows (-3 is only needed if your ROM image is v03):

```
./build/xgs -3
```

You can also display the help text if you need help with the command-line options:

```
./build/xgs --help
```

# Status
It runs on windows 10 but I have yet to try it on other platforms.

Currently the emulator successfully boots to an AppleSoft prompt.

This code will be very much in flux for the next few months as I continue to
debug, improve, and streamline the code base.

