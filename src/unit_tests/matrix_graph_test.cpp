#include <iostream>
#include <string>

#include "../graph/matrix_graph.h"

// Minimal assertion-based tests for MatrixGraph (no external framework).
// Returns 0 if all tests pass, 1 otherwise.
int main() {
    int failures = 0;

    auto check = [&failures](bool condition, const std::string& name) {
        if (condition) {
            std::cout << "[PASS] " << name << "\n";
        } else {
            std::cout << "[FAIL] " << name << "\n";
            ++failures;
        }
    };

    MatrixGraph g(true, true);

    // Initial state.
    check(g.vertexCount() == 0, "vertexCount == 0 at start");

    // insertVertex.
    check(g.insertVertex("A"), "insertVertex A");
    check(g.insertVertex("B"), "insertVertex B");
    check(g.insertVertex("C"), "insertVertex C");
    check(g.vertexCount() == 3, "vertexCount == 3 after inserts");

    // insertEdge + hasEdge + edgeWeight.
    check(g.insertEdge(0, 1, 3.0f), "insertEdge 0->1");
    check(g.insertEdge(1, 2, 5.0f), "insertEdge 1->2");
    check(g.hasEdge(0, 1), "hasEdge 0->1");
    check(!g.hasEdge(2, 0), "no edge 2->0");
    check(g.insertEdge(0, 0, 2.0f), "insertEdge self-loop 0->0");
    check(g.edgeWeight(0, 1) == 3.0f, "edgeWeight 0->1 == 3");
    // Directed: no reverse edge created.
    check(!g.hasEdge(1, 0), "directed: no reverse 1->0");

    // neighbors.
    auto nb = g.neighbors(0);
    bool nbOk = nb.size() == 2;
    check(nbOk, "neighbors(0) has two neighbors");

    // removeEdge.
    check(g.removeEdge(0, 1), "removeEdge 0->1");
    check(!g.hasEdge(0, 1), "hasEdge 0->1 false after removal");
    check(!g.removeEdge(0, 1), "removeEdge on missing edge returns false");

    // removeVertex with reindexing.
    check(g.insertVertex("D"), "insertVertex D");
    check(g.removeVertex(1), "removeVertex 1");
    check(g.vertexCount() == 3, "vertexCount == 3 after removing one");

    // Invalid inputs handled gracefully.
    check(!g.removeVertex(99), "removeVertex invalid index returns false");
    check(!g.insertEdge(0, 99), "insertEdge invalid destination returns false");
    check(g.edgeWeight(99, 0) == -1.0f, "edgeWeight invalid origin returns -1");
    check(g.neighbors(99).empty(), "neighbors invalid returns empty");

    std::cout << "\nMatrixGraph tests: failures = " << failures << "\n";
    return failures == 0 ? 0 : 1;
}