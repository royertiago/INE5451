#ifndef BITHACK_HPP
#define BITHACK_HPP

#include <limits>

/* Bit operations implemented mainly in terms of GCC's __builtin functions.
 */

/* Find last set; returns the index of the highest set bit.
 */
int fls( unsigned i ) {
    return std::numeric_limits<unsigned>::digits - 1 - __builtin_clz(i);
}

#endif // BITHACK_HPP
