#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <limits>
#include <vector>

#include "graph/graph.h"

constexpr float INFINITY_DIST = std::numeric_limits<float>::infinity();

struct DijkstraResult
{
  int startVertex = -1;
  std::vector<float> distances;
  std::vector<int> predecessors;

  // Returns the reconstructed shortest path from startVertex to destination.
  // Returns an empty vector if destination is unreachable.
  std::vector<int> getPathTo(int destination) const;

  // Prints the shortest distances and full paths to all vertices.
  void printResult(const Graph &graph) const;
};

// Computes single-source shortest paths from startVertex using Dijkstra's algorithm.
DijkstraResult dijkstra(const Graph &graph, int startVertex);

#endif // DIJKSTRA_H
