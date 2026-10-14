#include "kruskal.h"

#include <algorithm>
#include <chrono>
#include <vector>

using namespace std;

namespace
{
  // Union-Find para gerenciar a floresta F
  class FlorestaConjuntosDisjuntos
  {
  public:
    explicit FlorestaConjuntosDisjuntos(int totalVertices)
        : pai(totalVertices), rank(totalVertices, 0), totalArvores(totalVertices)
    {
      for (int i = 0; i < totalVertices; ++i)
      {
        pai[i] = i;
      }
    }

    int encontrar(int i)
    {
      if (pai[i] == i) return i;
      return pai[i] = encontrar(pai[i]); // Compressao de caminhos
    }

    bool unir(int i, int j)
    {
      int raizI = encontrar(i);
      int raizJ = encontrar(j);
      if (raizI == raizJ) return false; // Mesma arvore: formaria ciclo

      if (rank[raizI] < rank[raizJ])
      {
        pai[raizI] = raizJ;
      }
      else if (rank[raizI] > rank[raizJ])
      {
        pai[raizJ] = raizI;
      }
      else
      {
        pai[raizJ] = raizI;
        ++rank[raizI];
      }
      --totalArvores;
      return true;
    }

    int quantidadeArvores() const
    {
      return totalArvores;
    }

  private:
    vector<int> pai;
    vector<int> rank;
    int totalArvores;
  };
} // namespace

ResultadoAGM agmKruskal(Graph &grafo)
{
  ResultadoAGM resultado;
  resultado.nomeAlgoritmo = "Kruskal";

  int n = grafo.vertexCount();
  if (n <= 1)
  {
    resultado.viavel = true;
    return resultado;
  }

  auto inicio = chrono::high_resolution_clock::now();

  // Passo 1: Coleta todas as arestas unicas (u < v) para o conjunto de controle Q
  vector<ArestaAGM> conjuntoControleQ;
  for (int u = 0; u < n; ++u)
  {
    for (int v : grafo.neighbors(u))
    {
      if (u < v)
      {
        float peso = grafo.edgeWeight(u, v);
        conjuntoControleQ.push_back({u, v, peso});
      }
    }
  }

  // Passo 2: Ordenar as arestas por peso crescente
  sort(conjuntoControleQ.begin(), conjuntoControleQ.end(), [](const ArestaAGM &a, const ArestaAGM &b) {
    if (a.peso != b.peso) return a.peso < b.peso;
    if (a.u != b.u) return a.u < b.u;
    return a.v < b.v;
  });

  // Passo 3: Inicializar floresta F com cada vertice em sua propria arvore isolada
  FlorestaConjuntosDisjuntos florestaF(n);

  // Passo 4: Selecionar a menor aresta que une arvores diferentes (evita ciclo)
  for (const auto &aresta : conjuntoControleQ)
  {
    if (florestaF.encontrar(aresta.u) != florestaF.encontrar(aresta.v))
    {
      resultado.arestas.push_back(aresta);
      resultado.pesoTotal += aresta.peso;
      florestaF.unir(aresta.u, aresta.v);

      if (florestaF.quantidadeArvores() == 1) break; // Todas conectadas
    }
  }

  // Passo 5: Medir tempo de execucao e preencher o resultado
  auto fim = chrono::high_resolution_clock::now();
  resultado.tempoExecucaoUs = chrono::duration<double, micro>(fim - inicio).count();
  resultado.viavel = (florestaF.quantidadeArvores() == 1);

  return resultado;
}
