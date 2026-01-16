# TL16C2550
Serial Drivers for Commander X16 devices using the TL16C2550 and Compatible UARTS

## Overview
This library provides serial communication support for the Commander X16 computer using the TL16C2550 dual UART chip. It is designed to be compiled with the cc65 cross-compiler toolchain.

## Building

### Prerequisites
- cc65 cross-compiler toolchain installed and in PATH
- Make utility

### Compilation
To build the library:
```bash
make
```

This will:
- Compile all C source files in `src/` to object files
- Assemble all assembly source files in `src/` to object files
- Create a library archive `build/libtl16c2550.a`
- Copy all header files from `include/` to `build/`

### Output
After building, you will find:
- `build/libtl16c2550.a` - The compiled library
- `build/tl16c2550.h` - C header file
- `build/tl16c2550.inc` - Assembly include file
- `build/*.o` - Individual object files

### Cleaning
To remove all build artifacts:
```bash
make clean
```

## Usage
To use this library in your Commander X16 project:

1. Include the header file in your C code:
```c
#include "tl16c2550.h"
```

2. Link against the library when building your project:
```bash
cl65 -t cx16 -o myprogram.prg myprogram.c -L./build -ltl16c2550
```

## API
See `include/tl16c2550.h` for the complete API documentation.
