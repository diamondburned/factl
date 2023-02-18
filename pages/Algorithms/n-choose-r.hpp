#include "Factorial.hpp"
#include <Template.hpp>

int nCr(int n, int r) {
  return factorial(n) / (factorial(r) * factorial(n - r));
}

static void test_nCr() {
  assert(nCr(0, 0) == 1);
  assert(nCr(1, 0) == 1);
  assert(nCr(1, 1) == 1);
  assert(nCr(2, 0) == 1);
  assert(nCr(2, 1) == 2);
  assert(nCr(2, 2) == 1);
  assert(nCr(3, 0) == 1);
  assert(nCr(3, 1) == 3);
  assert(nCr(3, 2) == 3);
  assert(nCr(3, 3) == 1);
  assert(nCr(5, 3) == 10);
}
