#include <Template.hpp>

// To represent Disjoint Sets
struct DisjointSets {
  vi p, r; // parent, rank
  int n;

  // Constructor.
  DisjointSets(int n_) : n(n_), p(vi(n_)), r(vi(n_, 0)) {
    // Initially, all vertices are in different sets and have rank 0.
    for (int i = 0; i <= n; i++) {
      p[i] = i; // every element is parent of itself
    }
  }

  // Find the parent of a node 'u'
  // Path Compression
  int find(int u) {
    // Make the parent of the nodes in the path from u--> parent[u] point to
    // parent[u]
    if (u != p[u]) {
      p[u] = find(p[u]);
    }
    return p[u];
  }

  // Union by rank
  void merge(int x, int y) {
    x = find(x);
    y = find(y);

    /* Make tree with smaller height
    a subtree of the other tree */
    if (r[x] > r[y]) {
      p[y] = x;
    } else { // If rnk[x] <= rnk[y]
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

  // kruskalMST returns the weight of the MST.
  int kruskalMST() {
    int mst_wt = 0;

    sort(all(edges));

    DisjointSets ds(V);

    for (auto [w, uv] : edges) {
      int u = uv.first;
      int v = uv.second;

      int set_u = ds.find(u);
      int set_v = ds.find(v);

      // prevent cycle
      if (set_u != set_v) {
        // u -> v with weight w, add code if needed
        mst_wt += w;
        ds.merge(set_u, set_v);
      }
    }

    return mst_wt;
  };
};

// https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-using-stl-in-c/
