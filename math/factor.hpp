#ifndef MATH_FACTOR_HPP
#define MATH_FACTOR_HPP

/* Algorithms for factoring numbers.
 */

#include <vector>

namespace math {
    template< typename T >
    struct factor {
        T base;
        T exponent;
    };

    /* Factorizes the prime i by brute-forcing the first few primes.
     *
     * If it fails to fully factor the number,
     * the last factor<int> will be {m, -1},
     * where m is the "part it could not factor".
     */
    std::vector< factor<int> > small_primes_brute_force( int n );
}

#endif // MATH_FACTOR_HPP
