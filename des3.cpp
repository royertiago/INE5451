/* DES algorithm, but with only three iterations,
 * and without the initial permutation nor the final swap.
 */

#include <cstdio>
#include "des/des3.h"

int main( int argc, char ** argv ) {
    if( argc != 3 ) {
        std::fprintf( stderr, "Usage: %s <text> <key>\n", argv[0] );
        return 1;
    }

    long long unsigned text;
    long long unsigned key;
    std::sscanf( argv[1], "%llx", &text );
    std::sscanf( argv[2], "%llx", &key );

    std::printf( "%llX\n", des::des3( text, key ) );

    return 0;
}
