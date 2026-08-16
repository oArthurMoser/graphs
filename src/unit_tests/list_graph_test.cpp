#include <iostream>
#include <string>

#include "../graph/list_graph.h"

// Minimal assertion-based tests for ListGraph (no external framework).
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

    // Undirected, unweighted graph.
    ListGraph g(false, false);

    check(g.vertexCount() == 0, "vertexCount == 0 at start");

    check(g.insertVertex("A"), "insertVertex A");
    check(g.insertVertex("B"), "insertVertex B");
    check(g.insertVertex("C"), "insertVertex C");
    check(g.vertexCount() == 3, "vertexCount == 3 after inserts");

    // insertEdge creates the reverse edge in undirected graphs.
    check(g.insertEdge(0, 1), "insertEdge 0-1");
    check(g.hasEdge(0, 1), "hasEdge 0-1");
    check(g.hasEdge(1, 0), "undirected: hasEdge reverse 1-0");
    check(g.edgeWeight(0, 1) == 1.0f, "unweighted: edgeWeight == 1");

    // Unweighted: weight argument is ignored.
    check(g.insertEdge(1, 2, 99.0f), "insertEdge 1-2 with weight 99");
    check(g.edgeWeight(1, 2) == 1.0f, "unweighted: stored weight is 1");

    // neighbors.
    auto nb = g.neighbors(2);
    bool nbOk = nb.size() == 1 && nb[0] == 1;
    check(nbOk, "neighbors(2) == {1}");

    // removeEdge removes the reverse edge too.
    check(g.removeEdge(0, 1), "removeEdge 0-1");
    check(!g.hasEdge(0, 1), "hasEdge 0-1 false after removal");
    check(!g.hasEdge(1, 0), "undirected: reverse also removed");
    check(!g.removeEdge(0, 1), "removeEdge on missing edge returns false");

    // removeVertex: edges to the removed vertex are removed and remaining
    // destinations are reindexed.
    // Current graph: A(0) and C(2) connected by 1-2 (edge C-1... wait: B was 1).
    // Re-add an edge 1->2 then remove vertex 1.
    check(g.insertVertex("D"), "insertVertex D");
    check(g.insertEdge(1, 2), "insertEdge 1-2");
    check(g.insertEdge(2, 3), "insertEdge 2-3");
    check(g.removeVertex(1), "removeVertex 1");
    // After removing vertex 1, old 2 becomes 1 and old 3 becomes 2.
    check(g.vertexCount() == 3, "vertexCount == 3 after removal");
    check(g.hasEdge(1, 2), "edge reindexed: 1->2 still present");

    // Invalid inputs handled gracefully.
    check(!g.removeVertex(99), "removeVertex invalid returns false");
    check(!g.insertEdge(0, 99), "insertEdge invalid destination returns false");
    check(g.edgeWeight(99, 0) == -1.0f, "edgeWeight invalid origin returns -1");
    check(g.neighbors(99).empty(), "neighbors invalid returns empty");

    std::cout << "\nListGraph tests: failures = " << failures << "\n";
    return failures == 0 ? 0 : 1;
}