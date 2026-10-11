#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

#include "dijkstra.h"

std::vector<int> DijkstraResult::getPathTo(int destination) const
{
  std::vector<int> path;
  if (destination < 0 || destination >= static_cast<int>(distances.size()))
  {
    return path;
  }
  if (distances[static_cast<size_t>(destination)] == INFINITY_DIST)
  {
    return path; // Unreachable
  }

  for (int at = destination; at != -1; at = predecessors[static_cast<size_t>(at)])
  {
    path.push_back(at);
    if (at == startVertex)
    {
      break;
    }
  }

  std::reverse(path.begin(), path.end());
  return path;
}

void DijkstraResult::printResult(const Graph &graph) const
{
  std::cout << "Dijkstra Shortest Paths (origin: [" << startVertex << "] "
            << graph.vertexLabel(startVertex) << "):\n";

  for (size_t i = 0; i < distances.size(); ++i)
  {
    int dest = static_cast<int>(i);
    std::cout << "  -> Dest: [" << dest << "] " << graph.vertexLabel(dest)
              << " | Dist: ";

    if (distances[i] == INFINITY_DIST)
    {
      std::cout << "INF | Path: (unreachable)\n";
    }
    else
    {
      std::cout << distances[i] << " | Path: ";
      std::vector<int> path = getPathTo(dest);
      for (size_t p = 0; p < path.size(); ++p)
      {
        if (p > 0)
        {
          std::cout << " -> ";
        }
        std::cout << "[" << path[p] << "] " << graph.vertexLabel(path[p]);
      }
      std::cout << "\n";
    }
  }
}

DijkstraResult dijkstra(const Graph &graph, int startVertex)
{
  DijkstraResult result;
  const int n = graph.vertexCount();
  if (startVertex < 0 || startVertex >= n)
  {
    return result;
  }

  result.startVertex = startVertex;
  result.distances.assign(static_cast<size_t>(n), INFINITY_DIST);
  result.predecessors.assign(static_cast<size_t>(n), -1);

  std::vector<bool> closed(static_cast<size_t>(n), false);

  result.distances[static_cast<size_t>(startVertex)] = 0.0f;
  int current = startVertex;

  while (current != -1)
  {
    // Explore all neighbors of current vertex
    for (int neighbor : const_cast<Graph &>(graph).neighbors(current))
    {
      if (!closed[static_cast<size_t>(neighbor)])
      {
        float weight = const_cast<Graph &>(graph).edgeWeight(current, neighbor);
        if (weight >= 0) // Valid edge
        {
          float newDist = result.distances[static_cast<size_t>(current)] + weight;
          if (newDist < result.distances[static_cast<size_t>(neighbor)])
          {
            result.distances[static_cast<size_t>(neighbor)] = newDist;
            result.predecessors[static_cast<size_t>(neighbor)] = current;
          }
        }
      }
    }

    // Mark current as closed
    closed[static_cast<size_t>(current)] = true;

    // Pick next open vertex with minimum non-infinite distance
    int nextVertex = -1;
    float minDistance = INFINITY_DIST;

    for (int i = 0; i < n; ++i)
    {
      if (!closed[static_cast<size_t>(i)] && result.distances[static_cast<size_t>(i)] < minDistance)
      {
        minDistance = result.distances[static_cast<size_t>(i)];
        nextVertex = i;
      }
    }

    current = nextVertex;
  }

  return result;
}
