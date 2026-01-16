# TL16C2550
Serial Drivers for Commander X16 devices using the TL16C2550 and Compatible UARTS

## Project Structure

```
TL16C2550/
├── include/          # Public header files
│   └── tl16c2550.h  # Main UART driver API
├── src/             # Source files
│   └── tl16c2550.c  # UART driver implementation
├── obj/             # Object files (generated)
├── lib/             # Library output (generated)
│   └── tl16c2550.lib
└── Makefile         # Build system
```

## Building

This project uses the cc65 compiler suite. Make sure you have cc65 installed and in your PATH.

### Prerequisites

- cc65 toolchain (cc65, ca65, ar65, ld65)
- make

### Build Commands

```bash
# Build the library
make

# Build for a specific target (e.g., Commodore 64)
make TARGET=c64

# Clean build artifacts
make clean

# Install library and headers
make install

# Install to custom location
make install INSTALL_DIR=/path/to/install

# Show help
make help
```

## Using the Library

1. Build the library: `make`
2. Install it: `make install`
3. Include the header in your code: `#include "tl16c2550.h"`
4. Link against the library: `tl16c2550.lib`

### Example

```c
#include "tl16c2550.h"

int main(void) {
    unsigned char data;
    
    // Initialize UART
    uart_init();
    
    // Send a byte
    uart_putc('H');
    
    // Receive a byte
    if (uart_data_available()) {
        uart_getc(&data);
    }
    
    return 0;
}
```

## License

See LICENSE file for details.
