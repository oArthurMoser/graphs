#ifndef LIST_GRAPH_H
#define LIST_GRAPH_H

#include <string>
#include <vector>

#include "edge.h"
#include "graph.h"

// Graph represented by an adjacency list: for each vertex i, a list of
// Edge objects stores all edges leaving i.
//
// Edges use less memory than a matrix for sparse graphs, but checking the
// existence of an edge is O(degree of the vertex) instead of O(1).
class ListGraph : public Graph
{
public:
  // Constructs an adjacency-list graph with the given configuration flags.
  ListGraph(bool isDirected, bool isWeighted);

  bool insertVertex(std::string label) override;
  bool removeVertex(int index) override;
  void printGraph() override;
  bool insertEdge(int origin, int destination, float weight = 1) override;
  bool removeEdge(int origin, int destination) override;
  bool hasEdge(int origin, int destination) override;
  float edgeWeight(int origin, int destination) override;
  std::vector<int> neighbors(int vertex) override;
  std::string vertexLabel(int index) const override;
  int vertexCount() const override;

private:
  std::vector<std::string> vertexLabels_;        // Labels by index.
  std::vector<std::vector<Edge>> adjacencyList_; // Outgoing edges per vertex.
};

#endif // LIST_GRAPH_H