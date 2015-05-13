#include <bitset>
#include "des/primitives.h"

#include "subkeys.h"

namespace des {
    input_key extract_key( unsigned long long input ) {
        std::bitset<64> bits(input); // key in a bitset
        std::bitset<56> key; // Key after passing through PC1
    
        /* std::bitset works in "little endian":
         * pkey[0] is the rightmost bit of the bitset,
         * while our primitives treats the bit 0 as the leftmost one.
         * So, we must invert the index in every access to bitsets.
         */
        for( int i = 0; i < 56; i++ )
            key[55-i] = bits[63-pc1[i]];

        return key.to_ullong();
    }

    std::vector<subkey> subkeys( input_key key ) {
        std::vector<subkey> subkeys;

        std::bitset<28> C(key >> 28); // higher bits of the key
        std::bitset<28> D(key); // lower bits of the key

        for( int i = 0; i < 16; i++ ) {
            // Cyclical permutation of the key halves
            C = (C << shift_count[i]) | (C >> (28 - shift_count[i]));
            D = (D << shift_count[i]) | (D >> (28 - shift_count[i]));

            // Concatenation of both subkeys
            std::bitset<56> CD( C.to_ullong() << 28 | D.to_ullong() );

            std::bitset<48> subkey;
            for( int j = 0; j < 48; j++ )
                subkey[47-j] = CD[55-pc2[j]];

            subkeys.push_back( subkey.to_ullong() );
        }

        return subkeys;
    }
} // namespace des
