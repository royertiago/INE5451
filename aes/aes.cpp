#include "aes.h"
#include "aes/subkeys.h"
#include "aes/primitives.h"

namespace {
    using namespace aes;

    /* Auxiliar function.
     * ARK, SB, SR and MC should be substituted by aes::addroundkey and friends
     * or by aes::addroundkey_inv and friends.
     */
    matrix aes_aux(
        const matrix & data,
        const std::vector<matrix> keys,
        matrix (*ARK)( const matrix &, const matrix & ),
        matrix (*SB)( const matrix & ),
        matrix (*SR)( const matrix & ),
        matrix (*MC)( const matrix & )
    )
    {
        matrix r = aes::addroundkey(data, keys[0]);
        for( int i = 1; i < 10; i++ ) {
            r = SB( r );
            r = SR( r );
            r = MC( r );
            r = ARK( r, keys[i] );
        }
        r = SB( r );
        r = SR( r );
        r = aes::addroundkey( r, keys[10] );

        return r;
    }
} // anonymous namespace

namespace aes {
    matrix aes( const matrix & data, const matrix & key ) {
        return aes_aux(
            data, aes::subkeys(key),
            addroundkey,
            subbytes,
            shiftrow,
            mixcolumn
        );
    }

    matrix aes_inv( const matrix & data, const matrix & key ) {
        auto vec = aes::subkeys(key);
        return aes_aux(
            data, std::vector<matrix>( vec.rbegin(), vec.rend() ),
            addroundkey_inv,
            subbytes_inv,
            shiftrow_inv,
            mixcolumn_inv
        );
    }
}
