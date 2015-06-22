#include "aes/subbytes.h"
#include <catch.hpp>

TEST_CASE( "AES S-box", "[aes]" ) {
    CHECK( aes::s_box[0x53] == 0xed );
}
