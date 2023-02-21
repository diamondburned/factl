// C++ has std::next_permutation that gets the permutation for us.
#include <Template.hpp>

static void example_permutations() {
  vi vin = {1, 2, 3};

  vector<vi> permus;
  do {
    permus.push_back(vin);
  } while (next_permutation(all(vin)));

  assert(permus == (vector<vi>{
                       {1, 2, 3},
                       {1, 3, 2},
                       {2, 1, 3},
                       {2, 3, 1},
                       {3, 1, 2},
                       {3, 2, 1},
                   }));

  // The order of the input vector is preserved.
  assert(vin == (vi{1, 2, 3}));
}
