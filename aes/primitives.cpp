#include "primitives.h"
#include "aes/precompute.h"
#include "aes/polynomial.h"

namespace aes {
    unsigned char s_box[256];
    unsigned char s_box_inv[256];

    namespace detail {
        void init_s_box() {
            bool c[] = {1, 1, 0, 0, 0, 1, 1, 0}; // fixed constant

            for( int i = 0; i < 256; i++ ) {
                polynomial b; // s-box output for i

                /* Note we do not need to check if i != 0
                 * because polynomial(0).inv() == 0.
                 */
                polynomial a = polynomial(i).inv();

                for( int i = 0; i < 8; i++ )
                    b[i] = a[i] ^ a[(i+4) % 8] ^ a[(i+5) % 8] ^
                        a[(i+6) % 8] ^ a[(i+7) % 8] ^ c[i];

                s_box[i] = b.data;
            }

            for( int i = 0; i < 256; i++ )
                s_box_inv[s_box[i]] = i;

        } // void init_s_box()
    } // namespace detail

    matrix subbytes( const matrix & m ) {
        matrix r;
        for( int i = 0; i < 4; ++i )
            for( int j = 0; j < 4; ++j )
                r[i][j] = polynomial(s_box[m[i][j].data]);
        return r;
    }

    matrix subbytes_inv( const matrix & m ) {
        matrix r;
        for( int i = 0; i < 4; ++i )
            for( int j = 0; j < 4; ++j )
                r[i][j] = polynomial(s_box_inv[m[i][j].data]);
        return r;
    }

    matrix shiftrow( const matrix & m ) {
        matrix r;
        for( int i = 0; i < 4; i++ )
            for( int j = 0; j < 4; j++ )
                r[i][j] = m[i][(j + i) % 4];
        return r;
    }

    matrix shiftrow_inv( const matrix & m ) {
        matrix r;
        for( int i = 0; i < 4; i++ )
            for( int j = 0; j < 4; j++ )
                r[i][j] = m[i][(j - i + 4) % 4];
        return r;
    }
} // namespace aes
