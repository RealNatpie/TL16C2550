# Makefile for TL16C2550 Serial Library (Commander X16)
# Requires cc65 cross compiler toolchain

# Detect operating system
ifeq ($(OS),Windows_NT)
    # Windows commands
    RM = del /Q
    RMDIR = rmdir /S /Q
    MKDIR = if not exist
    CP = copy /Y
    FIXPATH = $(subst /,\,$1)
else
    # Unix/Linux/Mac commands
    RM = rm -f
    RMDIR = rm -rf
    MKDIR = mkdir -p
    CP = cp
    FIXPATH = $1
endif

# Tool definitions
CC = cl65
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
CFLAGS = -t $(TARGET) -c -O -I $(INC_DIR)
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
LIBRARY = $(BUILD_DIR)/tl16c2550.lib

# Examples directory
EXAMPLES_DIR = examples
BUILD_EXAMPLES_DIR = $(BUILD_DIR)/$(EXAMPLES_DIR)

# Example programs
EXAMPLE_SOURCES = $(wildcard $(EXAMPLES_DIR)/*.c)
EXAMPLE_PROGRAMS = $(patsubst $(EXAMPLES_DIR)/%.c,$(BUILD_EXAMPLES_DIR)/%.prg,$(EXAMPLE_SOURCES))

# Default target
all: $(BUILD_DIR) $(LIBRARY) copy-headers examples

# Create build directory
$(BUILD_DIR):
	$(MKDIR) $(call FIXPATH,$(BUILD_DIR))

# Create build examples directory
$(BUILD_EXAMPLES_DIR): $(BUILD_DIR)
	$(MKDIR) $(call FIXPATH,$(BUILD_EXAMPLES_DIR))

# Build library from object files
$(LIBRARY): $(ALL_OBJECTS)
	$(AR) a $@ $^
	$(RM) $(ALL_OBJECTS)

# Compile C source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $<

# Assemble assembly source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.s $(HEADERS)
	$(AS) $(ASFLAGS) -o $@ $<

# Copy header files to build directory
copy-headers: $(BUILD_DIR)
ifeq ($(OS),Windows_NT)
	-$(CP) $(call FIXPATH,$(INC_DIR)\*.h) $(call FIXPATH,$(BUILD_DIR)\ )
	-$(CP) $(call FIXPATH,$(INC_DIR)\*.inc) $(call FIXPATH,$(BUILD_DIR)\ )
else
	-$(CP) $(INC_DIR)/*.h $(BUILD_DIR)/
	-$(CP) $(INC_DIR)/*.inc $(BUILD_DIR)/
endif

# Build example programs
examples: $(BUILD_EXAMPLES_DIR) $(LIBRARY) $(EXAMPLE_PROGRAMS)

$(BUILD_EXAMPLES_DIR)/%.prg: $(EXAMPLES_DIR)/%.c $(LIBRARY) $(HEADERS)
	$(CC) -t $(TARGET) -I $(INC_DIR) $< $(LIBRARY) -o $@

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
	@echo "  all          - Build library, copy headers, and compile examples (default)"
	@echo "  examples     - Compile example programs to build/examples/"
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
