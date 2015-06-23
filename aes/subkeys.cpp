#include "math/algo.hpp"
#include "aes/subkeys.h"
#include "aes/subbytes.h"

#include <stdio.h>

namespace aes {
    std::vector<matrix> subkeys( matrix key ) {
        std::vector<matrix> subkeys;
        subkeys.push_back( key );

        for( int i = 0; i < 10; i++ ) {
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
}
