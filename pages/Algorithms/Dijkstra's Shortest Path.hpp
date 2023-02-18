// Program to find Dijkstra's shortest path using
// priority_queue in STL
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
      int u = pq.top().second;
      pq.pop();

      for (auto [v, w] : adj[u]) {
        if (dist[v] > dist[u] + w) {
          dist[v] = dist[u] + w;
          pq.push(make_pair(dist[v], v));
        }
      }
    }

    return dist;
  };
};

// https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
