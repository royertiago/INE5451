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

TEST_CASE( "aes::polynomial division", "[aes]" ) {
    using aes::polynomial;
    for( int i = 0; i < 256; i++ )
        for( int j = 1; j < 256; j++ ) {
            polynomial p(i);
            polynomial q(j);
            INFO( "Dividend " << p << " - Divisor " << q );
            CHECK( ((p / q) * q) == p );
        }
}

TEST_CASE( "aes::polynomial bit accessors", "[aes]" ) {
    using aes::polynomial;
    polynomial p(0x71);

    // Operation with accessor methods
    CHECK( p.get(0) == true );
    CHECK( p.get(1) == false );
    CHECK( p.get(2) == false );
    CHECK( p.get(3) == false );
    CHECK( p.get(4) == true );
    CHECK( p.get(5) == true );
    CHECK( p.get(6) == true );
    CHECK( p.get(7) == false );

    p.set(0);
    CHECK( p.get(0) == true );
    p.set(1);
    CHECK( p.get(1) == true );

    p.unset(1);
    CHECK( p.get(1) == false );
    p.unset(7);
    CHECK( p.get(7) == false );

    CHECK( p == polynomial(0x71) );

    // Operation with polynomial::bit_accessor and boolean literals
    CHECK( p[0] == true );
    CHECK( p[1] == false );
    CHECK( p[2] == false );
    CHECK( p[3] == false );
    CHECK( p[4] == true );
    CHECK( p[5] == true );
    CHECK( p[6] == true );
    CHECK( p[7] == false );

    p[0] = true;
    CHECK( p[0] == true );
    p[1] = true;
    CHECK( p[1] == true );

    p[1] = false;
    CHECK( p[1] == false );
    p[7] = false;
    CHECK( p[7] == false );

    // Operations between bit_accessor's.
    CHECK( p[1] == p[2] );
    CHECK( p[4] == p[5] );
    CHECK( p[1] != p[4] );
    CHECK( p[1] <= p[2] );
    CHECK( p[1] <= p[4] );
    CHECK( p[4] >= p[5] );
    CHECK( p[4] >= p[1] );
    CHECK( p[1] < p[4] );
    CHECK( p[4] > p[1] );

    p[0] = p[7];
    CHECK( p[0] == false );
    p[1] = p[7];
    CHECK( p[1] == false );
    p[0] = p[1] = p[4];
    CHECK( p[0] == true );
    CHECK( p[1] == true );

    p[0] = !p[0];
    CHECK( p[0] == false );
    p[5] = p[4] ^ p[6];
    CHECK( p[5] == false );
    p[5] = p[4] || false;
    CHECK( p[5] == true );
    p[5] = p[4] && false;
    CHECK( p[5] == false );
    p[5] = p[4] | false;
    CHECK( p[5] == true );
    p[5] = p[4] & false;
    CHECK( p[5] == false );
    p[5] = ~p[5];
    CHECK( p[5] == true );

    // Exception tests
    CHECK_THROWS_AS( p.get(8), std::out_of_range );
    CHECK_THROWS_AS( p.set(8), std::out_of_range );
    CHECK_THROWS_AS( p.unset(8), std::out_of_range );
    CHECK_THROWS_AS( p[8], std::out_of_range );
}
