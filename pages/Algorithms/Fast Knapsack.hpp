// This function solves the 0-1 Knapsack problem in O(nW) time, where n is the
// number of items and W is the maximum weight.
#include <Template.hpp>

// - val[] is for storing maximum profit for each weight
// - wt[] is for storing weights
// - n is number of item
// - W is maximum capacity of bag
int knapsack(vector<int> val, vector<int> wt, int n, int W) {
  vector<int> dp(W + 1);
  for (int i = 0; i < n; i++)
    for (int j = W; j >= wt[i]; j--)
      dp[j] = max(dp[j], val[i] + dp[j - wt[i]]);
  return dp[W];
}

// https://www.geeksforgeeks.org/space-optimized-dp-solution-0-1-knapsack-problem/

static void test_knapsack() {
  assert(knapsack({7, 8, 4}, {3, 8, 6}, 3, 10) == 11); // geeksforgeeks case
}
