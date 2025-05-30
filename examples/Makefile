# Makefile for generic linked list example
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
INCLUDE_DIR = ../include
SRC_DIR = ../src/linkedList
BIN_DIR = ../bin

# Create bin directory if it doesn't exist
$(shell mkdir -p $(BIN_DIR))

# Source files
SOURCES = generic_list_example.c \
          $(SRC_DIR)/createNode.c \
          $(SRC_DIR)/insertAtHead.c \
          $(SRC_DIR)/insertAtTail.c \
          $(SRC_DIR)/deleteNode.c \
          $(SRC_DIR)/displayList.c \
          $(SRC_DIR)/freeList.c \
          $(SRC_DIR)/helpers.c

# Object files
OBJECTS = $(SOURCES:.c=.o)

# Target executable - now goes to bin directory
TARGET = $(BIN_DIR)/generic_list_example

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Clean
clean:
	rm -f $(OBJECTS) $(TARGET)

# Run the example
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
