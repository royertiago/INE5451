#ifndef DES_CONSTANTS_H
#define DES_CONSTANTS_H

/* Primitive functions and permutations
 * used in the Data Encription Standard algorithm.
 *
 * To ease the algorithm implementation,
 * every function that returns an index returns 0-indexed values.
 *
 * Some permutations have its inverses precalculated;
 * they are suffixed with _inv.
 */

namespace des {

    /* s_box[i][input]
     * Returns the value of applying the (i+1)-th S-box
     * to the chosen input.
     *
     * Note that the "official" algorithm uses a somewhat complex indexing scheme
     * (the first and last bits are concatenated to form the row index,
     * then the middle bits are used as the column index).
     * The S-boxes here already do this for you.
     */
    extern const unsigned char s_box[8][64];

    /* shift_count[i]
     * Return the number of bits that should be left shifted
     * when extracting the subkey for the (i+1)-th iteraion.
     */
    extern const unsigned char shift_count[16];

    /* All the permutations returns 0-indexed values.
     */
    extern const unsigned char ip[64];
    extern const unsigned char ip_inv[64];
    extern const unsigned char pc1[56];
    extern const unsigned char pc2[48];

    /* Expansion function, used to expand the input to the function f
     * from 32 bits to 48.
     *
     * Also indexed in zero.
     */
    extern const unsigned char E[48];

    /* Permutation used right after passing thorough the S-boxes.
     */
    extern const unsigned char P[32];

} // namespace des

#endif // DES_H
