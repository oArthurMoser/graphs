#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "graph_reader.h"

bool GraphReader::readFileInfo(const std::string &filePath, GraphFileInfo &info)
{
  std::ifstream file(filePath);
  if (!file.is_open())
  {
    std::cerr << "Error: Unable to open file " << filePath << "\n";
    return false;
  }

  std::string line;
  while (std::getline(file, line))
  {
    if (line.empty() || line[0] == '#')
    {
      continue;
    }
    std::istringstream iss(line);
    int dInt = 0;
    int pInt = 0;
    if (iss >> info.vertexCount >> info.edgeCount >> dInt >> pInt)
    {
      info.isDirected = (dInt != 0);
      info.isWeighted = (pInt != 0);
      return true;
    }
    break;
  }

  std::cerr << "Error: Invalid header format in file " << filePath << "\n";
  return false;
}

bool GraphReader::populateGraph(const std::string &filePath, Graph &graph)
{
  std::ifstream file(filePath);
  if (!file.is_open())
  {
    std::cerr << "Error: Unable to open file " << filePath << "\n";
    return false;
  }

  std::string line;
  bool headerParsed = false;
  GraphFileInfo info;

  while (std::getline(file, line))
  {
    if (line.empty() || line[0] == '#')
    {
      continue;
    }

    std::istringstream iss(line);
    if (!headerParsed)
    {
      int dInt = 0;
      int pInt = 0;
      if (!(iss >> info.vertexCount >> info.edgeCount >> dInt >> pInt))
      {
        std::cerr << "Error: Failed to parse header line.\n";
        return false;
      }
      info.isDirected = (dInt != 0);
      info.isWeighted = (pInt != 0);
      headerParsed = true;

      // Insert all vertices
      for (int i = 0; i < info.vertexCount; ++i)
      {
        std::string label;
        if (info.vertexCount <= 26)
        {
          label = std::string(1, static_cast<char>('A' + i));
        }
        else
        {
          label = "V" + std::to_string(i);
        }
        graph.insertVertex(label);
      }
      continue;
    }

    // Read edges
    int origin = 0;
    int destination = 0;
    float weight = 1.0f;

    if (info.isWeighted)
    {
      if (iss >> origin >> destination >> weight)
      {
        graph.insertEdge(origin, destination, weight);
      }
    }
    else
    {
      if (iss >> origin >> destination)
      {
        // May optionally have weight or default to 1.0
        if (iss >> weight)
        {
          graph.insertEdge(origin, destination, weight);
        }
        else
        {
          graph.insertEdge(origin, destination, 1.0f);
        }
      }
    }
  }

  return headerParsed;
}

std::unique_ptr<MatrixGraph> GraphReader::readMatrixGraph(const std::string &filePath)
{
  GraphFileInfo info;
  if (!readFileInfo(filePath, info))
  {
    return nullptr;
  }

  auto graph = std::make_unique<MatrixGraph>(info.isDirected, info.isWeighted);
  if (!populateGraph(filePath, *graph))
  {
    return nullptr;
  }

  return graph;
}

std::unique_ptr<ListGraph> GraphReader::readListGraph(const std::string &filePath)
{
  GraphFileInfo info;
  if (!readFileInfo(filePath, info))
  {
    return nullptr;
  }

  auto graph = std::make_unique<ListGraph>(info.isDirected, info.isWeighted);
  if (!populateGraph(filePath, *graph))
  {
    return nullptr;
  }

  return graph;
}
