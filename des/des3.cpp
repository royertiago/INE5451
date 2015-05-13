#include "des3.h"
#include "des/f.h"
#include "des/subkeys.h"

namespace des {
    long long unsigned des3( long long unsigned text, long long unsigned input_key ) {
        return des3_key( text, des::extract_key(input_key) );
    }

    long long unsigned des3_key( long long unsigned text, long long unsigned key ) {
        auto subkeys = des::subkeys( key );

        des::half_data r0, l0, r1, l1, r2, l2, r3, l3;
        l0 = text >> 32;
        r0 = text & ((1llu << 32) - 1);
        l1 = r0;
        r1 = l0 ^ des::f(r0, subkeys[0]);
        l2 = r1;
        r2 = l1 ^ des::f(r1, subkeys[1]);
        l3 = r2;
        r3 = l2 ^ des::f(r2, subkeys[2]);
        return  (long long unsigned) l3 << 32 | r3;
    }

    long long unsigned brute_force_8(
        long long unsigned plain,
        long long unsigned ciphered,
        long long unsigned partial_key,
        long long unsigned mask
    ) {
        for( int i = 0; i < (1 << __builtin_popcountll(mask)); i++ ) {
            /* Bit subset expansion.
             * The code here (except the last three bits)
             * are here to map the '1' bits in the variable i
             * to the avaliable bits in the mask.
             */
            unsigned long long mask_tmp = mask;
            int j = i;
            unsigned long long subset = 0;
            while( j != 0 ) {
                if( j & 0b1 == 1 )
                    subset |= mask_tmp & -mask_tmp;
                j >>= 1;
                mask_tmp -= mask_tmp & -mask_tmp;
            }

            unsigned long long key = subset | partial_key;
            if( des3_key(plain, key) == ciphered )
                return key;
        }
        return -1;
    }


} // namespace des
