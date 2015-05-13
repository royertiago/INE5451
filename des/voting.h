#ifndef DES_VOTING_H
#define DES_VOTING_H

/* Voting structure for breaking the DES.
 */

#include "des/types.h"

namespace des {
    struct votes {
        /* votes[i] is how many times the bits of the number i
         * were chosen as key candidates.
         */
        unsigned char votes[64];

        /* If there is a winner, return its index;
         * otherwise, return 64.
         */
        unsigned char vote() const;
    };

    /* Computes the votes for the given inputs and output_xor pair
     * for the chosen S-box and write it to the given voting_data.
     */
    void vote( unsigned char input1, unsigned char input2, unsigned char output_xor,
        votes& voting_data, int s_box_index );
}

#endif // DES_VOTING_H
