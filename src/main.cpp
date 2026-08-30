#include <chrono>
#include <iomanip>
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

  std::cout << "--- BFS Traversal (Start: Vertex 0 / A) ---\n";
  std::cout << "[MatrixGraph] ";
  printBfs(*matrixG, 0);
  std::cout << "[ListGraph]   ";
  printBfs(*listG, 0);
  std::cout << "\n";

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

void runLargeGraphDemo(const std::string &filePath)
{
  std::cout << "====================================================\n";
  std::cout << " DEMO 3: Performance & Traversal on Large Graph\n";
  std::cout << " File: " << filePath << "\n";
  std::cout << "====================================================\n\n";

  auto t0 = std::chrono::high_resolution_clock::now();
  std::unique_ptr<MatrixGraph> matrixG = GraphReader::readMatrixGraph(filePath);
  auto t1 = std::chrono::high_resolution_clock::now();
  std::unique_ptr<ListGraph> listG = GraphReader::readListGraph(filePath);
  auto t2 = std::chrono::high_resolution_clock::now();

  if (!matrixG || !listG)
  {
    std::cerr << "Failed to load large graph.\n";
    return;
  }

  double loadMatrixMs = std::chrono::duration<double, std::milli>(t1 - t0).count();
  double loadListMs = std::chrono::duration<double, std::milli>(t2 - t1).count();

  std::cout << "Vertices in graph: " << matrixG->vertexCount() << "\n";
  std::cout << "Load Time -> MatrixGraph: " << loadMatrixMs << " ms | ListGraph: " << loadListMs << " ms\n\n";

  // Measure BFS
  auto bfsStartM = std::chrono::high_resolution_clock::now();
  std::vector<int> bfsOrderM = bfs(*matrixG, 0);
  auto bfsEndM = std::chrono::high_resolution_clock::now();

  auto bfsStartL = std::chrono::high_resolution_clock::now();
  std::vector<int> bfsOrderL = bfs(*listG, 0);
  auto bfsEndL = std::chrono::high_resolution_clock::now();

  std::cout << "BFS reached " << bfsOrderM.size() << " vertices.\n";
  std::cout << "BFS Time -> MatrixGraph: "
            << std::chrono::duration<double, std::micro>(bfsEndM - bfsStartM).count() << " us | ListGraph: "
            << std::chrono::duration<double, std::micro>(bfsEndL - bfsStartL).count() << " us\n\n";

  // Measure DFS
  auto dfsStartM = std::chrono::high_resolution_clock::now();
  std::vector<int> dfsOrderM = dfs(*matrixG, 0);
  auto dfsEndM = std::chrono::high_resolution_clock::now();

  auto dfsStartL = std::chrono::high_resolution_clock::now();
  std::vector<int> dfsOrderL = dfs(*listG, 0);
  auto dfsEndL = std::chrono::high_resolution_clock::now();

  std::cout << "DFS reached " << dfsOrderM.size() << " vertices.\n";
  std::cout << "DFS Time -> MatrixGraph: "
            << std::chrono::duration<double, std::micro>(dfsEndM - dfsStartM).count() << " us | ListGraph: "
            << std::chrono::duration<double, std::micro>(dfsEndL - dfsStartL).count() << " us\n\n";

  // Measure Dijkstra
  auto dijkStartM = std::chrono::high_resolution_clock::now();
  DijkstraResult dijkM = dijkstra(*matrixG, 0);
  auto dijkEndM = std::chrono::high_resolution_clock::now();

  auto dijkStartL = std::chrono::high_resolution_clock::now();
  DijkstraResult dijkL = dijkstra(*listG, 0);
  auto dijkEndL = std::chrono::high_resolution_clock::now();

  std::cout << "Dijkstra Time -> MatrixGraph: "
            << std::chrono::duration<double, std::micro>(dijkEndM - dijkStartM).count() << " us | ListGraph: "
            << std::chrono::duration<double, std::micro>(dijkEndL - dijkStartL).count() << " us\n\n";

  // Sample paths
  std::cout << "Sample Shortest Paths from Origin [V0]:\n";
  int targets[] = {10, matrixG->vertexCount() / 2, matrixG->vertexCount() - 1};
  for (int target : targets)
  {
    if (target < matrixG->vertexCount())
    {
      std::cout << "  -> Target [" << target << "] " << matrixG->vertexLabel(target)
                << " | Shortest Distance: " << dijkL.distances[static_cast<size_t>(target)]
                << " | Path: ";
      std::vector<int> path = dijkL.getPathTo(target);
      for (size_t p = 0; p < path.size(); ++p)
      {
        if (p > 0)
        {
          std::cout << " -> ";
        }
        std::cout << matrixG->vertexLabel(path[p]);
      }
      std::cout << "\n";
    }
  }
  std::cout << "\n";
}

int main()
{
  runNavigationDemo("graph_examples/example_navigation.txt");
  runDijkstraDemo("graph_examples/example_dijkstra.txt");
  
  std::cout << "====================================================\n";
  std::cout << " DEMO: Medium-Sized Graph (10 Vertices, 14 Edges)\n";
  std::cout << "====================================================\n\n";
  runDijkstraDemo("graph_examples/medium_graph.txt");

  runLargeGraphDemo("graph_examples/large_graph.txt");
  runLargeGraphDemo("graph_examples/huge_graph.txt");

  return 0;
}