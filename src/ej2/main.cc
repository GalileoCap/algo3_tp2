#include "utils.h"

#include <iostream>

struct DisjointSet {
  struct Data {
    int size;
    std::vector<int> max;
  };

  DisjointSet(int n);

  int unite(int v, int w);
  int find(int v);

  int& size(int v);
  int& max(int v, int w);

  std::vector<int> repr;
  std::vector<struct Data> data;
};

DisjointSet::DisjointSet(int n) :
  repr(n, -1),
  data(n, {1, std::vector<int>(n, -1)})
  {}

int& DisjointSet::size(int v) {
  return data[find(v)].size;
}

int& DisjointSet::max(int v, int w) {
  v = find(v); w = find(w);
  int &mvw = data[v].max[w],
      &mwv = data[w].max[v];
  mvw = std::max(mvw, mwv);
  mwv = std::max(mvw, mwv);
  return mwv;
}

int DisjointSet::unite(int v, int w) {
  v = find(v); w = find(w);
  if (v == w) return size(v); //A: Nothing to do
  if (size(v) < size(w)) std::swap(v, w); //TODO: Is this needed?

  size(v) += size(w);
  for (int u = 0; u < repr.size(); u++)
    max(v, u) = std::max(max(v, u), max(w, u));
  repr[w] = v;

  return size(v);
}

int DisjointSet::find(int v) {
  return (repr[v] == -1) ? v : repr[v] = find(repr[v]);
}

void printDisjoint(struct DisjointSet& set) {
  printf("   ");
  for (int v = 0; v < set.repr.size(); v++)
    if (v == set.find(v)) printf(" %i ", v+1);
  printf("\n");

  for (int v = 0; v < set.repr.size(); v++) {
    if (v == set.find(v)) {
      printf("%i: ", v+1);
      for (int w = 0; w <= v; w++)
        if (v == w) printf(" - ");
        else if (w == set.find(w)) printf("% i ", set.max(v, w));
      printf("\n");
    }
  }
  printf("\n");
}

int main(void) {
  int T; //U: Number of test cases
  std::cin >> T;

  for (int test = 0; test < T; test++) {
    int n, m; //U: |V|, |E|
    std::cin >> n >> m;

    //A: Input the weighed graph; O(n + m)
    struct DisjointSet set(n);
    std::vector<struct Edge> edges(m);
    for (int i = 0, v, w, k; i < m; i++) {
      std::cin >> v >> w >> k;
      v--; w--; //NOTE: The input is 1-indexed
      edges[i] = {v, w, k};
      set.max(v, w) = k;
    }
#ifdef DEBUG
    printDisjoint(set);
#endif // DEBUG

    //A: Sort the edges by heaviest to lightest; O(m log(m)) <= O(m log(n^2)) = O(2m log(n)) = O(m log(n))
    std::sort(edges.begin(), edges.end(), Edge::greaterThan);

    int res = 0;
    for (const struct Edge& e : edges) {
      int v = e.v, w = e.w, weight = e.weight;
      bool counts = true;
      if (set.find(v) != set.find(w)) {
        int sum = set.unite(v, w);
        for (int u = 0; u < n; u++)
          if (set.find(u) != set.find(v))
            counts &= weight > set.max(v, u);

        res += sum * counts;
#ifdef DEBUG
        printf("(%i, %i): %C? %i\n", v+1, w+1, counts ? 'T' : 'F', set.unite(v, w));
        printDisjoint(set);
#endif // DEBUG
      }
    }

    std::cout << res << std::endl;
  }

  return 0;
}
