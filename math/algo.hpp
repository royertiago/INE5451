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
    euclid_data<T> extended_euclid( T a, T b ) {
        T xx = T(1), xy = T(0), yx = T(0), yy = T(1);
        while( b != 0 ) {
            T nxy = xx - xy*(a/b);
            xx = xy;
            xy = nxy;

            T nyy = yx - yy*(a/b);
            yx = yy;
            yy = nyy;

            T nb = a % b;
            a = b;
            b = nb;
        }
        return {xx, yx, a};
    }

    /* Computes the inverse of a modulo n.
     * This algorithm assumes gcd(a, n) == 1.
     */
    template< typename T >
    T modular_inverse( T a, T n ) {
        auto d = extended_euclid( a, n );
        return (d.x + n) % n;
    }
}

#endif // MATH_ALGO_HPP
