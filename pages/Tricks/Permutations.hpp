// C++ has std::next_permutation that gets the permutation for us.
#include <Template.hpp>

static void example_permutations() {
  vi vin = {1, 2, 3};
  do {
    for (auto x : vin)
      cout << x;
    cout << "\n";
  } while (next_permutation(all(vin)));
}
