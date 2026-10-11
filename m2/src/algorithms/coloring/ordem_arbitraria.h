#ifndef ORDEM_ARBITRARIA_H
#define ORDEM_ARBITRARIA_H

#include "graph/graph.h"
#include "coloring_result.h"

using namespace std;

// Colora os vertices na ordem natural (0..V-1) escolhendo a primeira cor livre
ResultadoColoracao coloracaoOrdemArbitraria(Graph &grafo);

#endif // ORDEM_ARBITRARIA_H
