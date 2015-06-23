#ifndef AES_PRIMITIVES_H
#define AES_PRIMITIVES_H

/* Primitive operations of the Advanced Encryption Standard.
 */

#include "aes/matrix.h"

namespace aes {
    extern unsigned char s_box[256];
    extern unsigned char s_box_inv[256];

    matrix subbytes( const matrix & );
    matrix subbytes_inv( const matrix & );
    matrix shiftrow( const matrix & );
    matrix shiftrow_inv( const matrix & );
}

#endif // AES_PRIMITIVES_H
