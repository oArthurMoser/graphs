#include <iostream>
#include <memory>
#include <string>

#include "algorithms/dijkstra.h"
#include "algorithms/search.h"
#include "graph/list_graph.h"
#include "graph/matrix_graph.h"
#include "io/graph_reader.h"

void runNavigationDemo(const std::string &filePath)
{
  std::cout << "====================================================\n";
  std::cout << " DEMO 1: BFS & DFS on Navigation Graph\n";
  std::cout << " File: " << filePath << "\n";
  std::cout << "====================================================\n\n";

  // 1. Load into MatrixGraph and ListGraph
  std::unique_ptr<MatrixGraph> matrixG = GraphReader::readMatrixGraph(filePath);
  std::unique_ptr<ListGraph> listG = GraphReader::readListGraph(filePath);

  if (!matrixG || !listG)
  {
    std::cerr << "Failed to load navigation graph.\n";
    return;
  }

  std::cout << "--- MatrixGraph Representation ---\n";
  matrixG->printGraph();
  std::cout << "\n";

  std::cout << "--- ListGraph Representation ---\n";
  listG->printGraph();
  std::cout << "\n";

  // 2. Run BFS on both
  std::cout << "--- BFS Traversal (Start: Vertex 0 / A) ---\n";
  std::cout << "[MatrixGraph] ";
  printBfs(*matrixG, 0);
  std::cout << "[ListGraph]   ";
  printBfs(*listG, 0);
  std::cout << "\n";

  // 3. Run DFS on both
  std::cout << "--- DFS Traversal (Start: Vertex 0 / A) ---\n";
  std::cout << "[MatrixGraph] ";
  printDfs(*matrixG, 0);
  std::cout << "[ListGraph]   ";
  printDfs(*listG, 0);
  std::cout << "\n";
}

void runDijkstraDemo(const std::string &filePath)
{
  std::cout << "====================================================\n";
  std::cout << " DEMO 2: Dijkstra Shortest Path on Weighted Graph\n";
  std::cout << " File: " << filePath << "\n";
  std::cout << "====================================================\n\n";

  std::unique_ptr<MatrixGraph> matrixG = GraphReader::readMatrixGraph(filePath);
  std::unique_ptr<ListGraph> listG = GraphReader::readListGraph(filePath);

  if (!matrixG || !listG)
  {
    std::cerr << "Failed to load dijkstra graph.\n";
    return;
  }

  std::cout << "--- MatrixGraph Representation ---\n";
  matrixG->printGraph();
  std::cout << "\n";

  std::cout << "--- ListGraph Representation ---\n";
  listG->printGraph();
  std::cout << "\n";

  std::cout << "--- Running Dijkstra (Start: Vertex 0 / A) ---\n";
  std::cout << "[MatrixGraph Results]\n";
  DijkstraResult resMatrix = dijkstra(*matrixG, 0);
  resMatrix.printResult(*matrixG);
  std::cout << "\n";

  std::cout << "[ListGraph Results]\n";
  DijkstraResult resList = dijkstra(*listG, 0);
  resList.printResult(*listG);
  std::cout << "\n";
}

void runBasicOperationsDemo()
{
  std::cout << "====================================================\n";
  std::cout << " DEMO 3: Basic Graph Operations (Insert, Query, Remove)\n";
  std::cout << "====================================================\n\n";

  MatrixGraph mg(false, true); // Undirected, weighted
  mg.insertVertex("Alpha");
  mg.insertVertex("Beta");
  mg.insertVertex("Gamma");
  mg.insertEdge(0, 1, 4.5f);
  mg.insertEdge(1, 2, 7.2f);

  std::cout << "Initial MatrixGraph:\n";
  mg.printGraph();

  std::cout << "\nHas edge (Alpha -> Beta): " << (mg.hasEdge(0, 1) ? "true" : "false") << "\n";
  std::cout << "Edge weight (Alpha -> Beta): " << mg.edgeWeight(0, 1) << "\n";
  std::cout << "Vertex count: " << mg.vertexCount() << "\n";
  std::cout << "Label of vertex 0: " << mg.vertexLabel(0) << "\n";

  std::cout << "\nRemoving edge (Beta <-> Gamma)...\n";
  mg.removeEdge(1, 2);
  mg.printGraph();

  std::cout << "\nRemoving vertex 0 (Alpha)...\n";
  mg.removeVertex(0);
  mg.printGraph();
  std::cout << "\n";
}

int main()
{
  runNavigationDemo("graph_examples/example_navigation.txt");
  runDijkstraDemo("graph_examples/example_dijkstra.txt");
  runBasicOperationsDemo();

  return 0;
}