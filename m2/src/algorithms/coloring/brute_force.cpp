#include "brute_force.h"

#include <chrono>
#include <iostream>
#include <vector>

using namespace std;

namespace
{
  // Verifica se nenhum vizinho ja colorido possui a mesma cor
  bool corEhSegura(Graph &grafo, int verticeAtual, int corCandidata, const vector<int> &cores)
  {
    for (int vizinho : grafo.neighbors(verticeAtual))
    {
      if (cores[vizinho] == corCandidata)
      {
        return false;
      }
    }
    return true;
  }

  // Backtracking para testar se e possivel colorir com k cores
  bool buscarKColoracao(Graph &grafo, int verticeAtual, int k, vector<int> &cores)
  {
    if (verticeAtual == grafo.vertexCount())
    {
      return true;
    }

    for (int cor = 0; cor < k; ++cor)
    {
      if (corEhSegura(grafo, verticeAtual, cor, cores))
      {
        cores[verticeAtual] = cor;
        if (buscarKColoracao(grafo, verticeAtual + 1, k, cores))
        {
          return true;
        }
        cores[verticeAtual] = -1;
      }
    }
    return false;
  }

  // Verifica se o grafo tem arestas
  bool possuiArestas(Graph &grafo)
  {
    int total = grafo.vertexCount();
    for (int i = 0; i < total; ++i)
    {
      if (!grafo.neighbors(i).empty())
      {
        return true;
      }
    }
    return false;
  }
} // namespace

ResultadoColoracao coloracaoForcaBruta(Graph &grafo, int limiteVertices)
{
  ResultadoColoracao resultado;
  resultado.nomeAlgoritmo = "Forca Bruta";

  int n = grafo.vertexCount();
  if (n == 0)
  {
    resultado.viavel = true;
    resultado.quantidadeCores = 0;
    return resultado;
  }

  // Limite de seguranca (se limiteVertices <= 0, o limite esta desativado)
  if (limiteVertices > 0 && n > limiteVertices)
  {
    cerr << "[Forca Bruta] Aviso: Grafo possui " << n
         << " vertices (limite: " << limiteVertices
         << "). Abortado para evitar travamento. Passe limite <= 0 para desativar.\n";
    resultado.viavel = false;
    resultado.quantidadeCores = -1;
    return resultado;
  }

  auto inicio = chrono::high_resolution_clock::now();

  // Grafo sem arestas requer apenas 1 cor
  if (!possuiArestas(grafo))
  {
    resultado.viavel = true;
    resultado.quantidadeCores = 1;
    resultado.coresVertices.assign(n, 0);
    auto fim = chrono::high_resolution_clock::now();
    resultado.tempoExecucaoUs = chrono::duration<double, micro>(fim - inicio).count();
    return resultado;
  }

  // Testa k = 2, 3, ... ate encontrar solucao viavel
  vector<int> cores(n, -1);
  for (int k = 2; k <= n; ++k)
  {
    fill(cores.begin(), cores.end(), -1);
    if (buscarKColoracao(grafo, 0, k, cores))
    {
      resultado.viavel = true;
      resultado.quantidadeCores = k;
      resultado.coresVertices = cores;
      break;
    }
  }

  auto fim = chrono::high_resolution_clock::now();
  resultado.tempoExecucaoUs = chrono::duration<double, micro>(fim - inicio).count();

  return resultado;
}
