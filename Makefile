# Simple Makefile as an alternative to CMake
# You can use this if you prefer make over CMake

CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c99 -g -O0
INCLUDES = -I./include
LIBS = -lpthread -lm

# Add -lssl -lcrypto if you want OpenSSL support
ifdef USE_SSL
    LIBS += -lssl -lcrypto
    CFLAGS += -DUSE_SSL
endif

# Source files
SRCDIR = src
INCDIR = include
BUILDDIR = build
BINDIR = $(BUILDDIR)/bin

# Find all .c files in src directory and subdirectories
SOURCES = $(shell find $(SRCDIR) -name "*.c")
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)

# Target executable
TARGET = $(BINDIR)/c_https_server

# Default target
all: $(TARGET)

# Create directories
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BINDIR): $(BUILDDIR)
	mkdir -p $(BINDIR)

# Build object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build executable
$(TARGET): main.c $(OBJECTS) | $(BINDIR)
	$(CC) $(CFLAGS) $(INCLUDES) main.c $(OBJECTS) -o $@ $(LIBS)

# Clean build files
clean:
	rm -rf $(BUILDDIR)

# Debug target with additional flags
debug: CFLAGS += -DDEBUG -g3
debug: $(TARGET)

# Release target with optimization
release: CFLAGS = -Wall -Wextra -Wpedantic -std=c99 -O3 -DNDEBUG
release: $(TARGET)

# Install dependencies (Ubuntu/Debian)
install-deps:
	sudo apt update
	sudo apt install -y build-essential libssl-dev gdb valgrind

# Run with valgrind
valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

.PHONY: all clean debug release install-deps valgrind

# Help target
help:
	@echo "Available targets:"
	@echo "  all          - Build the project (default)"
	@echo "  debug        - Build with debug flags"
	@echo "  release      - Build with optimization"
	@echo "  clean        - Remove build files"
	@echo "  install-deps - Install development dependencies"
	@echo "  valgrind     - Run with memory checking"
	@echo "  help         - Show this help message"
	@echo ""
	@echo "Options:"
	@echo "  USE_SSL=1    - Enable SSL support (make USE_SSL=1)"
