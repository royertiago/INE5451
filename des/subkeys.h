#ifndef DES_SUBKEYS_H
#define DES_SUBKEYS_H

/* Function that extracts the subkey list from the original key.
 */

#include <cstdint>
#include <vector>

namespace des {
    /* input_key
     * Crude 64-bit key, directly from the input.
     * This key includes the 8 parity bits.
     */
    typedef std::uint_least64_t input_key;

    /* 48-bit subkey.
     */
    typedef uint_least64_t subkey;

    /* Return a list of subkeys for the given key.
     */
    std::vector<subkey> subkeys( input_key );
}

#endif // DES_SUBKEYS_H
