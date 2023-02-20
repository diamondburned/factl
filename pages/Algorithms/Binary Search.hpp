// A simple binary search algorithm. Give it the length of the array and a
// callback to compare the index to the value you're looking for. It returns the
// index of the value you're looking for, or length if it doesn't exist.
//
// This algorithm was adapted from the Go standard library.
#include <Template.hpp>

int binarySearch(const vector<int> &vec, function<bool(const int &v)> compare) {
  int i = 0, j = sz(vec);
  while (i < j) {
    int h = int(uint(i + j) >> 1);
    if (!compare(vec[h])) {
      i = h + 1;
    } else {
      j = h;
    }
  }
  return i;
}

static void test_binarySearch() {
  vi vin = {1, 2, 3, 4, 5};
  assert(binarySearch(vin, [](int v) { return v >= 3; }) == 2);
  assert(binarySearch(vin, [](int v) { return v >= 6; }) == 5);
}
