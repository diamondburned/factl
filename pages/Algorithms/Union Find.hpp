// Union Find aka Disjoint Sets implementation. Also used in Kruskal's Minimum
// Spanning Tree.
#include <Template.hpp>

struct UnionFind {
  vector<ll> root;
  vector<ll> rank;
  ll count;

  UnionFind(ll n) : root(n), rank(n, 1), count(n) { iota(all(root), 0); }

  ll find(ll x) {
    if (root[x] != x) {
      root[x] = find(root[x]);
    }
    return root[x];
  }

  void merge(ll x, ll y) {
    if (!connected(x, y)) {
      ll X = find(x);
      ll Y = find(y);
      if (rank[X] < rank[Y]) {
        root[X] = Y;
      } else if (rank[X] > rank[Y]) {
        root[Y] = X;
      } else {
        root[X] = Y;
        rank[Y]++;
      }
      count -= 1;
    }
  }

  bool connected(ll x, ll y) { return find(x) == find(y); }
};
