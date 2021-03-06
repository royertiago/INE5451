#ifndef AES_AES_H
#define AES_AES_H

/* "Black-box" interface to the AES algorithm.
 */
#include "aes/matrix.h"

namespace aes {
    matrix aes( const matrix & data, const matrix & key, int rounds = 10 );
    matrix aes_inv( const matrix & data, const matrix & key, int rounds = 10 );
}

#endif // AES_AES_H
