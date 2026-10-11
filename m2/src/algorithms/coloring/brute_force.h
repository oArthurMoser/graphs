#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

#include "graph/graph.h"
#include "coloring_result.h"

using namespace std;

// Forca Bruta: testa k = 2, 3, ... ate encontrar coloracao viavel.
// limiteVertices: maximo de vertices permitido (padrao: 20).
// Passe limiteVertices <= 0 para desativar o limite de seguranca.
ResultadoColoracao coloracaoForcaBruta(Graph &grafo, int limiteVertices = 20);

#endif // BRUTE_FORCE_H
