#ifndef DES_DES3_H
#define DES_DES3_H

/* Utilities for help breaking DES-3.
 */

namespace des {
    /* Runs the DES algorithm, but three iterations only,
     * and no initial permutation nor final swap.
     */
    long long unsigned des3( long long unsigned text, long long unsigned input_key );

    /* Same as above, but bypasses the permutation pc1
     * perfomed in the input key, to extract the 56 useful bits.
     *
     * Useful for brute-forcing the remaining 8 bits in the key, after voting.
     */
    long long unsigned des3_key( long long unsigned text, long long unsigned key );

} // namespace des


#endif // DES_DES3_H
