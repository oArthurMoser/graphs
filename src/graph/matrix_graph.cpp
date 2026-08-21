#include <iostream>
#include <string>
#include <vector>

#include "matrix_graph.h"

MatrixGraph::MatrixGraph(bool isDirected, bool isWeighted)
    : Graph(isDirected, isWeighted) {}

void MatrixGraph::growMatrix()
{
  size_t oldSize = adjacencyMatrix_.size();
  // Grow each existing row by one column and add a new empty row.
  for (size_t i = 0; i < oldSize; ++i)
  {
    adjacencyMatrix_[i].push_back(NO_EDGE);
  }
  adjacencyMatrix_.push_back(std::vector<float>(oldSize + 1, NO_EDGE));
}

bool MatrixGraph::insertVertex(std::string label)
{
  vertexLabels_.push_back(label);
  growMatrix();
  return true;
}

bool MatrixGraph::removeVertex(int index)
{
  if (index < 0 || index >= vertexCount())
  {
    return false;
  }
  // Remove the corresponding row and column from the matrix.
  adjacencyMatrix_.erase(adjacencyMatrix_.begin() + index);
  for (size_t i = 0; i < adjacencyMatrix_.size(); ++i)
  {
    adjacencyMatrix_[i].erase(adjacencyMatrix_[i].begin() + index);
  }
  vertexLabels_.erase(vertexLabels_.begin() + index);
  return true;
}

void MatrixGraph::printGraph()
{
  std::cout << "Graph (Directed: "
            << (isDirected_ ? "yes" : "no")
            << ", Weighted: "
            << (isWeighted_ ? "yes" : "no")
            << ") [MatrixGraph]\n";
  for (size_t i = 0; i < vertexLabels_.size(); ++i)
  {
    std::cout << "[" << i << "] " << vertexLabels_[i] << " -> ";
    std::vector<int> n = neighbors(static_cast<int>(i));
    if (n.empty())
    {
      std::cout << "(no connections)\n";
      continue;
    }
    bool first = true;
    for (int dest : n)
    {
      if (!first)
      {
        std::cout << ", ";
      }
      first = false;
      std::cout << "(" << dest << ")";
      if (isWeighted_)
      {
        std::cout << " [weight: " << edgeWeight(static_cast<int>(i), dest) << "]";
      }
    }
    std::cout << "\n";
  }
}

bool MatrixGraph::insertEdge(int origin, int destination, float weight)
{
  if (origin < 0 || origin >= vertexCount() ||
      destination < 0 || destination >= vertexCount())
  {
    return false;
  }
  // For unweighted graphs the stored weight is always 1.
  float w = isWeighted_ ? weight : 1.0f;
  adjacencyMatrix_[static_cast<size_t>(origin)][static_cast<size_t>(destination)] = w;
  if (!isDirected_)
  {
    adjacencyMatrix_[static_cast<size_t>(destination)][static_cast<size_t>(origin)] = w;
  }
  return true;
}

bool MatrixGraph::removeEdge(int origin, int destination)
{
  if (origin < 0 || origin >= vertexCount() ||
      destination < 0 || destination >= vertexCount())
  {
    return false;
  }
  if (adjacencyMatrix_[static_cast<size_t>(origin)][static_cast<size_t>(destination)] == NO_EDGE)
  {
    return false;
  }
  adjacencyMatrix_[static_cast<size_t>(origin)][static_cast<size_t>(destination)] = NO_EDGE;
  if (!isDirected_)
  {
    adjacencyMatrix_[static_cast<size_t>(destination)][static_cast<size_t>(origin)] = NO_EDGE;
  }
  return true;
}

// O(1) for MatrixGraph thanks to direct matrix access.
bool MatrixGraph::hasEdge(int origin, int destination)
{
  if (origin < 0 || origin >= vertexCount() ||
      destination < 0 || destination >= vertexCount())
  {
    return false;
  }
  return adjacencyMatrix_[static_cast<size_t>(origin)][static_cast<size_t>(destination)] != NO_EDGE;
}

// O(1) for MatrixGraph thanks to direct matrix access.
float MatrixGraph::edgeWeight(int origin, int destination)
{
  if (origin < 0 || origin >= vertexCount() ||
      destination < 0 || destination >= vertexCount())
  {
    return NO_EDGE_WEIGHT;
  }
  float w = adjacencyMatrix_[static_cast<size_t>(origin)][static_cast<size_t>(destination)];
  return w == NO_EDGE ? NO_EDGE_WEIGHT : w;
}

std::vector<int> MatrixGraph::neighbors(int vertex)
{
  std::vector<int> result;
  if (vertex < 0 || vertex >= vertexCount())
  {
    return result;
  }
  const std::vector<float> &row = adjacencyMatrix_[static_cast<size_t>(vertex)];
  for (size_t j = 0; j < row.size(); ++j)
  {
    if (row[j] != NO_EDGE)
    {
      result.push_back(static_cast<int>(j));
    }
  }
  return result;
}

int MatrixGraph::vertexCount() const
{
  return static_cast<int>(vertexLabels_.size());
}