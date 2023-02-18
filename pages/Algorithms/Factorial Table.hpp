// Lookup table version of the factorial function.
#include <Template.hpp>

// factorials is a factorial lookup table. Taken from
// https://en.wikipedia.org/wiki/Factorial.
static std::vector<int64_t> factorials = {
    1,                   // 0!
    1,                   // 1!
    2,                   // 2!
    6,                   // 3!
    24,                  // 4!
    120,                 // 5!
    720,                 // 6!
    5040,                // 7!
    40320,               // 8!
    362880,              // 9!
    3628800,             // 10!
    39916800,            // 11!
    479001600,           // 12!
    6227020800,          // 13!
    87178291200,         // 14!
    1307674368000,       // 15!
    20922789888000,      // 16!
    355687428096000,     // 17!
    6402373705728000,    // 18!
    121645100408832000,  // 19!
    2432902008176640000, // 20!
};
