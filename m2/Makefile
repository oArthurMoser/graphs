CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I src

BUILD_DIR = build
SRC_DIR = src
GRAPH = $(SRC_DIR)/graph
IO = $(SRC_DIR)/io
COLORING = $(SRC_DIR)/algorithms/coloring
MST = $(SRC_DIR)/algorithms/mst

MAIN_SOURCES = $(SRC_DIR)/main.cpp \
               $(GRAPH)/graph.cpp \
               $(GRAPH)/matrix_graph.cpp \
               $(GRAPH)/list_graph.cpp \
               $(IO)/graph_reader.cpp \
               $(COLORING)/brute_force.cpp \
               $(COLORING)/welsh_powell.cpp \
               $(COLORING)/dsatur.cpp \
               $(COLORING)/ordem_arbitraria.cpp \
               $(MST)/prim.cpp \
               $(MST)/kruskal.cpp

MAIN_BINARY = $(BUILD_DIR)/main

.SUFFIXES:

.PHONY: all build run clean

all: build

build: $(MAIN_BINARY)

$(MAIN_BINARY): $(MAIN_SOURCES)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

run: $(MAIN_BINARY)
	./$(MAIN_BINARY)

clean:
	rm -rf $(BUILD_DIR)

