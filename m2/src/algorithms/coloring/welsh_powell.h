#ifndef WELSH_POWELL_H
#define WELSH_POWELL_H

#include "graph/graph.h"
#include "coloring_result.h"

using namespace std;

// Welsh & Powell: ordena vertices por grau decrescente e atribui uma cor por rodada
ResultadoColoracao coloracaoWelshPowell(Graph &grafo);

#endif // WELSH_POWELL_H
