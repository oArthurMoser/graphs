#include "welsh_powell.h"

#include <algorithm>
#include <chrono>
#include <vector>

using namespace std;

ResultadoColoracao coloracaoWelshPowell(Graph &grafo)
{
  ResultadoColoracao resultado;
  resultado.nomeAlgoritmo = "Welsh & Powell";

  int n = grafo.vertexCount();
  if (n == 0)
  {
    resultado.viavel = true;
    return resultado;
  }

  auto inicio = chrono::high_resolution_clock::now();

  // Cache das listas de adjacencia
  vector<vector<int>> listaAdjacencia(n);
  for (int i = 0; i < n; ++i)
  {
    listaAdjacencia[i] = grafo.neighbors(i);
  }

  // 1. Ordena os vertices por grau em ordem decrescente
  vector<pair<int, int>> grausVertices(n); // (grau, vertice)
  for (int i = 0; i < n; ++i)
  {
    grausVertices[i] = {static_cast<int>(listaAdjacencia[i].size()), i};
  }

  sort(grausVertices.begin(), grausVertices.end(), [](const auto &a, const auto &b) {
    if (a.first != b.first) return a.first > b.first;
    return a.second < b.second;
  });

  // 2. Inicializa todos os vertices como sem cor (-1)
  vector<int> cores(n, -1);
  int verticesSemCor = n;
  int corAtual = 0;

  // 3. Enquanto houver vertice sem cor, colore com corAtual os nao vizinhos
  while (verticesSemCor > 0)
  {
    for (const auto &item : grausVertices)
    {
      int vertice = item.second;
      if (cores[vertice] != -1) continue;

      bool conflito = false;
      for (int vizinho : listaAdjacencia[vertice])
      {
        if (cores[vizinho] == corAtual)
        {
          conflito = true;
          break;
        }
      }

      if (!conflito)
      {
        cores[vertice] = corAtual;
        --verticesSemCor;
      }
    }
    ++corAtual;
  }

  auto fim = chrono::high_resolution_clock::now();
  resultado.tempoExecucaoUs = chrono::duration<double, micro>(fim - inicio).count();
  resultado.viavel = true;
  resultado.quantidadeCores = corAtual;
  resultado.coresVertices = cores;

  return resultado;
}
