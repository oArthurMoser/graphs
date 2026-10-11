#ifndef EDGE_H
#define EDGE_H

// Represents a single edge leaving a vertex in an adjacency list.
// Used by ListGraph to store the destination and the weight of the edge.
struct Edge
{
  int destination; // Index of the destination vertex.
  float weight;    // Weight of the edge (always 1 for unweighted graphs).
};

#endif // EDGE_H