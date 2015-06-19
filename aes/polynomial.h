#ifndef AES_POLYNOMIAL_H
#define AES_POLYNOMIAL_H

/* Struct that represents a polynomial in the finite field GF(2^8).
 */

#include <iosfwd>

namespace aes {
    struct polynomial {
        unsigned char data;

        polynomial() :
            data(0)
        {}

        /* Construct a polynomial with the given bits set.
         *
         * Design decision: there will not be any implicit conversion functions
         * between aes::polynomial and unsigned char.
         * The arithmetic operators in aes::polynomial
         * are very different from the unsigned char ones,
         * so its better to have the compiler warn for erroneous operations
         * than to discover them after hours of bug-hunting.
         */
        explicit polynomial( unsigned char data ) :
            data(data)
        {}

        /* Returns the multiplicative inverse of this polynomial,
         * or the null polynomial if data == 0.
         */
        polynomial inv() const;
    };

    inline polynomial operator+( polynomial p, polynomial q ) {
        return polynomial( p.data ^ q.data );
    }
    inline polynomial operator-( polynomial p, polynomial q ) {
        return polynomial( p.data ^ q.data );
    }
    inline bool operator==( polynomial p, polynomial q ) {
        return p.data == q.data;
    }
    inline bool operator!=( polynomial p, polynomial q ) {
        return p.data != q.data;
    }

    polynomial operator*( polynomial, polynomial );
    polynomial operator/( polynomial, polynomial );

    std::ostream & operator<<( std::ostream &, polynomial );
}

#endif // AES_POLYNOMIAL_H
