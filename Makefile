# Makefile for TL16C2550 Serial Library (Commander X16)
# Requires cc65 cross compiler toolchain

# Tool definitions
CC = cc65
AS = ca65
AR = ar65
LD = ld65

# Target platform
TARGET = cx16

# Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Compiler flags
CFLAGS = -t $(TARGET) -O -I $(INC_DIR)
ASFLAGS = -t $(TARGET) -I $(INC_DIR)

# Source files
C_SOURCES = $(wildcard $(SRC_DIR)/*.c)
ASM_SOURCES = $(wildcard $(SRC_DIR)/*.s)

# Object files
C_OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(C_SOURCES))
ASM_OBJECTS = $(patsubst $(SRC_DIR)/%.s,$(BUILD_DIR)/%.o,$(ASM_SOURCES))
ALL_OBJECTS = $(C_OBJECTS) $(ASM_OBJECTS)

# Header files
HEADERS = $(wildcard $(INC_DIR)/*.h) $(wildcard $(INC_DIR)/*.inc)

# Library name
LIBRARY = $(BUILD_DIR)/libtl16c2550.a

# Default target
all: $(BUILD_DIR) $(LIBRARY) copy-headers

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build library from object files
$(LIBRARY): $(ALL_OBJECTS)
	$(AR) a $@ $^

# Compile C source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$*.s $<
	$(AS) $(ASFLAGS) -o $@ $(BUILD_DIR)/$*.s

# Assemble assembly source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.s $(HEADERS)
	$(AS) $(ASFLAGS) -o $@ $<

# Copy header files to build directory
copy-headers: $(BUILD_DIR)
	cp $(INC_DIR)/*.h $(BUILD_DIR)/ 2>/dev/null || true
	cp $(INC_DIR)/*.inc $(BUILD_DIR)/ 2>/dev/null || true

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Install to system (optional)
install: all
	@echo "Install target not implemented. Use headers and library from $(BUILD_DIR)/"

# Display help
help:
	@echo "TL16C2550 Serial Library Makefile"
	@echo "=================================="
	@echo "Targets:"
	@echo "  all          - Build library and copy headers (default)"
	@echo "  clean        - Remove build artifacts"
	@echo "  help         - Display this help message"
	@echo ""
	@echo "Output:"
	@echo "  Library:  $(LIBRARY)"
	@echo "  Headers:  $(BUILD_DIR)/*.h, $(BUILD_DIR)/*.inc"
	@echo ""
	@echo "Requirements:"
	@echo "  - cc65 cross compiler toolchain"
	@echo "  - Target platform: $(TARGET)"

.PHONY: all clean install copy-headers help
