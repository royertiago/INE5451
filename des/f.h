#ifndef DES_F_H
#define DES_F_H

/* 'f' function, applied to the right part of each key,
 * and auxiliary functions.
 */

#include "des/types.h"

namespace des {

    /* The expansion function E, used to make the half_data
     * as large as the subkey used this round.
     */
    expanded_data expand( half_data );

    /* Return the result of applying the function 'f'
     * to the given right half with the specified subkey.
     */
    half_data f( half_data, subkey );

    /* Runs the permutation function P,
     * used after the output of the S-boxes are concatenated.
     */
    half_data p( half_data );

    /* Inverts the permutation P.
     */
    half_data p_inv( half_data );

} // namespace des

#endif // DES_F_H
