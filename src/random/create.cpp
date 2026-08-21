#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <unordered_set>

#include "graph/graph.h"
#include "random/create.h"

namespace
{

  constexpr int kMinVertices = 1;
  constexpr int kMaxVertices = 100000;
  constexpr int kMaxRandomEdgesPerVertex = 10;

} // namespace

int readVertexCount()
{
  int vertexCount = 0;

  while (true)
  {
    std::cout << "Digite a quantidade de vertices (min 1, max 100000): ";

    if (!(std::cin >> vertexCount))
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Entrada invalida. Informe um numero inteiro.\n";
      continue;
    }

    if (vertexCount < kMinVertices || vertexCount > kMaxVertices)
    {
      std::cout << "Valor fora do intervalo permitido.\n";
      continue;
    }

    return vertexCount;
  }
}

void createVertices(Graph &graph, int vertexCount)
{
  for (int i = 0; i < vertexCount; ++i)
  {
    graph.insertVertex("V" + std::to_string(i + 1));
  }
}

void createRandomEdges(Graph &graph, int vertexCount)
{
  std::random_device rd2;
  std::mt19937 rng(rd2());

  if (vertexCount <= 1)
  {
    return;
  }

  const int maxEdgesPerVertex = std::min(kMaxRandomEdgesPerVertex, vertexCount - 1);
  std::uniform_int_distribution<int> edgeCountDist(1, maxEdgesPerVertex);
  std::uniform_int_distribution<int> vertexDist(0, vertexCount - 1);

  for (int origin = 0; origin < vertexCount; ++origin)
  {
    const int desiredEdges = edgeCountDist(rng);
    std::unordered_set<int> chosenDestinations;

    while (static_cast<int>(chosenDestinations.size()) < desiredEdges)
    {
      const int destination = vertexDist(rng);
      if (destination == origin)
      {
        continue;
      }

      if (chosenDestinations.insert(destination).second)
      {
        graph.insertEdge(origin, destination);
      }
    }
  }
}

void faker(Graph &graph)
{
  const int vertexCount = readVertexCount();

  createVertices(graph, vertexCount);
  createRandomEdges(graph, vertexCount);
}