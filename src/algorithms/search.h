#ifndef SEARCH_H
#define SEARCH_H

#include <vector>

#include "graph/graph.h"

// Breadth-First Search (BFS) starting at startVertex.
// Returns a vector of vertex indices in the order they were visited.
std::vector<int> bfs(const Graph &graph, int startVertex);

// Performs BFS and prints the visited sequence (labels and indices) to stdout.
void printBfs(const Graph &graph, int startVertex);

// Depth-First Search (DFS) starting at startVertex.
// Returns a vector of vertex indices in the order they were visited.
std::vector<int> dfs(const Graph &graph, int startVertex);

// Performs DFS and prints the visited sequence (labels and indices) to stdout.
void printDfs(const Graph &graph, int startVertex);

#endif // SEARCH_H
