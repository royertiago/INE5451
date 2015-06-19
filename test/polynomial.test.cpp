#include "aes/polynomial.h"
#include <catch.hpp>

TEST_CASE( "aes::polynomial multiplication", "[aes]" ) {
    using aes::polynomial;
    CHECK( (polynomial(0xcb) * polynomial(0x02)) == polynomial(0x8d) );
    CHECK( (polynomial(0x57) * polynomial(0x13)) == polynomial(0xfe) );
    CHECK( (polynomial(0x53) * polynomial(0xca)) == polynomial(0x01) );
}

TEST_CASE( "aes::polynomial::inv", "[aes]" ) {
    using aes::polynomial;
    for( int i = 1; i < 256; i++ ) {
        polynomial p(i);
        polynomial inv = p.inv();
        INFO( "Polynomial " << p << " - inverse " << inv );
        CHECK( (p * inv) == polynomial(1) );
    }
}
