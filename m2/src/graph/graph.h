#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>

using namespace std;

// Classe base abstrata que define o contrato compartilhado por todas as
// representacoes de grafo (MatrixGraph e ListGraph).
class Graph
{
public:
  Graph(bool isDirected, bool isWeighted);
  virtual ~Graph() = default;

  virtual bool insertVertex(string label) = 0;
  virtual bool removeVertex(int index) = 0;
  virtual void printGraph() = 0;
  virtual bool insertEdge(int origin, int destination, float weight = 1) = 0;
  virtual bool removeEdge(int origin, int destination) = 0;
  virtual bool hasEdge(int origin, int destination) = 0;
  virtual float edgeWeight(int origin, int destination) = 0;
  virtual vector<int> neighbors(int vertex) = 0;
  virtual string vertexLabel(int index) const = 0;
  virtual int vertexCount() const = 0;

  bool isDirected() const;
  bool isWeighted() const;

  // Aliases em Portugues para facil compreensao e utilizacao
  bool inserirVertice(string rotulo) { return insertVertex(rotulo); }
  bool removerVertice(int indice) { return removeVertex(indice); }
  void imprimirGrafo() { printGraph(); }
  bool inserirAresta(int origem, int destino, float peso = 1) { return insertEdge(origem, destino, peso); }
  bool removerAresta(int origem, int destino) { return removeEdge(origem, destino); }
  bool possuiAresta(int origem, int destino) { return hasEdge(origem, destino); }
  float pesoAresta(int origem, int destino) { return edgeWeight(origem, destino); }
  vector<int> vizinhos(int vertice) { return neighbors(vertice); }
  string rotuloVertice(int indice) const { return vertexLabel(indice); }
  int quantidadeVertices() const { return vertexCount(); }
  bool ehDirecionado() const { return isDirected(); }
  bool ehPonderado() const { return isWeighted(); }

protected:
  bool isDirected_;
  bool isWeighted_;
};

#endif // GRAPH_H