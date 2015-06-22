#ifndef AES_MATRIX_H
#define AES_MATRIX_H

/* Matrix of 4x4 bytes that is used in the AES algorithm.
 */

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
}
#endif // AES_MATRIX_H
