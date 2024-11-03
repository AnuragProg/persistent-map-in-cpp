# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -Iinclude

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = include

# Files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)            # All .cpp files in src/
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o) # Object files in obj/
TARGET = $(BIN_DIR)/main                  # Name of the final executable

# Default target
all: $(TARGET)

# Build the target executable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)  # Create bin directory if it doesn't exist
	$(CXX) $(OBJS) -o $@

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)  # Create obj directory if it doesn't exist
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

.PHONY: all clean
