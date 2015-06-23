#ifndef MATH_ALGO_HPP
#define MATH_ALGO_HPP

/* Templated mathematical algorithms.
 */

#include "bithack.hpp"

namespace math {
    /* Computes t^i, T is a member of a semigroup.
     * We assume i > 0.
     */
    template< typename T >
    T pow( T t, unsigned i ) {
        // Square and multiply algorithm.
        T r(t);
        for( int k = fls(i) - 1; k >= 0; k-- ) {
            r = r * r;
            if( (i >> k) % 2 == 1 )
                r = r * t;
        }
        return r;
    }

}

#endif // MATH_ALGO_HPP
