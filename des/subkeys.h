#ifndef DES_SUBKEYS_H
#define DES_SUBKEYS_H

/* Function that extracts the subkey list from the original key.
 */

#include <utility>
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

    /* Reconstructs the original subkey that generated the given subkey
     * at the i-th iteration of the subkey algorithm.
     *
     * Note that is not possible to reconstruct the subkey completely.
     * The first member of the pair will contain every known bit of the key
     * in the correct position, and the unkonwn values will be zero.
     * The second member is a mask: if the corresponding bit is known,
     * the value in the mask is zero; if it is unknown, in the mask it is one.
     */
    std::pair<input_key, input_key> reconstruct_key( subkey, int i );

    /* Return a list of subkeys for the given key.
     */
    std::vector<subkey> subkeys( input_key );
}

#endif // DES_SUBKEYS_H
