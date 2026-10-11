#ifndef MST_RESULT_H
#define MST_RESULT_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Representa uma aresta da AGM
struct ArestaAGM
{
  int u;
  int v;
  float peso;
};

// Resultado dos algoritmos de Arvore Geradora Minima
struct ResultadoAGM
{
  string nomeAlgoritmo;
  float pesoTotal = 0.0f;
  vector<ArestaAGM> arestas;
  double tempoExecucaoUs = 0.0;
  bool viavel = false;

  void imprimirResultado(const vector<string> &rotulos) const
  {
    cout << "[" << nomeAlgoritmo << "]\n";
    cout << "  - Status: " << (viavel ? "AGM gerada com sucesso" : "Grafo desconexo / Falha") << "\n";
    cout << "  - Soma dos pesos das arestas (Custo Total): " << pesoTotal << "\n";
    cout << "  - Arestas na AGM: " << arestas.size() << "\n";
    cout << "  - Tempo de execucao: " << tempoExecucaoUs << " us (" << (tempoExecucaoUs / 1000.0) << " ms)\n";

    if (rotulos.size() <= 10 && viavel)
    {
      cout << "  - Arestas selecionadas:\n";
      for (const auto &aresta : arestas)
      {
        string rotuloU = (aresta.u < static_cast<int>(rotulos.size())) ? rotulos[aresta.u] : to_string(aresta.u);
        string rotuloV = (aresta.v < static_cast<int>(rotulos.size())) ? rotulos[aresta.v] : to_string(aresta.v);
        cout << "      {" << rotuloU << ", " << rotuloV << "} [peso: " << aresta.peso << "]\n";
      }
    }
  }
};

#endif // MST_RESULT_H
