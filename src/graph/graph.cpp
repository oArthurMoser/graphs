#include "graph.h"

Graph::Graph(bool isDirected, bool isWeighted)
    : isDirected_(isDirected), isWeighted_(isWeighted) {}

bool Graph::isDirected() const {
    return isDirected_;
}

bool Graph::isWeighted() const {
    return isWeighted_;
}