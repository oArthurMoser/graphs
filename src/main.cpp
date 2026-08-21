#include <iostream>

#include "graph/list_graph.h"
#include "graph/matrix_graph.h"
#include "random/create.h"

int main()
{
  ListGraph lineGraph(true, false);
  faker(lineGraph);
  lineGraph.printGraph();

  std::cout << "\n----------------------------------------\n\n";

  MatrixGraph matrixGraph(true, false);
  faker(matrixGraph);
  matrixGraph.printGraph();

  return 0;
}