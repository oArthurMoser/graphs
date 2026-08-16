#include <iostream>

#include "graph/list_graph.h"
#include "graph/matrix_graph.h"

// Demonstrates the basic graph operations on both MatrixGraph and ListGraph.
int main() {
    std::cout << "========== MatrixGraph (directed, weighted) ==========\n";
    MatrixGraph matrixGraph(true, true);

    matrixGraph.insertVertex("A");
    matrixGraph.insertVertex("B");
    matrixGraph.insertVertex("C");
    matrixGraph.insertVertex("D");

    matrixGraph.insertEdge(0, 1, 3.0f);
    matrixGraph.insertEdge(0, 2, 1.0f);
    matrixGraph.insertEdge(1, 2, 5.0f);
    matrixGraph.insertEdge(2, 3, 2.0f);

    matrixGraph.printGraph();

    std::cout << "\n-- Queries on MatrixGraph --\n";
    std::cout << "hasEdge(0, 1): " << (matrixGraph.hasEdge(0, 1) ? "true" : "false") << "\n";
    std::cout << "hasEdge(3, 0): " << (matrixGraph.hasEdge(3, 0) ? "true" : "false") << "\n";
    std::cout << "edgeWeight(1, 2): " << matrixGraph.edgeWeight(1, 2) << "\n";
    std::cout << "edgeWeight(0, 3) [no edge]: " << matrixGraph.edgeWeight(0, 3) << "\n";
    std::cout << "neighbors(0): ";
    for (int n : matrixGraph.neighbors(0)) {
        std::cout << n << " ";
    }
    std::cout << "\n";

    std::cout << "\n-- Removing edge (1, 2) on MatrixGraph --\n";
    matrixGraph.removeEdge(1, 2);
    matrixGraph.printGraph();

    std::cout << "\n-- Removing vertex 1 on MatrixGraph --\n";
    matrixGraph.removeVertex(1);
    matrixGraph.printGraph();

    std::cout << "\n========== ListGraph (undirected, unweighted) ==========\n";
    ListGraph listGraph(false, false);

    listGraph.insertVertex("A");
    listGraph.insertVertex("B");
    listGraph.insertVertex("C");
    listGraph.insertVertex("D");

    listGraph.insertEdge(0, 1);
    listGraph.insertEdge(0, 2);
    listGraph.insertEdge(1, 2);
    listGraph.insertEdge(2, 3);

    listGraph.printGraph();

    std::cout << "\n-- Queries on ListGraph --\n";
    std::cout << "hasEdge(1, 0) [reverse of 0-1]: "
              << (listGraph.hasEdge(1, 0) ? "true" : "false") << "\n";
    std::cout << "edgeWeight(2, 3): " << listGraph.edgeWeight(2, 3) << "\n";
    std::cout << "edgeWeight(0, 3) [no edge]: " << listGraph.edgeWeight(0, 3) << "\n";
    std::cout << "neighbors(2): ";
    for (int n : listGraph.neighbors(2)) {
        std::cout << n << " ";
    }
    std::cout << "\n";

    std::cout << "\n-- Removing vertex 1 on ListGraph (reindexes remaining) --\n";
    listGraph.removeVertex(1);
    listGraph.printGraph();

    return 0;
}