# TL16C2550
Serial Drivers for Commander X16 devices using the TL16C2550 and Compatible UARTS

## ⚠️ Work in Progress
This project is currently under active development with significant functionality still to be implemented. The API is not yet stable and may change.

## Overview
This library provides serial communication support for the Commander X16 computer using the TL16C2550 dual UART chip. It is designed to be compiled with the cc65 cross-compiler toolchain.   It does not currently integrate with the built in serial functions in cc65.   There is not currently an integration for serial on the cx16 target.   I'm not activly looking into integrating because the x16 does not have dedicated serial and the exisiting serial in cc65 does not apeare to be flexable enough (I could be wrong and may look into this later).   This is targeting the TL16c2550 Uart, but is compatible with others.   This is the UART in use by the Texelec Serail/ESP32 card and midi card.

## Current Status
Currently implemented:
- **Data Structures**: UART_Instance struct with full field definitions
- **UART Creation**:
  - `createUART()` - Public wrapper function that calculates divisor from baud rate
  - `createUARTWithDivisor()` - Internal function for creating UART with explicit divisor
  - `findDivisor()` - Calculates baud rate divisor from crystal clock and desired rate
- **Device Discovery**: `scanUARTs()` - Detects UART devices at known addresses
- **Global Management**:
  - `uart_instances[]` - Global array for storing up to 20 UART instance pointers
  - `uart_instance_count` - Tracks active UART instances
- **Assembly Functions**:
  - `_addUART()` - Adds UART instance to global array and performs hardware initialization
- **Documentation**:
  - UART_Instance structure field offsets (for assembly access)
  - Buffer status bitmap definitions (EMPTY, FULL, WRAPPED)
  - Line Status Register (LSR) bit definitions with descriptions

Still to be implemented:
- Complete hardware initialization in `_addUART()` (baud rate, line control, interrupts)
- Interrupt handling infrastructure
- Data transmission and reception routines
- Circular buffer read/write operations
- Error handling and status reporting
- Example code and API documentation

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

## API
See `include/tl16c2550.h` for available functions and data structures. Note that the API is still under development and subject to change.
