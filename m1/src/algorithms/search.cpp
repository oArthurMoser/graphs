#include <iostream>
#include <queue>
#include <vector>

#include "search.h"

std::vector<int> bfs(const Graph &graph, int startVertex)
{
  std::vector<int> visitOrder;
  const int n = graph.vertexCount();
  if (startVertex < 0 || startVertex >= n)
  {
    return visitOrder;
  }

  std::vector<bool> visited(static_cast<size_t>(n), false);
  std::queue<int> queue;

  visited[static_cast<size_t>(startVertex)] = true;
  queue.push(startVertex);
  visitOrder.push_back(startVertex);

  while (!queue.empty())
  {
    int current = queue.front();
    queue.pop();

    for (int neighbor : const_cast<Graph &>(graph).neighbors(current))
    {
      if (!visited[static_cast<size_t>(neighbor)])
      {
        visited[static_cast<size_t>(neighbor)] = true;
        visitOrder.push_back(neighbor);
        queue.push(neighbor);
      }
    }
  }

  return visitOrder;
}

void printBfs(const Graph &graph, int startVertex)
{
  std::vector<int> order = bfs(graph, startVertex);
  std::cout << "BFS (start: [" << startVertex << "] "
            << graph.vertexLabel(startVertex) << "): ";
  for (size_t i = 0; i < order.size(); ++i)
  {
    if (i > 0)
    {
      std::cout << " -> ";
    }
    std::cout << "[" << order[i] << "] " << graph.vertexLabel(order[i]);
  }
  std::cout << "\n";
}

namespace
{
  void dfsRecursive(const Graph &graph, int current, std::vector<bool> &visited, std::vector<int> &visitOrder)
  {
    visited[static_cast<size_t>(current)] = true;
    visitOrder.push_back(current);

    for (int neighbor : const_cast<Graph &>(graph).neighbors(current))
    {
      if (!visited[static_cast<size_t>(neighbor)])
      {
        dfsRecursive(graph, neighbor, visited, visitOrder);
      }
    }
  }
} // namespace

std::vector<int> dfs(const Graph &graph, int startVertex)
{
  std::vector<int> visitOrder;
  const int n = graph.vertexCount();
  if (startVertex < 0 || startVertex >= n)
  {
    return visitOrder;
  }

  std::vector<bool> visited(static_cast<size_t>(n), false);
  dfsRecursive(graph, startVertex, visited, visitOrder);
  return visitOrder;
}

void printDfs(const Graph &graph, int startVertex)
{
  std::vector<int> order = dfs(graph, startVertex);
  std::cout << "DFS (start: [" << startVertex << "] "
            << graph.vertexLabel(startVertex) << "): ";
  for (size_t i = 0; i < order.size(); ++i)
  {
    if (i > 0)
    {
      std::cout << " -> ";
    }
    std::cout << "[" << order[i] << "] " << graph.vertexLabel(order[i]);
  }
  std::cout << "\n";
}
