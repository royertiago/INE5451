/* Generate a list of outputs from a SPN.
 */
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <random>
#include "spn/spn.h"

int permutation_s[16] = {
    8, 4, 2, 1, 12, 6, 3, 13,
    10, 5, 14, 7, 15, 11, 9, 0
};

int main( int argc, char ** argv ) {
    if( argc != 4 ) {
        std::cerr << "Usage: " << argv[0] << " <key> <amount> <seed>\n";
        return 1;
    }
    spn::key key = std::atoi( argv[1] );
    int amount = std::atoi( argv[2] );
    long long unsigned seed = std::atoll( argv[3] );

    spn::spn spn( permutation_s );
    std::mt19937 rng(seed);

    for( int i = 0; i < amount; i++ )
        std::cout << std::setw(4) << std::setfill('0') << std::hex
            << spn.encrypt( rng() & 0xFFFF, key ) << std::endl;

    return 0;
}
