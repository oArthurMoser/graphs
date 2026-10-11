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

  // Cache das listas de adjacencia e graus
  vector<vector<int>> listaAdjacencia(n);
  vector<int> graus(n);
  for (int i = 0; i < n; ++i)
  {
    listaAdjacencia[i] = grafo.neighbors(i);
    graus[i] = static_cast<int>(listaAdjacencia[i].size());
  }

  // 1. Identifica o vertice com maior grau
  int verticeMaiorGrau = 0;
  for (int i = 1; i < n; ++i)
  {
    if (graus[i] > graus[verticeMaiorGrau])
    {
      verticeMaiorGrau = i;
    }
  }

  // 2. Colore o vertice de maior grau com a primeira cor (0)
  vector<int> cores(n, -1);
  cores[verticeMaiorGrau] = 0;

  // Rastreia cores distintas nos vizinhos de cada vertice (grau de saturacao)
  vector<unordered_set<int>> coresVizinhas(n);
  for (int vizinho : listaAdjacencia[verticeMaiorGrau])
  {
    coresVizinhas[vizinho].insert(0);
  }

  int verticesColoridos = 1;
  vector<int> corVisitada(n + 2, -1);

  // 3. Enquanto houver vertices sem cor
  while (verticesColoridos < n)
  {
    // Seleciona vertice com maior saturacao (desempate por maior grau)
    int melhorVertice = -1;
    int maiorSaturacao = -1;
    int maiorGrau = -1;

    for (int i = 0; i < n; ++i) // Itera sobre todos os vertices
    {
      if (cores[i] != -1) continue; // Ja colorido

      int saturacao = static_cast<int>(coresVizinhas[i].size()); // atribui o grau de saturacao do vertice i
      int grau = graus[i];

      if (saturacao > maiorSaturacao || (saturacao == maiorSaturacao && grau > maiorGrau))
      {
        maiorSaturacao = saturacao;
        maiorGrau = grau;
        melhorVertice = i;
      }
    }

    if (melhorVertice == -1) break;

    // Atribui a menor cor livre que vizinhos nao possuem
    for (int vizinho : listaAdjacencia[melhorVertice]) // Itera sobre os vizinhos do vertice selecionado
    {
      int c = cores[vizinho]; // Pega a cor do vizinho
      if (c >= 0 && c < static_cast<int>(corVisitada.size())) // Marca a cor como visitada para o vertice selecionado
      {
        corVisitada[c] = melhorVertice;
      }
    }

    int corEscolhida = 0;
    while (corEscolhida < static_cast<int>(corVisitada.size()) && corVisitada[corEscolhida] == melhorVertice) // Encontra a menor cor livre
    {
      ++corEscolhida;
    }

    cores[melhorVertice] = corEscolhida; // Atribui a cor escolhida ao vertice selecionado
    ++verticesColoridos;

    // Atualiza a saturacao dos vizinhos
    for (int vizinho : listaAdjacencia[melhorVertice])
    {
      if (cores[vizinho] == -1)
      {
        coresVizinhas[vizinho].insert(corEscolhida); // Marca a cor escolhida como vizinha do vizinho
      }
    }
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
