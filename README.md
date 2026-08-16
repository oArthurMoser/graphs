# Graph Project (Basic Graph Library)

Part 1 of an academic work on graphs: the basic data structure of a graph
and the fundamental manipulation operations (insert/remove vertices and
edges, query edges, list neighbors and print the graph).

Implemented in C++17 using only the STL, with two representations:

- **`MatrixGraph`** — adjacency matrix (`N x N`), edge queries in O(1).
- **`ListGraph`** — adjacency list (per-vertex list of `Edge`), lower memory
  usage for sparse graphs, edge queries in O(degree of the vertex).

This project does **not** yet implement search, shortest-path, MST, flow or
coloring algorithms — those will come in future stages.

## Design

The abstract base class `Graph` defines the common contract shared by both
representations. Each graph is created with two fixed configuration flags:

```cpp
Graph(bool isDirected, bool isWeighted);
```

- `isDirected`: if `true`, edges are one-way (origin → destination only).
  If `false`, every inserted edge also creates the reverse edge.
- `isWeighted`: if `true`, the weight passed to `insertEdge` is stored and
  used. If `false`, all existing edges have implicit weight `1`.

## Operations

```cpp
bool insertVertex(std::string label);
bool removeVertex(int index);
void printGraph();
bool insertEdge(int origin, int destination, float weight = 1);
bool removeEdge(int origin, int destination);
bool hasEdge(int origin, int destination);
float edgeWeight(int origin, int destination);
std::vector<int> neighbors(int vertex);
```

Every operation that receives a vertex index validates bounds and returns a
failure/sentinel value (never crashes) on invalid input.

## Project structure

```
graphs/
├── Makefile
├── README.md
├── graph_examples/
│   └── example1.txt
└── src/
    ├── main.cpp
    ├── graph/
    │   ├── graph.h / graph.cpp
    │   ├── edge.h
    │   ├── matrix_graph.h / matrix_graph.cpp
    │   └── list_graph.h / list_graph.cpp
    └── unit_tests/            (optional)
```

## Build and run

Portable across macOS, Linux and Windows (MinGW/MSYS2 or WSL). Only a C++17
compiler (`g++`/`clang++`) and `make` are required.

```sh
make build      # compile the library and main.cpp
make run        # run the demonstration binary
make clean      # remove the build/ directory
```

## License

Academic project.