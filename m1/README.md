# Graph Library & Algorithms (Parts 1 & 2)

Academic graph library in C++17 implementing graph data structures, file loading, search algorithms (BFS & DFS), shortest path computation (Dijkstra), and runtime performance comparisons between graph representations.

Implemented using only modern standard C++ (C++17) and the STL, supporting both:

- **`MatrixGraph`** — adjacency matrix (`N x N`), edge queries in $O(1)$.
- **`ListGraph`** — adjacency list (per-vertex list of `Edge`), memory efficient for sparse graphs ($O(|V| + |E|)$).

All algorithms (**BFS, DFS, Dijkstra**) are decoupled from the concrete representations and operate polymorphically on the base `Graph` class.

---

## Architecture & Design

### Abstract Base Class `Graph`

Defines the shared interface and configuration flags:

```cpp
Graph(bool isDirected, bool isWeighted);
```

- `isDirected`: Controls whether edges are one-way (`true`) or bidirectional (`false`).
- `isWeighted`: Controls whether edge weights are preserved or defaulted to `1.0`.

### Core Operations

```cpp
bool insertVertex(std::string label);
bool removeVertex(int index);
std::string vertexLabel(int index) const;
void printGraph();
bool insertEdge(int origin, int destination, float weight = 1.0f);
bool removeEdge(int origin, int destination);
bool hasEdge(int origin, int destination);
float edgeWeight(int origin, int destination);
std::vector<int> neighbors(int vertex);
int vertexCount() const;
```

---

## File Format & I/O

The `GraphReader` module parses formatted graph text files:

```text
V A D P
Ao Ad Ap
Ao Ad Ap
...
```

- `V`: Number of vertices.
- `A`: Number of edges.
- `D`: `1` if directed, `0` if undirected.
- `P`: `1` if weighted, `0` if unweighted.
- Followed by `A` edge lines (`origin destination [weight]`).
- Empty lines and lines starting with `#` are ignored.
- For unweighted graphs, a third value is optional; if omitted, weight defaults to `1.0`.

Vertex labels are generated automatically while loading:

- Up to 26 vertices: `A` through `Z`.
- More than 26 vertices: `V0`, `V1`, `V2`, ...

```cpp
std::unique_ptr<MatrixGraph> mg = GraphReader::readMatrixGraph("graph_examples/example_dijkstra.txt");
std::unique_ptr<ListGraph> lg = GraphReader::readListGraph("graph_examples/example_dijkstra.txt");
```

---

## Algorithms

### 1. Breadth-First Search (BFS)

```cpp
#include "algorithms/search.h"

std::vector<int> order = bfs(graph, 0);
printBfs(graph, 0);
```

### 2. Depth-First Search (DFS)

```cpp
#include "algorithms/search.h"

std::vector<int> order = dfs(graph, 0);
printDfs(graph, 0);
```

### 3. Dijkstra Shortest Path

Calculates the single-source shortest path, minimum distances, and path reconstructions to all reachable vertices.

```cpp
#include "algorithms/dijkstra.h"

DijkstraResult result = dijkstra(graph, 0);
result.printResult(graph);
std::vector<int> pathTo4 = result.getPathTo(4);
```

---

## Demo Flow (`make run`)

The executable currently runs the following sequence automatically:

1. Navigation graph demo (`example_navigation.txt`) with BFS and DFS on both `MatrixGraph` and `ListGraph`.
2. Weighted shortest-path demo (`example_dijkstra.txt`) with Dijkstra on both representations.
3. Medium graph demo (`medium_graph.txt`) reusing the Dijkstra showcase.
4. Large graph benchmark (`large_graph.txt`) with load time, BFS/DFS timing, Dijkstra timing, and sample shortest paths.
5. Huge graph benchmark (`huge_graph.txt`) with the same performance and path summary metrics.

## Project Structure

```
graphs/
├── Makefile
├── README.md
├── docs/
│   ├── 00-overview.md
│   ├── 01-graph-class-design.md
│   ├── 02-operations-spec.md
│   └── 03-project-structure.md
├── graph_examples/
│   ├── example_navigation.txt   # Unweighted graph for BFS/DFS demo
│   ├── example_dijkstra.txt     # Weighted graph for Dijkstra demo
│   ├── example_directed.txt     # Directed weighted example
│   ├── medium_graph.txt         # Medium weighted graph demo
│   ├── large_graph.txt          # Large graph performance benchmark
│   └── huge_graph.txt           # Huge graph performance benchmark
├── build/
│   └── main                      # Generated binary after build
└── src/
    ├── main.cpp
    ├── algorithms/
    │   ├── search.h / search.cpp       # BFS and DFS
    │   └── dijkstra.h / dijkstra.cpp   # Dijkstra
    ├── graph/
    │   ├── graph.h / graph.cpp         # Base class
    │   ├── edge.h                      # Edge struct
    │   ├── matrix_graph.h / matrix_graph.cpp
    │   └── list_graph.h / list_graph.cpp
    └── io/
        ├── graph_reader.h / graph_reader.cpp # File parser
```

---

## Build & Run

Portable across macOS, Linux, and Windows (MinGW/MSYS2 or WSL).

```sh
make all        # Alias for build
make build      # Compile the binary to build/main
make run        # Run the full automated demonstration
make clean      # Remove build artifacts
```
