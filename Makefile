# out
TARGET = $(BIN_DIR)/app

# compiler
CXX = g++

# folders
SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin
BUILD_DIR = build
LIB_DIR = lib

# flags
CXXFLAGS = -Wall -Wextra -O2 -I$(INCLUDE_DIR) -L$(LIB_DIR)
LDFLAGS = -lglfw -lglad

# .c/.cpp files
SRC_FILES = $(wildcard $(SRC_DIR)/**/*.cpp)

# .o files
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# out rule
$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ_FILES) $(LDFLAGS)

# .cpp compile
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

refresh: clean run

clean:
	rm -rf $(BUILD_DIR)/* $(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all $(TARGET)

valgrind_extreme: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes $(TARGET)

.PHONY: all run refresh clean valgrind valgrind_extreme