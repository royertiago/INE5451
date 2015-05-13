#ifndef DES_DES3_H
#define DES_DES3_H

/* Utilities for help breaking DES-3.
 */

namespace des {
    /* Runs the DES algorithm, but three iterations only,
     * and no initial permutation nor final swap.
     */
    long long unsigned des3( long long unsigned text, long long unsigned key );

} // namespace des


#endif // DES_DES3_H
