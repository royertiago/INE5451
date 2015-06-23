#ifndef AES_MATRIX_H
#define AES_MATRIX_H

/* Matrix of 4x4 bytes that is used in the AES algorithm.
 */

#include <iosfwd>
#include "aes/polynomial.h"

namespace aes {
    struct matrix {
        polynomial data[4][4];

        matrix() = default;

        /* Parse the string via operator>>.
         * Throws std::invalid_argument if invalid string.
         */
        matrix( const std::string & );

        /* Fills the matrix entries linewise.
         * Note that the filling is linewise, as it is in C matrices,
         * not columnwise, as it is done by operator>>.
         * Throws std::out_of_range if the initializer list is too big,
         * leaves null members if the list is too short.
         */
        matrix( std::initializer_list<polynomial> );

        /* Same as the constructor for std::initializer_list<polynomial>,
         * but additionally throws std::out_of_range
         * if any of the values is greater than 255.
         *
         * (The type is unsigned instead of unsigned char
         * to avoid narrowing-conversion errors.)
         */
        matrix( std::initializer_list<unsigned> );

        polynomial * operator[]( std::size_t index ) {
            return &data[index][0];
        }
        const polynomial * operator[]( std::size_t index ) const {
            return &data[index][0];
        }
    };

    // Supported operators
    matrix operator+( const matrix &, const matrix & );
    matrix operator*( const matrix &, const matrix & );

    inline bool operator==( const matrix & a, const matrix & b ) {
        for( int i = 0; i < 4; i++ )
        for( int j = 0; j < 4; j++ )
            if( a[i][j] != b[i][j] )
                return false;
        return true;
    }
    inline bool operator!=( const matrix & a, const matrix & b ) {
        return !( a == b );
    }

    /* Interprets a list of 32 hexadecimal characters as an aes::matrix.
     * The characters are stored column-wise in the matrix;
     * that is, the first two characters represent index [0][0],
     * the next two represent [1][0], and so on.
     */
    std::istream & operator>>( std::istream &, matrix & );

    /* Writes an whitespace-separated list of 16 hexadecimal numbers
     * in the same format read by operator>>.
     */
    std::ostream & operator<<( std::ostream &, const matrix & );
}
#endif // AES_MATRIX_H
