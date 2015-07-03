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
    spn::key key = std::strtol( argv[1], 0, 16 );
    int amount = std::strtol( argv[2], 0, 10 );
    long long unsigned seed = std::strtol( argv[3], 0, 16 );

    spn::spn spn( permutation_s );
    std::mt19937 rng(seed);

    for( int i = 0; i < amount; i++ ) {
        spn::data data = rng() & 0xFFFF;
        std::cout << std::setw(4) << std::setfill('0') << std::hex
            << data << ' '
            << std::setw(4) << std::setfill('0') << std::hex
            << spn.encrypt( data, key ) << std::endl;
    }

    return 0;
}
