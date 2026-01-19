# TL16C2550 Examples

This directory contains example programs demonstrating the capabilities of the TL16C2550 UART library. Each example serves a specific purpose in validating your setup and understanding the library's functionality.

## comptest

**Purpose:** Compilation verification

The `comptest` example is a minimal compilation test that verifies your build environment is properly configured. It confirms that the source files compile successfully without errors or warnings.

**Compilation:**
```bash
cc65 -t cx16 comptest.c tl16c2550.lib -o comptest.prg
```

**Usage:**
```bash
x16emu -prg comptest.prg
```

This is a good starting point to ensure your toolchain and compiler flags are correctly set up before proceeding to more advanced examples.

## libtest

**Purpose:** Library integration validation

The `libtest` example verifies that your build has been properly compiled and linked against the TL16C2550 library. This example performs basic arithmetic operations using library functions to confirm correct library binding and execution.

Specifically, the test adds 5 to several numbers and validates the results, ensuring that the library is correctly integrated into your build system and functioning as expected.

**Compilation:**
```bash
cc65 -t cx16 libtest.c tl16c2550.lib -o libtest.prg
```

**Usage:**
```bash
x16emu -prg libtest.prg
```

This example can be tested on the Commander X16 emulator. Run this example to confirm that library symbols are properly resolved and that the compiled library is accessible to your application.

## finduart

**Purpose:** Hardware device discovery and communication testing

The `finduart` example performs an enumeration scan of connected devices to identify UART interfaces compatible with the TL16C2550 chipset. The scan locates devices by detecting the characteristic signature stored in the scratch register at offset 7.

Once devices are identified, this example validates basic communication with the detected hardware to ensure proper connectivity and operation.

**Compilation:**
```bash
cc65 -t cx16 finduart.c tl16c2550.lib -o finduart.prg
```

**Hardware Requirement:**

This example requires real Commander X16 hardware with compatible UART devices connected to your system. It cannot be tested on the emulator alone. Once compiled, load the `.prg` file onto your hardware and execute it for device discovery and initial hardware validation.

**Note:** The device signature scan may produce false positives if other hardware shares similar register characteristics. Always verify detected devices through independent means when possible, and validate communication parameters before attempting read/write operations on critical hardware.

## Building All Examples

To compile all examples at once:
```bash
make
```

Refer to the project Makefile for additional build options and targets.

## Manual Compilation

Each example can be compiled independently using the cc65 compiler with the following general pattern:
```bash
cc65 -t cx16 <example>.c tl16c2550.lib -o <example>.prg
```

This command targets the Commander X16 platform (`-t cx16`), links against the TL16C2550 library, and produces a runnable program file.
