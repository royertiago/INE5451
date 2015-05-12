#include <bitset>
#include "primitives.h"
#include "f.h"

namespace des {
    expanded_data expand( half_data data ) {
        std::bitset<32> bdata(data);
        std::bitset<48> expanded;
        /* std::bitset treats the index 0 as the rightmost bit;
         * we want it to refer to the leftmost bit.
         */
        for( int i = 0; i < 48; i++ )
            expanded[47-i] = bdata[31-E[i]];
        return expanded.to_ullong();
    }

    half_data p( half_data data ) {
        std::bitset<32> bdata(data);
        std::bitset<32> ret;
        for( int i = 0; i < 32; i++ )
            ret[31-i] = bdata[31-P[i]];
        return ret.to_ullong();
    }

    half_data p_inv( half_data data ) {
        std::bitset<32> bdata(data);
        std::bitset<32> ret;
        for( int i = 0; i < 32; i++ )
            ret[31-P[i]] = bdata[31-i];
        return ret.to_ullong();
    }
} // namespace des
