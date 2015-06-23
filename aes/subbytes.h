#ifndef AES_SUBBYTES_H
#define AES_SUBBYTES_H

/* SubBytes procedure of AES.
 */

#include "aes/matrix.h"

namespace aes {
    extern unsigned char s_box[256];
    extern unsigned char s_box_inv[256];

    inline matrix subbytes( const matrix & m ) {
        matrix r;
        for( int i = 0; i < 4; ++i )
            for( int j = 0; j < 4; ++j )
                r[i][j] = polynomial(s_box[m[i][j].data]);
        return r;
    }

    inline matrix subbytes_inv( const matrix & m ) {
        matrix r;
        for( int i = 0; i < 4; ++i )
            for( int j = 0; j < 4; ++j )
                r[i][j] = polynomial(s_box_inv[m[i][j].data]);
        return r;
    }
}

#endif // AES_SUBBYTES_H
