#ifndef AES_SUBKEYS_H
#define AES_SUBKEYS_H

/* Subkey generation algorithm.
 */
#include <vector>
#include "aes/matrix.h"

namespace aes {
    // Returns the subkeys of the given key.
    std::vector<matrix> subkeys( matrix key );

    /* Computes the key that generated the given subkey
     * at the specified round.
     */
    matrix superkey( const matrix & subkey, int round );
}

#endif // AES_SUBKEYS_H
