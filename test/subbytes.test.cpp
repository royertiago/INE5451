#include "aes/subbytes.h"
#include <catch.hpp>

using aes::matrix;

TEST_CASE( "AES S-box", "[aes]" ) {
    CHECK( aes::s_box[0x53] == 0xed );
}

TEST_CASE( "AES S-box inverse", "[aes]" ) {
    for( int i = 0; i < 256; i++ ) {
        INFO( "i = " << i );
        CHECK( aes::s_box_inv[aes::s_box[i]] == i );
        CHECK( aes::s_box[aes::s_box_inv[i]] == i );
    }
}

TEST_CASE( "AES subbytes", "[aes]" ) {
    matrix m{
        0x00, 0x3C, 0x6E, 0x47,
        0x1F, 0x4E, 0x22, 0x74,
        0x0E, 0x08, 0x1B, 0x31,
        0x54, 0x59, 0x0B, 0x1A,
    };
    matrix ans{
        0x63, 0xEB, 0x9F, 0xA0,
        0xC0, 0x2F, 0x93, 0x92,
        0xAB, 0x30, 0xAF, 0xC7,
        0x20, 0xCB, 0x2B, 0xA2,
    };
    CHECK( aes::subbytes(m) == ans );
    CHECK( aes::subbytes_inv(ans) == m );
}
