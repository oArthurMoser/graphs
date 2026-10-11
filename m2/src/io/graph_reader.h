#ifndef GRAPH_READER_H
#define GRAPH_READER_H

#include <memory>
#include <string>

#include "graph/graph.h"
#include "graph/list_graph.h"
#include "graph/matrix_graph.h"

using namespace std;

// Cabecalho de metadados lido da primeira linha do arquivo (V A D P)
struct GraphFileInfo
{
  int vertexCount = 0;
  int edgeCount = 0;
  bool isDirected = false;
  bool isWeighted = false;
};

using InformacoesArquivoGrafo = GraphFileInfo;

class GraphReader
{
public:
  static bool readFileInfo(const string &filePath, GraphFileInfo &info);
  static bool populateGraph(const string &filePath, Graph &graph);
  static unique_ptr<MatrixGraph> readMatrixGraph(const string &filePath);
  static unique_ptr<ListGraph> readListGraph(const string &filePath);

  // Aliases em Portugues
  static bool lerInformacoesArquivo(const string &caminhoArquivo, GraphFileInfo &info)
  {
    return readFileInfo(caminhoArquivo, info);
  }

  static bool preencherGrafo(const string &caminhoArquivo, Graph &grafo)
  {
    return populateGraph(caminhoArquivo, grafo);
  }

  static unique_ptr<MatrixGraph> lerMatrixGraph(const string &caminhoArquivo)
  {
    return readMatrixGraph(caminhoArquivo);
  }

  static unique_ptr<ListGraph> lerListGraph(const string &caminhoArquivo)
  {
    return readListGraph(caminhoArquivo);
  }
};

using LeitorGrafo = GraphReader;

#endif // GRAPH_READER_H
