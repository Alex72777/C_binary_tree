# Compiler and flags
CC      = gcc
CFLAGS  = -Wall -Wextra -g

# Directories
SRC_DIR   = src
BUILD_DIR = build

# Output binary name
TARGET  = $(BUILD_DIR)/binary_tree

# Source and object files
SRCS    = $(SRC_DIR)/main.c $(SRC_DIR)/objects.c $(SRC_DIR)/binary_tree.c
OBJS    = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Default target: build the binary
all: $(BUILD_DIR) $(TARGET)

# Create the build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Link object files into the final binary
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile each .c file into a .o file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Remove all build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Rebuild everything from scratch
rebuild: clean all

# Declare targets that are not real files
.PHONY: all clean rebuild
