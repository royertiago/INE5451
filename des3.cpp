/* DES algorithm, but with only three iterations,
 * and without the initial permutation nor the final swap.
 */

#include <cstdio>
#include "des/f.h"
#include "des/subkeys.h"

int main( int argc, char ** argv ) {
    if( argc != 3 ) {
        std::fprintf( stderr, "Usage: %s <text> <key>\n", argv[0] );
        return 1;
    }

    long long unsigned text;
    long long unsigned key;
    std::sscanf( argv[1], "%llx", &text );
    std::sscanf( argv[2], "%llx", &key );

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
    text = (long long unsigned) l3 << 32 | r3;
    std::printf( "%llX\n", text );

    return 0;
}
