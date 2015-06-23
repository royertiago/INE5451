#ifndef AES_SUBKEYS_H
#define AES_SUBKEYS_H

/* Subkey generation algorithm.
 */
#include <vector>
#include "aes/matrix.h"

namespace aes {
    std::vector<matrix> subkeys( matrix key );
}

#endif // AES_SUBKEYS_H
