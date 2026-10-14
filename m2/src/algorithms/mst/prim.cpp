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

  // Passo 1: Iniciar conjunto de controle Q e remover o vertice inicial
  vector<bool> pertenceAoConjuntoQ(n, true);
  pertenceAoConjuntoQ[verticeInicial] = false;
  int verticesRestantesEmQ = n - 1;

  // Passo 2: Iniciar fila de prioridade com as arestas que cruzam o corte a partir do vertice inicial
  priority_queue<ArestaCandidata, vector<ArestaCandidata>, greater<ArestaCandidata>> filaPrioridade;
  for (int vizinho : grafo.neighbors(verticeInicial))
  {
    float peso = grafo.edgeWeight(verticeInicial, vizinho);
    filaPrioridade.push({peso, verticeInicial, vizinho});
  }

  // Passo 3: Enquanto Q nao estiver vazio e houver arestas disponiveis
  while (verticesRestantesEmQ > 0 && !filaPrioridade.empty())
  {
    ArestaCandidata menorAresta = filaPrioridade.top();
    filaPrioridade.pop();

    int u = menorAresta.origem;
    int v = menorAresta.destino;

    if (!pertenceAoConjuntoQ[v]) continue;

    // Passo 4: Adicionar aresta a solucao S e remover v de Q
    resultado.arestas.push_back({u, v, menorAresta.peso});
    resultado.pesoTotal += menorAresta.peso;
    pertenceAoConjuntoQ[v] = false;
    --verticesRestantesEmQ;

    // Passo 5: Adicionar novas arestas de v para os vertices que ainda estao em Q
    for (int vizinho : grafo.neighbors(v))
    {
      if (pertenceAoConjuntoQ[vizinho])
      {
        float peso = grafo.edgeWeight(v, vizinho);
        filaPrioridade.push({peso, v, vizinho});
      }
    }
  }

  // Passo 6: Medir tempo de execucao e preencher o resultado
  auto fim = chrono::high_resolution_clock::now();
  resultado.tempoExecucaoUs = chrono::duration<double, micro>(fim - inicio).count();
  resultado.viavel = (verticesRestantesEmQ == 0);

  return resultado;
}
