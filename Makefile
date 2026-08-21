CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I src

BUILD_DIR = build
SRC_DIR = src
GRAPH = $(SRC_DIR)/graph
RANDOM = $(SRC_DIR)/random

MAIN_SOURCES = $(SRC_DIR)/main.cpp \
               $(GRAPH)/graph.cpp \
               $(GRAPH)/matrix_graph.cpp \
               $(GRAPH)/list_graph.cpp \
               $(RANDOM)/create.cpp

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