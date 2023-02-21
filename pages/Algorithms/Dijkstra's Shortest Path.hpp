// Program to find Dijkstra's shortest path using priority_queue in STL.
#include <Template.hpp>

class Graph {
  int V;
  vector<list<pii>> adj;

public:
  // V is no. of vertices
  Graph(int V_) : V(V_), adj(decltype(adj)(V)){};

  void addEdge(int u, int v, int w) {
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  };

  // shortestPath returns a list of distances from src. It is sorted by
  // increasing order of distance.
  vector<int> shortestPath(int src) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    vector<int> dist(V, INT_MAX);

    pq.push({0, src});
    dist[src] = 0;

    while (!pq.empty()) {
      auto [d, u] = pq.top();
      pq.pop();

      if (d > dist[u]) {
        continue;
      }

      for (auto [v, w] : adj[u]) {
        if (dist[v] > d + w) {
          dist[v] = d + w;
          pq.push(make_pair(dist[v], v));
        }
      }
    }

    return dist;
  };
};

// https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/

static void example_Dijkstra() {
  Graph g(9);
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
  // Distances from 0 are [0]: 0, [1]: 4, [2]: 12, ...
  assert(g.shortestPath(0) == vi({0, 4, 12, 19, 21, 11, 9, 8, 14}));
}
