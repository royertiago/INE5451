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

    /* Helper to the euclidean algorithm.
     * In the non-tail recursive function,
     * we called recursively extended_euclid to get {x, y, gdc},
     * and returned {y, x - (a/b)*y, gcd}.
     * That is, we applied the linear transformation
     * T(x, y) = (y, x - (a/b)*y) to the pair (x, y).
     *
     * Thinking recursively, the caller of the current function
     * will also apply its own linear transformation,
     * and its caller also, and so on.
     *
     * Since a linear transformation may be represented as a matrix,
     * each level, in fact, simply multiplies the result of the next level
     * (the "deeper" level) by its own matrix.
     *
     * So, to implement it tail-recursively,
     * we pass the product of all the previous levels to the next.
     * The argumens xx, xy, yx and yy are simply the entries of this matrix.
     */
    template< typename T >
    euclid_data<T> euclid_helper( T a, T b, T xx, T xy, T yx, T yy ) {
        if( b == 0 )
            return {xx, yx, a};
        else
            return euclid_helper( b, a%b, xy, xx - xy*(a/b), yy, yx - yy*(a/b) );
    }

    template< typename T >
    euclid_data<T> extended_euclid( const T& a, const T& b ) {
        return euclid_helper( a, b, 1, 0, 0, 1 );
    }
}

#endif // MATH_ALGO_HPP
