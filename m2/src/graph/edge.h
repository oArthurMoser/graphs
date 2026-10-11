#ifndef EDGE_H
#define EDGE_H

using namespace std;

// Representa uma aresta saindo de um vertice em uma lista de adjacencia
struct Edge
{
  int destination; // Indice do vertice destino
  float weight;    // Peso da aresta (1 para grafos nao ponderados)
};

// Alias em Portugues
using Aresta = Edge;

#endif // EDGE_H