#include "prim.h"

#include <chrono>
#include <queue>
#include <vector>

using namespace std;

namespace
{
  // Aresta candidata na fila de prioridade
  struct ArestaCandidata
  {
    float peso;
    int origem;
    int destino;

    bool operator>(const ArestaCandidata &outra) const
    {
      return peso > outra.peso;
    }
  };
} // namespace

ResultadoAGM agmPrim(Graph &grafo, int verticeInicial)
{
  ResultadoAGM resultado;
  resultado.nomeAlgoritmo = "Prim";

  int n = grafo.vertexCount();
  if (n == 0)
  {
    resultado.viavel = true;
    return resultado;
  }

  if (verticeInicial < 0 || verticeInicial >= n)
  {
    verticeInicial = 0;
  }

  auto inicio = chrono::high_resolution_clock::now();

  // Controle Q: true indica que o vertice ainda pertence a Q
  vector<bool> pertenceAoConjuntoQ(n, true);

  // Remove vertice inicial de Q
  pertenceAoConjuntoQ[verticeInicial] = false;
  int verticesRestantesEmQ = n - 1;

  // Min-Heap com as arestas que cruzam o corte
  priority_queue<ArestaCandidata, vector<ArestaCandidata>, greater<ArestaCandidata>> filaPrioridade;

  for (int vizinho : grafo.neighbors(verticeInicial))
  {
    float peso = grafo.edgeWeight(verticeInicial, vizinho);
    filaPrioridade.push({peso, verticeInicial, vizinho});
  }

  // Enquanto Q nao estiver vazio
  while (verticesRestantesEmQ > 0 && !filaPrioridade.empty())
  {
    ArestaCandidata menorAresta = filaPrioridade.top();
    filaPrioridade.pop();

    int u = menorAresta.origem;
    int v = menorAresta.destino;

    if (!pertenceAoConjuntoQ[v]) continue;

    // Adiciona aresta a solucao S e remove v de Q
    resultado.arestas.push_back({u, v, menorAresta.peso});
    resultado.pesoTotal += menorAresta.peso;
    pertenceAoConjuntoQ[v] = false;
    --verticesRestantesEmQ;

    // Adiciona novas arestas de v para vertices em Q
    for (int vizinho : grafo.neighbors(v))
    {
      if (pertenceAoConjuntoQ[vizinho])
      {
        float peso = grafo.edgeWeight(v, vizinho);
        filaPrioridade.push({peso, v, vizinho});
      }
    }
  }

  auto fim = chrono::high_resolution_clock::now();
  resultado.tempoExecucaoUs = chrono::duration<double, micro>(fim - inicio).count();
  resultado.viavel = (verticesRestantesEmQ == 0);

  return resultado;
}
