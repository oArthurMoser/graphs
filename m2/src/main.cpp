#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "algorithms/coloring/brute_force.h"
#include "algorithms/coloring/dsatur.h"
#include "algorithms/coloring/ordem_arbitraria.h"
#include "algorithms/coloring/welsh_powell.h"
#include "algorithms/mst/kruskal.h"
#include "algorithms/mst/prim.h"
#include "graph/list_graph.h"
#include "graph/matrix_graph.h"
#include "io/graph_reader.h"

using namespace std;

// Retorna os rotulos ("A", "B", etc.) dos vertices para exibicao
vector<string> obterRotulosVertices(Graph &grafo)
{
  int n = grafo.vertexCount();
  vector<string> rotulos(n);
  for (int i = 0; i < n; ++i)
  {
    rotulos[i] = grafo.vertexLabel(i);
  }
  return rotulos;
}

// Executa os 4 algoritmos de coloracao no arquivo especificado.
// limiteForcaBruta: limite maximo de vertices (padrao: 20). Passe 0 para desativar.
void executarBateriaColoracao(const string &caminhoArquivo,
                              bool exibirLista = false,
                              bool exibirMatriz = false,
                              int limiteForcaBruta = 20)
{
  cout << "======================================================================\n";
  cout << " PARTE 1 - COLORACAO DE GRAFOS\n";
  cout << " Arquivo: " << caminhoArquivo << "\n";
  cout << "======================================================================\n";

  unique_ptr<ListGraph> grafo = GraphReader::readListGraph(caminhoArquivo);
  if (!grafo)
  {
    cerr << "Erro ao carregar o grafo: " << caminhoArquivo << "\n\n";
    return;
  }

  if (exibirMatriz)
  {
    unique_ptr<MatrixGraph> grafoMatriz = GraphReader::readMatrixGraph(caminhoArquivo);
    if (grafoMatriz)
    {
      cout << "--- Matriz de Adjacencia ---\n";
      grafoMatriz->printGraph();
      cout << "\n";
    }
  }

  if (exibirLista)
  {
    cout << "--- Lista de Adjacencia ---\n";
    grafo->printGraph();
    cout << "\n";
  }

  cout << "Vertices: " << grafo->vertexCount() << " | ";
  int totalArestas = 0;
  for (int i = 0; i < grafo->vertexCount(); ++i)
  {
    totalArestas += grafo->neighbors(i).size();
  }
  cout << "Arestas (bidirecionais): " << (totalArestas / 2) << "\n\n";

  vector<string> rotulos = obterRotulosVertices(*grafo);

  // 1. Forca Bruta
  ResultadoColoracao fb = coloracaoForcaBruta(*grafo, limiteForcaBruta);
  if (fb.viavel)
  {
    fb.imprimirResultado(rotulos);
  }
  else
  {
    cout << "[Forca Bruta]\n";
    cout << "  - Status: Nao executada (grafo com " << grafo->vertexCount()
         << " vertices excede o limite de seguranca de " << limiteForcaBruta << ")\n";
  }
  cout << "\n";

  // 2. Welsh & Powell
  ResultadoColoracao wp = coloracaoWelshPowell(*grafo);
  wp.imprimirResultado(rotulos);
  cout << "\n";

  // 3. DSATUR
  ResultadoColoracao ds = coloracaoDsatur(*grafo);
  ds.imprimirResultado(rotulos);
  cout << "\n";

  // 4. Sem Criterio de Ordem (Ordem Arbitraria)
  ResultadoColoracao oa = coloracaoOrdemArbitraria(*grafo);
  oa.imprimirResultado(rotulos);
  cout << "\n";
}

// Executa os 2 algoritmos de Arvore Geradora Minima (Prim e Kruskal)
void executarBateriaAGM(const string &caminhoArquivo,
                        bool exibirLista = false,
                        bool exibirMatriz = false)
{
  cout << "======================================================================\n";
  cout << " PARTE 2 - ARVORE GERADORA MINIMA (AGM)\n";
  cout << " Arquivo: " << caminhoArquivo << "\n";
  cout << "======================================================================\n";

  unique_ptr<ListGraph> grafo = GraphReader::readListGraph(caminhoArquivo);
  if (!grafo)
  {
    cerr << "Erro ao carregar o grafo: " << caminhoArquivo << "\n\n";
    return;
  }

  if (exibirMatriz)
  {
    unique_ptr<MatrixGraph> grafoMatriz = GraphReader::readMatrixGraph(caminhoArquivo);
    if (grafoMatriz)
    {
      cout << "--- Matriz de Adjacencia ---\n";
      grafoMatriz->printGraph();
      cout << "\n";
    }
  }

  if (exibirLista)
  {
    cout << "--- Lista de Adjacencia ---\n";
    grafo->printGraph();
    cout << "\n";
  }

  cout << "Vertices: " << grafo->vertexCount() << " | ";
  int totalArestas = 0;
  for (int i = 0; i < grafo->vertexCount(); ++i)
  {
    totalArestas += grafo->neighbors(i).size();
  }
  cout << "Arestas: " << (totalArestas / 2) << "\n\n";

  vector<string> rotulos = obterRotulosVertices(*grafo);

  // 1. Prim
  ResultadoAGM primRes = agmPrim(*grafo, 0);
  primRes.imprimirResultado(rotulos);
  cout << "\n";

  // 2. Kruskal
  ResultadoAGM kruskalRes = agmKruskal(*grafo);
  kruskalRes.imprimirResultado(rotulos);
  cout << "\n";
}

int main(int argc, char *argv[])
{
  // Permite passar arquivo diretamente por parametro: ./build/main <arquivo.txt>
  if (argc > 1)
  {
    string arquivo = argv[1];
    GraphFileInfo info;
    if (GraphReader::readFileInfo(arquivo, info))
    {
      if (info.isWeighted)
      {
        executarBateriaAGM(arquivo, false, false);
      }
      else
      {
        executarBateriaColoracao(arquivo, false, false, 20);
      }
      return 0;
    }
  }

  cout << "######################################################################\n";
  cout << "                      TRABALHO M2 - GRAFOS\n";
  cout << "######################################################################\n\n";

  // ================= PARTE 1: COLORAÇÃO =================
  // Parametros: caminho, exibirLista (0 ou 1), exibirMatriz (0 ou 1), limiteForcaBruta (padrao 20, 0 desativa)
  executarBateriaColoracao("graph_examples/coloring_s08_house.txt", true, true, 20);

  // executarBateriaColoracao("graph_examples/coloring_s08_welsh.txt", false, false, 20);
  // executarBateriaColoracao("graph_examples/coloring_cycle5.txt", false, false, 20);
  // executarBateriaColoracao("graph_examples/coloring_bipartite.txt", false, false, 20);
  // executarBateriaColoracao("graph_examples/coloring_petersen.txt", false, false, 20);
  // executarBateriaColoracao("graph_examples/coloring_medium.txt", false, false, 20);
  // executarBateriaColoracao("graph_examples/coloring_large.txt", false, false, 20);
  // executarBateriaColoracao("graph_examples/coloring_huge.txt", false, false, 20);

  // ================= PARTE 2: ÁRVORE GERADORA MÍNIMA =================
  // Parametros: caminho, exibirLista (0 ou 1), exibirMatriz (0 ou 1)
  executarBateriaAGM("graph_examples/mst_s09_slide.txt", false, false);
  // executarBateriaAGM("graph_examples/mst_s09_exercise.txt", false, false);
  // executarBateriaAGM("graph_examples/mst_medium.txt", false, false);
  // executarBateriaAGM("graph_examples/mst_large.txt", false, false);
  // executarBateriaAGM("graph_examples/mst_huge.txt", false, false);

  cout << "######################################################################\n";
  cout << "                 FIM DA EXECUCAO DO TRABALHO M2\n";
  cout << "######################################################################\n";

  return 0;
}
