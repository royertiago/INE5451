#ifndef DES_SUBKEYS_H
#define DES_SUBKEYS_H

/* Function that extracts the subkey list from the original key.
 */

#include <vector>
#include "des/types.h"

namespace des {
    /* Extract the 56 useful bits from the 64 input bits.
     */
    input_key extract_key( unsigned long long input_64_bits );

    /* Reconstruct the original input key, with its parity bits.
     *
     * That is, inverts the previous function.
     */
    long long unsigned restore_parity( input_key );

    /* Return a list of subkeys for the given key.
     */
    std::vector<subkey> subkeys( input_key );
}

#endif // DES_SUBKEYS_H
