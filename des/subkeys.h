#ifndef DES_SUBKEYS_H
#define DES_SUBKEYS_H

/* Function that extracts the subkey list from the original key.
 */

#include <vector>
#include "des/types.h"

namespace des {
    /* Return a list of subkeys for the given key.
     */
    std::vector<subkey> subkeys( input_key );
}

#endif // DES_SUBKEYS_H
