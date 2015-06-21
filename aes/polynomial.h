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

        /* Returns the bit at the given index.
         * Throws std::out_of_range if index is greater than 7.
         */
        bool get( std::size_t index ) const;

        /* Sets the bit (turns the bit to 1) at the given index.
         * Throws std::out_of_range if index is greater than 7.
         */
        void set( std::size_t index );

        /* Unsets the bit (turns the bit to 0) at the given index.
         * Throws std::out_of_range if index is greater than 7.
         */
        void unset( std::size_t index );

        // Nested class used to implement operator[].
        struct byte_accessor {
            int index;
            polynomial & p;

            operator bool() const;
            byte_accessor & operator=( bool b );
            byte_accessor & operator=( const byte_accessor & a );
        };

        /* Returns an accessor that can be used to mutate the element at the given index.
         * This operator exists so that the polynomial might be treated as a vector.
         * Throws std::out_of_range if index is greater than 7.
         */
        byte_accessor operator[]( int index );
        bool operator[]( int index ) const;
    };

    // Operators supported by aes::polynomial
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
