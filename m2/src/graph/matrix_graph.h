#ifndef MATRIX_GRAPH_H
#define MATRIX_GRAPH_H

#include <string>
#include <vector>

#include "graph.h"

using namespace std;

// Grafo representado por Matriz de Adjacencia N x N
class MatrixGraph : public Graph
{
public:
  static constexpr float NO_EDGE = 0.0f;
  static constexpr float NO_EDGE_WEIGHT = -1.0f;

  MatrixGraph(bool isDirected, bool isWeighted);

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
  vector<vector<float>> adjacencyMatrix_;

  void growMatrix();
};

#endif // MATRIX_GRAPH_H