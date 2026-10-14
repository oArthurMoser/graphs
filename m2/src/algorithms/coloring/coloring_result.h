#ifndef COLORING_RESULT_H
#define COLORING_RESULT_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Estrutura que armazena o resultado da execucao de um algoritmo de coloracao
struct ResultadoColoracao
{
  string nomeAlgoritmo;
  int quantidadeCores = 0;       // Numero de cores utilizadas (numero cromatico ou estimativa)
  vector<int> coresVertices;     // Indice i -> cor atribuida ao vertice i (0, 1, 2, ...)
  double tempoExecucaoUs = 0.0;  // Tempo de execucao em microssegundos
  bool viavel = false;           // Verdadeiro se a coloracao for valida (sem vizinhos com mesma cor)

  // Exibe o resultado formatado no console conforme o enunciado
  void imprimirResultado(const vector<string> &rotulos) const
  {
    cout << "[" << nomeAlgoritmo << "]\n";
    if (!viavel)
    {
      cout << "  - Status: Nao executado / Inviavel\n";
      return;
    }

    cout << "  - Tempo de execucao: " << tempoExecucaoUs << " us ("
         << (tempoExecucaoUs / 1000.0) << " ms)\n";
    cout << "  - Numero de cores utilizadas: " << quantidadeCores << "\n";

    // Requisito do enunciado: Para os grafos pequenos (menos de 10 vertices)
    // tambem devera ser exibida uma lista com os vertices e as cores correspondentes.
    if (coresVertices.size() < 10)
    {
      cout << "  - Vertices e cores correspondentes:\n";
      for (size_t i = 0; i < coresVertices.size(); ++i)
      {
        string rotulo = (i < rotulos.size() && !rotulos[i].empty()) ? rotulos[i] : to_string(i);
        cout << "      Vertice " << rotulo << " -> Cor " << coresVertices[i] << "\n";
      }
    }
  }

  // Metodo auxiliar para manter compatibilidade
  void printResult(const vector<string> &rotulos) const
  {
    imprimirResultado(rotulos);
  }
};

// Alias para compatibilidade
using ColoringResult = ResultadoColoracao;

#endif // COLORING_RESULT_H
