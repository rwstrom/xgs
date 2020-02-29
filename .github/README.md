
XGS-rws ![Ubuntu/macOSX Build](https://github.com/rwstrom/xgs/workflows/Ubuntu/macOSX%20Build/badge.svg)
===

This is a fork of [XGS ](https://github.com/jmthompson/xgs), a Linux-based Apple IIGS emulator.


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
**On mac/linux:**

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
**On Windows:**

```
Copy all the dll files from your SDL2/lib/x64 folder and 
all the fonts from the xgs/font folder and 
your xgs.rom file into the same folder as the xgs.exe 
then double click on the exe.
```
# Status

| OS  | Windows 10 | Ubuntu | OSX 10.15 |
| --- |     ---    |  ---   |   ---     |
| Builds 64-bit | Yes     | Yes    | Yes |
| Builds 32-bit | Untested | Untested | Untested |

Running emulator using 'Apple IIgs Dealer Diagnostics_v3.0.po' on Windows. 

| Test | Result | Notes |
| ---  | ---    |  ---  |
| ROM  | Fail |       |
| Speed/Interrupt| Fail | Program hangs.|
| MMU/IOU | Fail | Program crash.|
| Main RAM | Fail | |
| Expansion RAM | Fail| |
| Clock Ram | Fail| |
| Serial Port internal| Fail| Unimplemented feature |
| Serial Port crystal | Fail| Unimplemented feature |
| Sound circuitry | Pass  | |
| Sound speaker tone | Pass | |
| **Video pattern:** | | |
| Color bar | Pass | |
| Character generator| Fail | Prodos pathname error |
| 80/40 column | Pass | |
| Low resolution graphics| Pass| |
| High resolution graphics| Pass | |
| Double High resoulution | Fail | |
| Super High Resolution | Pass | |
| Screen/Text colors | Pass | |
| **Keyboard/Mouse:**| | |
| ADB keyboard| Fail | Prodos Error #80 |
| Standard IIe keyboard | Fail| Prodos Error #80 |
| Extended IIe keyboard | Fail | Prodos Error #80 |
| Numeric keypad IIe | Fail | Prodos Error #80 |
| ADB mouse | Pass | |
| Joystick/Paddle | Pass | Button press only | 
