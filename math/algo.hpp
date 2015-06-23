#ifndef MATH_ALGO_HPP
#define MATH_ALGO_HPP

/* Templated mathematical algorithms.
 */

namespace math {
    /* Computes t^i, T is a member of a monoid.
     * We assume T(1) is the identity of that monoid.
     */
    template< typename T >
    T pow( T t, unsigned i ) {
        T r(1);
        while( i != 0 ) {
            if( i % 2 == 1 )
                r = r * t;
            t = t * t;
            i >>= 1;
        }
        return r;
    }

}

#endif // MATH_ALGO_HPP
