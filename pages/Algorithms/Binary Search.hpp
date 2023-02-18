// A simple binary search algorithm. Give it the length of the array and a
// callback to compare the index to the value you're looking for. It returns the
// index of the value you're looking for, or length if it doesn't exist.
#include <Template.hpp>

// This algorithm was taken from the Go standard library.

int binarySearch(int len, function<bool(int)> compare) {
  int i = 0, j = len;
  while (i < j) {
    int h = int(uint(i + j) >> 1);
    if (!compare(h)) {
      i = h + 1;
    } else {
      j = h;
    }
  }
  return i;
}

static void test_binarySearch() {
  vi vin = {1, 2, 3, 4, 5};
  assert(binarySearch(vin.size(), [&](int i) { return vin[i] >= 3; }) == 2);
  assert(binarySearch(vin.size(), [&](int i) { return vin[i] >= 6; }) == 5);
}
