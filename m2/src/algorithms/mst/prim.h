#ifndef PRIM_H
#define PRIM_H

#include "graph/graph.h"
#include "mst_result.h"

using namespace std;

// Algoritmo de Prim para Arvore Geradora Minima (AGM)
ResultadoAGM agmPrim(Graph &grafo, int verticeInicial = 0);

#endif // PRIM_H
