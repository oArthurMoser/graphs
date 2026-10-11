#ifndef LIST_GRAPH_H
#define LIST_GRAPH_H

#include <string>
#include <vector>

#include "edge.h"
#include "graph.h"

using namespace std;

// Grafo representado por Lista de Adjacencia
class ListGraph : public Graph
{
public:
  ListGraph(bool isDirected, bool isWeighted);

  bool insertVertex(string label) override;
  bool removeVertex(int index) override;
  void printGraph() override;
  bool insertEdge(int origin, int destination, float weight = 1) override;
  bool removeEdge(int origin, int destination) override;
  bool hasEdge(int origin, int destination) override;
  float edgeWeight(int origin, int destination) override;
  vector<int> neighbors(int vertex) override;
  string vertexLabel(int index) const override;
  int vertexCount() const override;

private:
  vector<string> vertexLabels_;
  vector<vector<Edge>> adjacencyList_;
};

#endif // LIST_GRAPH_H