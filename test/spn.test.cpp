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

TEST_CASE( "SPN S-boxes", "[spn]" ) {
    spn::spn spn( permutation_s );
    CHECK( spn.S( 0b0001'1100'0010'0011 ) == 0b0100'0101'1101'0001 );
    CHECK( spn.S( 0b1000'0111'0100'1010 ) == 0b0011'1000'0010'0110 );
    CHECK( spn.S( 0b1101'0101'0110'1110 ) == 0b1001'1111'1011'0000 );
    CHECK( spn.S( 0b1010'1001'0000'1101 ) == 0b0110'1010'1110'1001 );

}

TEST_CASE( "SPN permutation", "[spn]" ) {
    CHECK( spn::P( 0b0100'0101'1101'0001 ) == 0b0010'1110'0000'0111 );
    CHECK( spn::P( 0b0011'1000'0010'0110 ) == 0b0100'0001'1011'1000 );
    CHECK( spn::P( 0b1001'1111'1011'0000 ) == 0b1110'0100'0110'1110 );
}

TEST_CASE( "SPN subkeys", "[spn]" ) {
    auto subkeys = spn::subkeys( 0b0011'1010'1001'0100'1101'0110'0011'1111 );
    CHECK( subkeys[0] == 0b0011'1010'1001'0100 );
    CHECK( subkeys[1] == 0b1010'1001'0100'1101 );
    CHECK( subkeys[2] == 0b1001'0100'1101'0110 );
    CHECK( subkeys[3] == 0b0100'1101'0110'0011 );
    CHECK( subkeys[4] == 0b1101'0110'0011'1111 );
}

TEST_CASE( "SPN encrypt/decrypt", "[spn]" ) {
    spn::spn spn( permutation_s );
    spn::key key = 0b0011'1010'1001'0100'1101'0110'0011'1111;
    spn::data plain = 0b0010'0110'1011'0111;
    spn::data cypher = 0b1011'1100'1101'0110;
    CHECK( spn.encrypt( plain, key ) == cypher );
    CHECK( spn.decrypt( cypher, key ) == plain );
}
