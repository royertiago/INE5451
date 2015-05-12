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

    half_data f( half_data data, subkey key ) {
        expanded_data expanded = expand(data);
        expanded ^= key;

        // bit mask that extract just the last six bits
        constexpr unsigned char mask = 0b111'111;

        /* Each of the six bit groups inside the expanded data.
         * We must cast to unsigned char to avoid narrowing conversion errors
         * (since any "small" arithmetic type is promoted to int
         * before doing any calculations.)
         */
        unsigned char b[8] = {
            (unsigned char) ((expanded >> 42) & mask),
            (unsigned char) ((expanded >> 36) & mask),
            (unsigned char) ((expanded >> 30) & mask),
            (unsigned char) ((expanded >> 24) & mask),
            (unsigned char) ((expanded >> 18) & mask),
            (unsigned char) ((expanded >> 12) & mask),
            (unsigned char) ((expanded >>  6) & mask),
            (unsigned char) ((expanded      ) & mask),
        };

        for( int i = 0; i < 8; i++ ) {
            /* A very strange indexing... */
            unsigned upper = ((b[i] >> 4) & 0b10) | (b[i] & 0b1);
            unsigned lower = (b[i] >> 1) & 0b1111;
            b[i] = s_box[i][(upper << 4) | lower];
        }

        half_data c = b[0] << 28 | b[1] << 24 | b[2] << 20 | b[3] << 16
                    | b[4] << 12 | b[5] <<  8 | b[6] <<  4 | b[7];

        return p(c);
    }
} // namespace des
