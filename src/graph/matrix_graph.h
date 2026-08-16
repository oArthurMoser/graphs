#ifndef MATRIX_GRAPH_H
#define MATRIX_GRAPH_H

#include <string>
#include <vector>

#include "graph.h"

// Graph represented by an adjacency matrix of size N x N, where
// M[i][j] holds the weight of the edge from i to j. A sentinel value
// (NO_EDGE) indicates there is no edge.
//
// Because it uses random access to the matrix, edge queries are O(1),
// at the cost of O(N^2) memory.
class MatrixGraph : public Graph {
public:
    // Sentinel used to represent "no edge" in the adjacency matrix.
    static constexpr float NO_EDGE = 0.0f;
    // Sentinel returned by edgeWeight for a non-existent edge / invalid origin.
    static constexpr float NO_EDGE_WEIGHT = -1.0f;

    // Constructs a matrix graph with the given configuration flags.
    MatrixGraph(bool isDirected, bool isWeighted);

    bool insertVertex(std::string label) override;
    bool removeVertex(int index) override;
    void printGraph() override;
    bool insertEdge(int origin, int destination, float weight = 1) override;
    bool removeEdge(int origin, int destination) override;
    bool hasEdge(int origin, int destination) override;
    float edgeWeight(int origin, int destination) override;
    std::vector<int> neighbors(int vertex) override;
    int vertexCount() const override;

private:
    std::vector<std::string> vertexLabels_;            // Labels by index.
    std::vector<std::vector<float>> adjacencyMatrix_;  // N x N matrix.

    // Expands the matrix by one row and one column, all set to NO_EDGE.
    void growMatrix();
};

#endif // MATRIX_GRAPH_H