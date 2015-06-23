#ifndef AES_MATRIX_H
#define AES_MATRIX_H

/* Matrix of 4x4 bytes that is used in the AES algorithm.
 */

#include <iosfwd>
#include "aes/polynomial.h"

namespace aes {
    struct matrix {
        polynomial data[4][4];

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
