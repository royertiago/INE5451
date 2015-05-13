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
     * 56-bit key, generated after passing through the initial permutation.
     * This key does not have the extra 8 parity bits.
     */
    typedef std::uint_least64_t input_key;

    /* 48-bit subkey.
     */
    typedef std::uint_least64_t subkey;

    /* Either the left or the right half of the input data.
     */
    typedef std::uint_least32_t half_data;

    /* A half_data that has passed through the expansion function,
     * inside the function 'f'.
     *
     * We define it as the same type as subkey to reinforce that
     * the exclusive-or operation can be done between these data types.
     */
    typedef subkey expanded_data;
}


#endif // DES_TYPES_H
