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

.PHONY: all build run clean

all: build

# Compiles graph sources and main.cpp into a single binary.
build: $(MAIN_BINARY)

$(MAIN_BINARY): $(MAIN_SOURCES)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Runs the generated binary.
run: $(MAIN_BINARY)
	./$(MAIN_BINARY)

# Removes the build directory (portable: works on macOS/Linux and MinGW/MSYS2/WSL).
clean:
	rm -rf $(BUILD_DIR)