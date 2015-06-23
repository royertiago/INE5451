#ifndef AES_PRIMITIVES_H
#define AES_PRIMITIVES_H

/* Primitive operations of the Advanced Encryption Standard.
 *
 * The operations addroundkey, subbytes, shiftrow and mixcolumn
 * have their meaning according to the Standard.
 * subbytes_inv, shiftrow_inv and mixcolumn_inv correctly inverts
 * the corresponding function.
 *
 * The only exception is addroundkey_inv.
 * addroundkey is its own inverse; that is,
 *  ARK( ARK( data, key ), key ) == data
 * for every value of data.
 * Then, instead of simply mimicking addroundkey,
 * addroundkey_inv is done so that it permutes with mixcolumn;
 * that is,
 *  IARK( IMC(data), key ) == IMC( ARK(data, key) ).
 *
 * This allows us to keep the same structure for encryption and decryption.
 */

#include "aes/matrix.h"

namespace aes {
    extern unsigned char s_box[256];
    extern unsigned char s_box_inv[256];

    matrix addroundkey( const matrix & data, const matrix & key );
    matrix addroundkey_inv( const matrix & data, const matrix & key );
    matrix subbytes( const matrix & );
    matrix subbytes_inv( const matrix & );
    matrix shiftrow( const matrix & );
    matrix shiftrow_inv( const matrix & );
    matrix mixcolumn( const matrix & );
    matrix mixcolumn_inv( const matrix & );
}

#endif // AES_PRIMITIVES_H
