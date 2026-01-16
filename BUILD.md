# Build System Documentation

## Overview

This project uses the cc65 compiler suite to build a library for 6502-based systems like the Commander X16.

## Build Process

The build process follows these steps:

1. **Compile C to Assembly**: C source files (`.c`) are compiled to assembly (`.s`) using `cc65`
2. **Assemble to Object**: Assembly files (`.s`) are assembled to object files (`.o`) using `ca65`
3. **Create Library**: Object files (`.o`) are archived into a library (`.lib`) using `ar65`

### Detailed Steps

```
src/tl16c2550.c  --[cc65]-->  obj/tl16c2550.s  --[ca65]-->  obj/tl16c2550.o  --[ar65]-->  lib/tl16c2550.lib
```

## Makefile Targets

- **all** (default): Builds the library
- **clean**: Removes object files and intermediate assembly files
- **distclean**: Removes all generated files and directories
- **install**: Copies library and headers to a distribution directory
- **help**: Shows available targets and usage examples

## Makefile Variables

- **TARGET**: Target platform (default: `cx16` for Commander X16)
  - Other options: `c64` (C64), `c128` (C128), `apple2`, `atari`, `nes`, etc.
- **INSTALL_DIR**: Installation directory (default: `dist`)

## Directory Structure

```
TL16C2550/
├── src/              # Source files (.c, .s)
├── include/          # Public header files (.h)
├── obj/              # Generated object files (.o) and assembly (.s)
├── lib/              # Generated library (.lib)
├── dist/             # Installation directory (created by 'make install')
│   ├── lib/          # Installed library
│   └── include/      # Installed headers
└── Makefile          # Build configuration
```

## Using the Library in Your Project

After building and installing the library:

```bash
# Build the library
make

# Install to dist/
make install
```

To use in your project:

```c
#include "tl16c2550.h"

int main(void) {
    uart_init();
    uart_putc('A');
    return 0;
}
```

Compile and link:

```bash
cc65 -t cx16 -I dist/include -o myprogram.s myprogram.c
ca65 -t cx16 -o myprogram.o myprogram.s
ld65 -t cx16 -o myprogram.prg myprogram.o dist/lib/tl16c2550.lib cx16.lib
```

## Cross-Platform Builds

To build for different targets:

```bash
# Commander X16 (default)
make

# Commodore 64
make TARGET=c64

# Apple II
make TARGET=apple2

# Clean and rebuild for different target
make clean
make TARGET=c128
```

## Development Workflow

1. Edit source files in `src/` or headers in `include/`
2. Run `make` to rebuild the library
3. Test your changes
4. Run `make clean` to clean up build artifacts
5. Run `make install` to prepare distribution

## Dependencies

- cc65 compiler suite (cc65, ca65, ar65, ld65)
- GNU Make or compatible
- Standard UNIX tools (mkdir, rm, cp)
