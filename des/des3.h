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

    /* Brute-forces the last bits of a DES-3 key.
     *
     * plain and ciphered are the desired input and output.
     * partial_key is a 56-bit DES-3 key, with all the known bits.
     * Every unknown bit is zero.
     * maks tells which of the bits in the partial_key are known.
     * If a bit is zero in the mask, then it is known, and vice-versa.
     *
     * Retruns the 56-bit key that solves the problem,
     * or -1 if no such key was found.
     */
    long long unsigned brute_force_8(
        long long unsigned plain,
        long long unsigned ciphered,
        long long unsigned partial_key,
        long long unsigned mask
    );

} // namespace des


#endif // DES_DES3_H
