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

} // namespace des
