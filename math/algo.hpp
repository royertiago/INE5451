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

    /* Data for the Extended Euclid's algorithm.
     */
    template< typename T >
    struct euclid_data {
        T x;
        T y;
        T gcd; // The greatest common divisor
    };

    template< typename T >
    euclid_data<T> extended_euclid( const T& a, const T& b ) {
        if( b == T(0) )
            return {1, 0, a};
        euclid_data<T> data = extended_euclid( b, a % b );
        return {data.y, data.x - T(a/b) * data.y, data.gcd};
    }
}

#endif // MATH_ALGO_HPP
