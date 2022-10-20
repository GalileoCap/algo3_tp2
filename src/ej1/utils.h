#pragma once

#include <vector>

#ifdef DEBUG
#include <cstdio>
#endif // DEBUG

enum color_t {
  WHITE, GREY, BLACK
};

using AdjacencyMatrix = std::vector<std::vector<int>>;
void connect(AdjacencyMatrix& adj, int p, int q); //U: Connects two nodes in the adjacency matrix
