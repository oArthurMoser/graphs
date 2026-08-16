#include <iostream>
#include <string>
#include <vector>

#include "list_graph.h"

// Sentinel returned by edgeWeight for a non-existent edge / invalid origin.
static constexpr float NO_EDGE_WEIGHT = -1.0f;

ListGraph::ListGraph(bool isDirected, bool isWeighted)
    : Graph(isDirected, isWeighted) {}

bool ListGraph::insertVertex(std::string label) {
    vertexLabels_.push_back(label);
    adjacencyList_.push_back(std::vector<Edge>());
    return true;
}

bool ListGraph::removeVertex(int index) {
    if (index < 0 || index >= vertexCount()) {
        return false;
    }
    // 1. Remove the target vertex's own adjacency list.
    adjacencyList_.erase(adjacencyList_.begin() + index);
    // 2. Remove any edge pointing to the removed vertex and reindex all
    //    destinations greater than the removed index.
    for (size_t i = 0; i < adjacencyList_.size(); ++i) {
        for (auto it = adjacencyList_[i].begin(); it != adjacencyList_[i].end();) {
            if (it->destination == index) {
                it = adjacencyList_[i].erase(it);
            } else if (it->destination > index) {
                it->destination -= 1;
                ++it;
            } else {
                ++it;
            }
        }
    }
    vertexLabels_.erase(vertexLabels_.begin() + index);
    return true;
}

void ListGraph::printGraph() {
    std::cout << "Graph (Directed: "
              << (isDirected_ ? "yes" : "no")
              << ", Weighted: "
              << (isWeighted_ ? "yes" : "no")
              << ") [ListGraph]\n";
    for (size_t i = 0; i < vertexLabels_.size(); ++i) {
        std::cout << "[" << i << "] " << vertexLabels_[i] << " -> ";
        std::vector<int> n = neighbors(static_cast<int>(i));
        if (n.empty()) {
            std::cout << "(no connections)\n";
            continue;
        }
        bool first = true;
        for (int dest : n) {
            if (!first) {
                std::cout << ", ";
            }
            first = false;
            std::cout << "(" << dest << ")";
            if (isWeighted_) {
                std::cout << " [weight: " << edgeWeight(static_cast<int>(i), dest) << "]";
            }
        }
        std::cout << "\n";
    }
}

bool ListGraph::insertEdge(int origin, int destination, float weight) {
    if (origin < 0 || origin >= vertexCount() ||
        destination < 0 || destination >= vertexCount()) {
        return false;
    }
    // For unweighted graphs the stored weight is always 1.
    float w = isWeighted_ ? weight : 1.0f;
    adjacencyList_[static_cast<size_t>(origin)].push_back(Edge{destination, w});
    if (!isDirected_) {
        adjacencyList_[static_cast<size_t>(destination)].push_back(Edge{origin, w});
    }
    return true;
}

bool ListGraph::removeEdge(int origin, int destination) {
    if (origin < 0 || origin >= vertexCount() ||
        destination < 0 || destination >= vertexCount()) {
        return false;
    }
    auto& srcList = adjacencyList_[static_cast<size_t>(origin)];
    auto removeOne = [&](std::vector<Edge>& list, int target) {
        for (auto it = list.begin(); it != list.end(); ++it) {
            if (it->destination == target) {
                list.erase(it);
                return true;
            }
        }
        return false;
    };
    // Reverse removal must happen only if the forward edge was removed.
    bool removed = removeOne(srcList, destination);
    if (removed && !isDirected_) {
        removeOne(adjacencyList_[static_cast<size_t>(destination)], origin);
    }
    return removed;
}

// O(degree of the vertex) for ListGraph, as it must scan the adjacency list.
bool ListGraph::hasEdge(int origin, int destination) {
    if (origin < 0 || origin >= vertexCount() ||
        destination < 0 || destination >= vertexCount()) {
        return false;
    }
    for (const Edge& e : adjacencyList_[static_cast<size_t>(origin)]) {
        if (e.destination == destination) {
            return true;
        }
    }
    return false;
}

// O(degree of the vertex) for ListGraph, as it must scan the adjacency list.
float ListGraph::edgeWeight(int origin, int destination) {
    if (origin < 0 || origin >= vertexCount() ||
        destination < 0 || destination >= vertexCount()) {
        return NO_EDGE_WEIGHT;
    }
    for (const Edge& e : adjacencyList_[static_cast<size_t>(origin)]) {
        if (e.destination == destination) {
            return e.weight;
        }
    }
    return NO_EDGE_WEIGHT;  // No edge found.
}

std::vector<int> ListGraph::neighbors(int vertex) {
    std::vector<int> result;
    if (vertex < 0 || vertex >= vertexCount()) {
        return result;
    }
    for (const Edge& e : adjacencyList_[static_cast<size_t>(vertex)]) {
        result.push_back(e.destination);
    }
    return result;
}

int ListGraph::vertexCount() const {
    return static_cast<int>(vertexLabels_.size());
}