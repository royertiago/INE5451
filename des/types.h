#ifndef DES_TYPES_H
#define DES_TYPES_H

/* Types used by the DES algorithm.
 *
 * These types provide semantical information about what is happening
 * in each step of the algorithm.
 */

#include <cstdint>

namespace des {
    /* input_key
     * Crude 64-bit key, directly from the input.
     * This key includes the 8 parity bits.
     */
    typedef std::uint_least64_t input_key;

    /* 48-bit subkey.
     */
    typedef uint_least64_t subkey;
}


#endif // DES_TYPES_H
