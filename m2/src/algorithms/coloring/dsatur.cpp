#include "dsatur.h"

#include <algorithm>
#include <chrono>
#include <unordered_set>
#include <vector>

using namespace std;

ResultadoColoracao coloracaoDsatur(Graph &grafo)
{
  ResultadoColoracao resultado;
  resultado.nomeAlgoritmo = "DSATUR";

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

  // Passo 1: Ordenar os vertices pelo seu grau em ordem decrescente
  vector<pair<int, int>> grausVertices(n); // {grau, vertice}
  for (int i = 0; i < n; ++i)
  {
    grausVertices[i] = {static_cast<int>(listaAdjacencia[i].size()), i};
  }

  sort(grausVertices.begin(), grausVertices.end(), [](const auto &a, const auto &b) {
    if (a.first != b.first) return a.first > b.first; // Maior grau primeiro
    return a.second < b.second;                       // Desempate pelo menor indice
  });

  // Passo 2: Criar vetor de cores e inicializar todos como "sem cor" (-1)
  vector<int> cores(n, -1);

  // Rastreia cores distintas nos vizinhos de cada vertice (grau de saturacao)
  vector<unordered_set<int>> coresVizinhas(n);

  // Passo 3: Colorir o vertice com maior grau com a primeira cor (0)
  int primeiroVertice = grausVertices[0].second;
  cores[primeiroVertice] = 0;

  // Atualiza a saturacao dos vizinhos do primeiro vertice colorido
  for (int vizinho : listaAdjacencia[primeiroVertice])
  {
    coresVizinhas[vizinho].insert(0);
  }

  int verticesColoridos = 1;
  vector<int> corVisitada(n + 2, -1);

  // Passo 4: Enquanto existir vertice sem cor no grafo
  while (verticesColoridos < n)
  {
    // Selecionar o vertice com maior grau de saturacao.
    // Em caso de empate, escolher o com maior grau dentre os de maior saturacao.
    int melhorVertice = -1;
    int maiorSaturacao = -1;
    int maiorGrau = -1;

    for (const auto &item : grausVertices)
    {
      int vertice = item.second;
      if (cores[vertice] != -1) continue; // Ja colorido

      int saturacao = static_cast<int>(coresVizinhas[vertice].size());
      int grau = item.first;

      if (saturacao > maiorSaturacao || (saturacao == maiorSaturacao && grau > maiorGrau))
      {
        maiorSaturacao = saturacao;
        maiorGrau = grau;
        melhorVertice = vertice;
      }
    }

    if (melhorVertice == -1) break;

    // Passo 5: Atribuir a primeira cor que nao esteja em um vertice adjacente
    for (int vizinho : listaAdjacencia[melhorVertice])
    {
      int c = cores[vizinho];
      if (c >= 0 && c < static_cast<int>(corVisitada.size()))
      {
        corVisitada[c] = melhorVertice;
      }
    }

    int corEscolhida = 0;
    while (corEscolhida < static_cast<int>(corVisitada.size()) && corVisitada[corEscolhida] == melhorVertice)
    {
      ++corEscolhida;
    }

    cores[melhorVertice] = corEscolhida;
    ++verticesColoridos;

    // Atualiza o grau de saturacao dos vizinhos
    for (int vizinho : listaAdjacencia[melhorVertice])
    {
      if (cores[vizinho] == -1)
      {
        coresVizinhas[vizinho].insert(corEscolhida);
      }
    }
  }

  // Passo 6: Medir tempo de execucao e preencher o resultado
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
