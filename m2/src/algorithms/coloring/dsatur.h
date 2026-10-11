#ifndef DSATUR_H
#define DSATUR_H

#include "graph/graph.h"
#include "coloring_result.h"

using namespace std;

// DSATUR: escolhe a cada passo o vertice com maior grau de saturacao
ResultadoColoracao coloracaoDsatur(Graph &grafo);

#endif // DSATUR_H
