# Makefile for TL16C2550 UART Library
# Target: Commander X16 (or other cc65 targets)

# Project name
PROJECT = tl16c2550

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
LIB_DIR = lib

# Target platform (change to your target: c64, cx16, apple2, etc.)
TARGET = cx16

# Tools
CC = cc65
AS = ca65
AR = ar65
LD = ld65

# Compiler flags
CFLAGS = -t $(TARGET) -O -I $(INC_DIR)
ASFLAGS = -t $(TARGET) -I $(INC_DIR)

# Source files
C_SOURCES = $(wildcard $(SRC_DIR)/*.c)
ASM_SOURCES = $(wildcard $(SRC_DIR)/*.s)

# Object files
C_OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SOURCES))
ASM_OBJECTS = $(patsubst $(SRC_DIR)/%.s,$(OBJ_DIR)/%.o,$(ASM_SOURCES))
OBJECTS = $(C_OBJECTS) $(ASM_OBJECTS)

# Library file
LIBRARY = $(LIB_DIR)/$(PROJECT).lib

# Default target
.PHONY: all
all: $(LIBRARY)

# Create directories if they don't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

# Compile C source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $(OBJ_DIR)/$*.s $<
	$(AS) $(ASFLAGS) -o $@ $(OBJ_DIR)/$*.s

# Assemble assembly source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s | $(OBJ_DIR)
	$(AS) $(ASFLAGS) -o $@ $<

# Create library
$(LIBRARY): $(OBJECTS) | $(LIB_DIR)
	$(AR) a $@ $(OBJECTS)

# Clean build artifacts
.PHONY: clean
clean:
	rm -f $(OBJ_DIR)/*.o $(OBJ_DIR)/*.s
	rm -f $(LIBRARY)

# Clean everything including directories
.PHONY: distclean
distclean: clean
	rm -rf $(OBJ_DIR) $(LIB_DIR)

# Install target (copy library and headers to a distribution directory)
INSTALL_DIR ?= dist
INSTALL_LIB_DIR = $(INSTALL_DIR)/lib
INSTALL_INC_DIR = $(INSTALL_DIR)/include

.PHONY: install
install: $(LIBRARY)
	mkdir -p $(INSTALL_LIB_DIR)
	mkdir -p $(INSTALL_INC_DIR)
	cp $(LIBRARY) $(INSTALL_LIB_DIR)/
	cp $(INC_DIR)/*.h $(INSTALL_INC_DIR)/

# Help target
.PHONY: help
help:
	@echo "TL16C2550 UART Library Build System"
	@echo ""
	@echo "Targets:"
	@echo "  all        - Build the library (default)"
	@echo "  clean      - Remove build artifacts"
	@echo "  distclean  - Remove all generated files and directories"
	@echo "  install    - Install library and headers to $(INSTALL_DIR)"
	@echo "  help       - Show this help message"
	@echo ""
	@echo "Variables:"
	@echo "  TARGET     - Target platform (default: $(TARGET))"
	@echo "  INSTALL_DIR- Installation directory (default: $(INSTALL_DIR))"
	@echo ""
	@echo "Example usage:"
	@echo "  make                    # Build for $(TARGET)"
	@echo "  make TARGET=c64         # Build for Commodore 64"
	@echo "  make install            # Install to dist/"
	@echo "  make INSTALL_DIR=/opt   # Install to custom location"
