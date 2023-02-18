// Prefix Sum is built-in using std::inclusive_scan and std::exclusive_scan!
// This page just shows how to use them.
#include <Template.hpp>

static void prefixSum() {
  vi vin = {1, 2, 3, 4, 5};
  vi vout(vin.size());

  // Find the inclusive sum of the elements in vin.
  inclusive_scan(all(vin), vout.begin());
  assert(vout == vi({1, 3, 6, 10, 15}));

  // Find the inclusive multiplication of the elements in vin.
  inclusive_scan(all(vin), vout.begin(), multiplies<int>());
  assert(vout == vi({1, 2, 6, 24, 120}));
}
