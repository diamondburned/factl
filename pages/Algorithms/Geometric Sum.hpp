// Find the sum of the geometric series.
//
// Parameters:
//
// - a: first term
// - r: common ratio
// - n: number of terms
//
#include <Template.hpp>

double geosum(double a, double r, int n) {
  if (r == 1)
    return a * n;
  return a * (1 - pow(r, n)) / (1 - r);
}

// https://www.geeksforgeeks.org/program-sum-geometric-series/

static void example_geosum() {
  assert(geosum(1, 2, 3) == 7);
  assert(geosum(2, 2, 15) == 65534); // geeksfogeeks
}
