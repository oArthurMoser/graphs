#ifndef GRAPH_READER_H
#define GRAPH_READER_H

#include <memory>
#include <string>

#include "graph/graph.h"
#include "graph/list_graph.h"
#include "graph/matrix_graph.h"

// Metadata header read from the first line of a graph text file.
struct GraphFileInfo
{
  int vertexCount = 0;
  int edgeCount = 0;
  bool isDirected = false;
  bool isWeighted = false;
};

class GraphReader
{
public:
  // Reads only the first line of the file (metadata: V A D P).
  // Returns true on success, false if file cannot be opened or parsed.
  static bool readFileInfo(const std::string &filePath, GraphFileInfo &info);

  // Populates an existing Graph instance with vertices and edges read from
  // the file.
  // Returns true on success, false otherwise.
  static bool populateGraph(const std::string &filePath, Graph &graph);

  // Factory methods to create and return a fully populated Graph instance.
  static std::unique_ptr<MatrixGraph> readMatrixGraph(const std::string &filePath);
  static std::unique_ptr<ListGraph> readListGraph(const std::string &filePath);
};

#endif // GRAPH_READER_H
