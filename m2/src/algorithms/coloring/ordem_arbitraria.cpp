#include "ordem_arbitraria.h"

#include <chrono>
#include <vector>

using namespace std;

ResultadoColoracao coloracaoOrdemArbitraria(Graph &grafo)
{
  ResultadoColoracao resultado;
  resultado.nomeAlgoritmo = "Sem Criterio de Ordem";

  int n = grafo.vertexCount();
  if (n == 0)
  {
    resultado.viavel = true;
    return resultado;
  }

  auto inicio = chrono::high_resolution_clock::now();

  vector<vector<int>> listaAdjacencia(n);
  for (int i = 0; i < n; ++i)
  {
    listaAdjacencia[i] = grafo.neighbors(i);
  }

  vector<int> cores(n, -1);
  vector<int> corVisitada(n + 2, -1);

  // Percorre os vertices na ordem arbitraria (0 ate n - 1)
  for (int vertice = 0; vertice < n; ++vertice)
  {
    // Marca cores usadas pelos vizinhos
    for (int vizinho : listaAdjacencia[vertice])
    {
      int cor = cores[vizinho];
      if (cor >= 0 && cor < static_cast<int>(corVisitada.size()))
      {
        corVisitada[cor] = vertice;
      }
    }

    // Pega a primeira cor disponivel
    int primeiraDisponivel = 0;
    while (primeiraDisponivel < static_cast<int>(corVisitada.size()) && corVisitada[primeiraDisponivel] == vertice)
    {
      ++primeiraDisponivel;
    }

    cores[vertice] = primeiraDisponivel;
  }

  auto fim = chrono::high_resolution_clock::now();
  resultado.tempoExecucaoUs = chrono::duration<double, micro>(fim - inicio).count();
  resultado.viavel = true;

  int maxCor = -1;
  for (int c : cores)
  {
    if (c > maxCor) maxCor = c;
  }
  resultado.quantidadeCores = maxCor + 1;
  resultado.coresVertices = cores;

  return resultado;
}
