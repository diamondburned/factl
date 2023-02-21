// This file implements the Held–Karp algorithm for the traveling salesman
// problem. The implementation can likely only handle at most 30 cities due to
// int size limits.
//
// Code ported from:
//
// - https://github.com/CarlEkerot/held-karp/blob/master/held-karp.py
// - https://github.com/dcruzf/HeldKarp/blob/master/code/heldkarptsp.cpp
//
#include <Template.hpp>

pair<int, vi> heldKarp(const vector<vi> &dists) {
  const int n = dists.size();

  vector<vector<pii>> costs(1 << n, vector<pii>(n));
  for (int k = 0; k < n; k++) {
    costs[1 << k][k] = {dists[0][k], 0};
  }

  for (uint subsz = 2; subsz < n; subsz++) {
    vector<bool> v(n - 1);
    fill(v.end() - subsz, v.end(), true);

    do {
      vi sub;
      for (int i = 0; i < n - 1; ++i) {
        if (v[i]) {
          sub.push_back(i + 1);
        }
      }

      int bsub = 0;
      for (auto bit : sub) {
        bsub |= 1 << bit;
      }

      for (auto k : sub) {
        auto psub = bsub & ~(1 << k);
        pii best = {n * 10, 0};

        for (auto m : sub) {
          if (m != k) {
            best = min(best, {costs[psub][m].first + dists[m][k], m});
          }
        }

        costs[bsub][k] = best;
      }
    } while (next_permutation(all(v)));
  }

  auto bits = (1 << n) - 2;

  pii best = {n * 10, 0};
  for (int k = 1; k < n - 1; k++) {
    best = min(best, {costs[bits][k].first + dists[k][0], k});
  }

  vector<int> path(n + 1, 0);
  pii v = best;

  for (int i = 1; i < n; i++) {
    path[i] = v.second;
    v = costs[bits][path[i]];
    bits &= ~(1 << path[i]);
  }

  return {best.first, path};
}

static void example_HeldKarp() {
  const auto tours = heldKarp({
      {0, 2, 9, 10},
      {1, 0, 6, 4},
      {15, 7, 0, 8},
      {6, 3, 12, 0},
  });

  // tour cost:
  assert(tours.first == 21);

  // tour path:
  assert(tours.second == vi({0, 1, 3, 2, 0}));
}
