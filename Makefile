CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I src

BUILD_DIR = build
SRC_DIR = src

MAIN_SOURCES = $(SRC_DIR)/main.cpp \
               $(SRC_DIR)/graph/graph.cpp \
               $(SRC_DIR)/graph/matrix_graph.cpp \
               $(SRC_DIR)/graph/list_graph.cpp

MAIN_BINARY = $(BUILD_DIR)/main

.SUFFIXES:

.PHONY: all build run test-matrix test-list clean

all: build

# Compiles graph sources and main.cpp into a single binary.
build: $(MAIN_BINARY)

$(MAIN_BINARY): $(MAIN_SOURCES)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Runs the generated binary.
run: $(MAIN_BINARY)
	./$(MAIN_BINARY)

# Compiles and runs the MatrixGraph unit tests (if they exist).
test-matrix:
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/test_matrix $(SRC_DIR)/unit_tests/matrix_graph_test.cpp \
	    $(SRC_DIR)/graph/graph.cpp $(SRC_DIR)/graph/matrix_graph.cpp
	./$(BUILD_DIR)/test_matrix

# Compiles and runs the ListGraph unit tests (if they exist).
test-list:
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/test_list $(SRC_DIR)/unit_tests/list_graph_test.cpp \
	    $(SRC_DIR)/graph/graph.cpp $(SRC_DIR)/graph/list_graph.cpp
	./$(BUILD_DIR)/test_list

# Removes the build directory (portable: works on macOS/Linux and MinGW/MSYS2/WSL).
clean:
	rm -rf $(BUILD_DIR)