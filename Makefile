# Compiler and Flags
CC = gcc
CFLAGS = -std=c23 -Wall -Werror -Wextra -pedantic-errors

# Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Source files
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/todo.c

# Object files
OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Target executable
TARGET = $(BUILD_DIR)/todoApp

# Default target: compile and run
all: $(TARGET)
	./$(TARGET)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile the source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Link the object files to create the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# Clean up the build directory
clean:
	rm -rf $(BUILD_DIR)

# Rebuild everything from scratch
rebuild: clean all
