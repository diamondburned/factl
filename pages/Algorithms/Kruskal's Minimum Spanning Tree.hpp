// This file implements the Kruskal's Minimum Spanning Tree algorithm. It is
// used to find the minimum spanning tree of an undirected weighted graph.
//
// Taken from
// https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-using-stl-in-c/.
#include <Template.hpp>

struct DisjointSets {
  vi p, r; // parent, rank
  int n;

  DisjointSets(int n) : n(n), p(vi(n)), r(vi(n, 0)) {
    for (int i = 0; i <= n; i++) {
      p[i] = i; // every element is parent of itself
    }
  }

  int find(int u) {
    if (u != p[u]) {
      p[u] = find(p[u]);
    }
    return p[u];
  }

  void merge(int x, int y) {
    x = find(x);
    y = find(y);

    if (r[x] > r[y]) {
      p[y] = x;
    } else {
      p[x] = y;
    }

    if (r[x] == r[y]) {
      r[y]++;
    }
  }
};

// Structure to represent a graph
struct Graph {
  int V, E;
  vector<pair<int, pii>> edges;

  Graph(int V, int E) : V(V), E(E) {}

  void addEdge(int u, int v, int w) { edges.push_back({w, {u, v}}); }

  // kruskalMST returns the weight and edges of the MST.
  pair<int, vector<pii>>
  kruskalMST(function<void(int u, int v, int w)> walk = nullptr) {
    int mstWeight = 0;
    vector<pii> mstEdges;

    DisjointSets ds(V);

    sort(all(edges));
    for (auto [w, uv] : edges) {
      int u = uv.first;
      int v = uv.second;

      int set_u = ds.find(u);
      int set_v = ds.find(v);

      if (set_u == set_v) {
        continue; // prevent cycles
      }

      if (walk) {
        walk(u, v, w);
      }

      mstWeight += w;
      mstEdges.push_back({u, v});
      ds.merge(set_u, set_v);

      if (mstEdges.size() == V - 1) {
        break;
      }
    }

    return {mstWeight, mstEdges};
  };
};

static void example_Kruskal_MST() {
  Graph g(9, 14);

  g.addEdge(0, 1, 4);
  g.addEdge(0, 7, 8);
  g.addEdge(1, 2, 8);
  g.addEdge(1, 7, 11);
  g.addEdge(2, 3, 7);
  g.addEdge(2, 8, 2);
  g.addEdge(2, 5, 4);
  g.addEdge(3, 4, 9);
  g.addEdge(3, 5, 14);
  g.addEdge(4, 5, 10);
  g.addEdge(5, 6, 2);
  g.addEdge(6, 7, 1);
  g.addEdge(6, 8, 6);
  g.addEdge(7, 8, 7);

  auto [weight, edges] = g.kruskalMST();
  assert(weight == 37);
  assert(edges == (vector<pii>{
                      {6, 7},
                      {2, 8},
                      {5, 6},
                      {0, 1},
                      {2, 5},
                      {2, 3},
                      {0, 7},
                      {3, 4},
                  }));
}
