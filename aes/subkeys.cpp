#include "math/algo.hpp"
#include "aes/subkeys.h"
#include "aes/primitives.h"

#include <stdio.h>

namespace aes {
    std::vector<matrix> subkeys( matrix key, int rounds ) {
        std::vector<matrix> subkeys;
        subkeys.push_back( key );

        for( int i = 0; i < rounds; i++ ) {
            matrix last = subkeys.back();
            matrix next;

            /* Set the first column of next to a rotation
             * of the last column of last_key,
             * submit it to the s_box,
             * and apply the round constant.
             */
            for( int j = 0; j < 4; j++ )
                next[j][0] = last[(j+1)%4][3];
            for( int j = 0; j < 4; j++ )
                next[j][0] = polynomial(s_box[next[j][0].data]);
            next[0][0] = next[0][0] + math::pow( polynomial(2), i );
            for( int j = 0; j < 4; j++ )
                next[j][0] = next[j][0] + last[j][0];

            // Add the other columns.
            for( int k = 1; k < 4; k++ )
            for( int j = 0; j < 4; j++ )
                next[j][k] = next[j][k-1] + last[j][k];

            subkeys.push_back( next );
        }

        return subkeys;
    }

    matrix superkey( const matrix & subkey, int round ) {
        matrix next = subkey;
        matrix last;
        for( int i = round - 1; i >= 0; --i ) {
            /* We will just revert the procedure performed in aes::subkeys.
             * Note that the order is irrelevant for j.
             */
            for( int k = 3; k > 0; --k )
            for( int j = 0; j < 4; j++ )
                last[j][k] = next[j][k] - next[j][k-1];
            /* This settles the values for the last three columns.
             *
             * The first column of 'next' is obtained
             * by doing a transform in the last column of 'last'
             * and xor-ring it with the first column of 'last'.
             * To obtain the first column back,
             * we will copy the last column of 'last'
             * (that we now have avaliable),
             * do that operations,
             * and xor with the first column of 'next'.
             *
             * It is important to note that we must do the same transformation
             * berofe xor-ring with the first column,
             * not undo them.
             */
            for( int j = 0; j < 4; j++ )
                last[j][0] = last[(j+1)%4][3];
            for( int j = 0; j < 4; j++ )
                last[j][0] = polynomial(s_box[last[j][0].data]);
            last[0][0] = last[0][0] + math::pow( polynomial(2), i );
            for( int j = 0; j < 4; j++ )
                last[j][0] = last[j][0] + next[j][0];

            next = last; // move backwards
        }
        return next;
    }
}
