#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>

// Abstract base class that defines the common contract shared by all
// graph representations (MatrixGraph and ListGraph).
//
// The graph is created with two fixed configuration flags:
//   - isDirected:  if true, edges are one-way (origin -> destination only).
//                  If false, every inserted edge also creates the reverse
//                  edge (destination -> origin).
//   - isWeighted:  if true, the weight passed to insertEdge is stored and
//                  used. If false, all existing edges have implicit weight 1.
//
// These flags never change after the graph is created and directly affect
// the behaviour of insertEdge, removeEdge, edgeWeight and printGraph.
class Graph
{
public:
  // Constructor. isDirected and isWeighted become immutable properties
  // of the graph.
  Graph(bool isDirected, bool isWeighted);

  // Virtual destructor to allow correct polymorphic deletion.
  virtual ~Graph() = default;

  // Adds a new vertex with the given label and no associated edges.
  // Returns true on success.
  virtual bool insertVertex(std::string label) = 0;

  // Removes the vertex at the given index together with all edges that
  // arrive at or leave it. Returns false if the index is invalid.
  virtual bool removeVertex(int index) = 0;

  // Prints the graph to the console in a readable, classroom-like format.
  virtual void printGraph() = 0;

  // Inserts an edge from origin to destination (and the reverse edge,
  // if the graph is undirected). Returns false on invalid indices.
  virtual bool insertEdge(int origin, int destination, float weight = 1) = 0;

  // Removes the edge between origin and destination (and its reverse,
  // if undirected). Returns false if indices are invalid or the edge
  // does not exist.
  virtual bool removeEdge(int origin, int destination) = 0;

  // Returns true if there is an edge from origin to destination.
  virtual bool hasEdge(int origin, int destination) = 0;

  // Returns the weight of the edge between origin and destination, or a
  // sentinel value (NO_EDGE) if the edge does not exist / indices are
  // invalid. Returns 1 for any existing edge in unweighted graphs.
  virtual float edgeWeight(int origin, int destination) = 0;

  // Returns the indices of all vertices adjacent (outgoing neighbors) to
  // the given vertex. Returns an empty vector if the vertex is invalid.
  virtual std::vector<int> neighbors(int vertex) = 0;

  // Returns the label of the vertex at the given index, or an empty string
  // if the index is invalid.
  virtual std::string vertexLabel(int index) const = 0;

  // Returns the number of vertices currently in the graph.
  virtual int vertexCount() const = 0;

  // Returns whether the graph is directed.
  bool isDirected() const;

  // Returns whether the graph is weighted.
  bool isWeighted() const;

protected:
  bool isDirected_; // Directed (one-way edges) vs undirected.
  bool isWeighted_; // Weighted edges vs unweighted (implicit weight 1).
};

#endif // GRAPH_H