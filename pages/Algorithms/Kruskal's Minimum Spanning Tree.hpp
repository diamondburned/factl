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
  assert(g.kruskalMST() == 37);
}
