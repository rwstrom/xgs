
XGS-rws ![Build](https://github.com/rwstrom/xgs/workflows/Build/badge.svg)
===

This is a fork of jmthompson's [XGS ](https://github.com/jmthompson/xgs) Apple IIGS emulator project.


# About This Version

Changes have been made so it compiles on windows, linux, and macOSX 10.15.

# ROMS

ROM versions 1 at 3 are supported.

The ROM is considered Apple copyrighted material and is not supplied here.
You can create your own or search the internet. [Here's one place you can look.](ftp://public.asimov.net/pub/apple_II/emulators/rom_images/)

# Binaries
Github Actions produces linux/macos/windows binaries when changes are made to the XGS-rws branch. 
These are for testing purposes only. 

Click on the [Actions](https://github.com/rwstrom/xgs/actions?query=branch%3AXGS-rws) tab above. 

From the 'Actions' page click on one of the workflows created by XGS-rws branch.

The artifacts section should contain zips for each platform.

After unzipping drop a copy of your rom file into the folder and click on the executable.

Note: linux/macos platforms will need sdl2 and boost installed.
Note: The default ROM file name is xgs.rom

Run xgs-rws --help for a list of options.

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
cmake --build . 
```
On linux/macos:
    The binary will be compiled to build/xgs.
On windows:
    The binary will be in build/Debug or build/Release
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

```
./build/xgs
```

You can also display the help text if you need help with the command-line options:

```
./build/xgs-rws --help
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
| Runs 64-bit | Yes | Untested | Untested |
| Runs 32-bit | Untested | Untested | Untested |

Running emulator on Windows using 'GS Diagnostics 3.1.2mg' . 

| Test | Result | Notes |
| ---  | ---    |  ---  |
| ROM  | Fail |      |
| Speed/Interrupt| Fail | |
| MMU/IOU | Pass | |
| Main RAM | Pass | |
| Expansion RAM | Pass| |
| Clock Ram | Fail| |
| Serial Port internal| Fail| Unimplemented feature |
| Serial Port crystal | Fail| Unimplemented feature |
| Sound circuitry | Pass  | |
| Sound speaker tone | Pass | |
| **Video pattern:** | | |
| Color bar | Pass | |
| Character generator| Pass |  |
| 80/40 column | Pass | |
| Low resolution graphics| Pass| |
| High resolution graphics| Pass | |
| Double High resoulution | Pass | Seems to have extra lines |
| Super High Resolution | Pass | |
| Screen/Text colors | Pass | |
| **Keyboard/Mouse:**| | |
| ADB keyboard| Fail | Unable to press clear key on keypad  |
| Standard IIe keyboard | Pass|  |
| Extended IIe keyboard | Fail | Unable to press clear key on keypad|
| Numeric keypad IIe | Fail |  Unable to press print key|
| ADB mouse | Pass | |
| Joystick/Paddle | Pass | Button press only | 
