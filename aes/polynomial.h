#ifndef AES_POLYNOMIAL_H
#define AES_POLYNOMIAL_H

/* Struct that represents a polynomial in the finite field GF(2^8).
 */

#include <cstddef>
#include <iosfwd>
#include <stdexcept>

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

        // Returns the bit at the given index.
        bool get( std::size_t index ) const {
            if( index >= 8 )
                throw std::out_of_range( "aes::polynomial::get: index is too large." );
            return (data >> index) & 1u;
        }

        // Sets the bit (turns the bit to 1) at the given index.
        void set( std::size_t index ) {
            if( index >= 8 )
                throw std::out_of_range( "aes::polynomial::set: index is too large." );
            data |= (1u << index);
        }

        // Unsets the bit (turns the bit to 0) at the given index.
        void unset( std::size_t index ) {
            if( index >= 8 )
                throw std::out_of_range( "aes::polynomial::unset: index is too large." );
            data &= ~(1u << index);
        }
    };

    inline polynomial operator+( polynomial p, polynomial q ) {
        return polynomial( p.data ^ q.data );
    }
    inline polynomial operator-( polynomial p, polynomial q ) {
        return polynomial( p.data ^ q.data );
    }
    polynomial operator*( polynomial, polynomial );
    inline polynomial operator/( polynomial p, polynomial q ) {
        return p * q.inv();
    }

    inline bool operator==( polynomial p, polynomial q ) {
        return p.data == q.data;
    }
    inline bool operator!=( polynomial p, polynomial q ) {
        return p.data != q.data;
    }


    std::ostream & operator<<( std::ostream &, polynomial );
}

#endif // AES_POLYNOMIAL_H
