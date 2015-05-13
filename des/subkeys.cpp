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

    long long unsigned restore_parity( input_key key ) {
        std::bitset<64> bits;
        std::bitset<56> bkey(key);
        for( int i = 0; i < 56; i++ )
            bits[63-pc1[i]] = bkey[55-i];

        /* The remaining bits exists to guarantee that the parity
         * of each 8-bit block is odd.
         */
        for( int i = 0; i < 8; i++ ) {
            bool bit = 1;
            for( int j = 1; j < 8; j++ )
                bit ^= bits[8*i + j];
            bits[8*i] = bit;
        }
        return bits.to_ullong();
    }

    std::pair<input_key, input_key> reconstruct_key( subkey s, int index ) {
        int shifts = 0;
        /* We must count values <= index because the shifts
         * happen before applying pc2 in the subkey algorithm.
         */
        for( int i = 0; i <= index; i++ )
            shifts += shift_count[i];

        std::bitset<56> CD; // left (C) and right (D) parts of the key
        std::bitset<56> CDm( (1llu << 56) - 1 ); // CD of the mask
        std::bitset<48> subkey(s);
        for( int i = 0; i < 48; i++ ) {
            CD[55-pc2[i]] = subkey[47-i];
            CDm[55-pc2[i]] = 0;
        }

        std::bitset<28> C( CD.to_ullong() >> 28 );
        std::bitset<28> Cm( CDm.to_ullong() >> 28 );
        std::bitset<28> D( CD.to_ullong() );
        std::bitset<28> Dm( CDm.to_ullong() );

        C = (C >> shifts) | (C << (28 - shifts));
        Cm = (Cm >> shifts) | (Cm << (28 - shifts));
        D = (D >> shifts) | (D << (28 - shifts));
        Dm = (Dm >> shifts) | (Dm << (28 - shifts));

        input_key key = C.to_ullong() << 28 | D.to_ullong();
        input_key mask = Cm.to_ullong() << 28 | Dm.to_ullong();
        return std::make_pair(key, mask);
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
