// Function to find factorials of a given number.
#include <Template.hpp>

int64_t factorial(int64_t n) {
  int64_t f = 1;
  while (n > 1) {
    f *= n--;
  }
  return f;
}

static void test_factorial() {
  assert(factorial(0) == 1);
  assert(factorial(1) == 1);
  assert(factorial(2) == 2);
  assert(factorial(3) == 6);
  assert(factorial(4) == 24);
  assert(factorial(5) == 120);
}
