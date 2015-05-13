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
} // namespace des
