#include "spn/spn.h"
#include <catch.hpp>

int permutation_s[16] = {
    14, 4, 13, 1, 2, 15, 11, 8,
    3, 10, 6, 12, 5, 9, 0, 7
};

int permutation_s_inv[16] = {
    14, 3, 4, 8, 1, 12, 10, 15,
    7, 13, 9, 6, 11, 2, 0, 5
};

TEST_CASE( "SPN constructor", "[spn]" ) {
    spn::spn spn( permutation_s );
    for( int i = 0; i < 16; i++ ) {
        INFO( "i = " << i );
        CHECK( spn.s_box_inv[i] == permutation_s_inv[i] );
    }
}
