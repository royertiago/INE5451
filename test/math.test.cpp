#include "math/algo.hpp"
#include <catch.hpp>

TEST_CASE( "Square and Multiply algorithm", "[math]" ) {
    CHECK( math::pow(1, 98) == 1 );
    CHECK( math::pow(2, 5) == 32 );
    CHECK( math::pow(3, 2) == 9 );
    CHECK( math::pow(5, 3) == 125 );
    CHECK( math::pow(7, 0) == 1 );

    CHECK( math::pow_mod(1, 50, 1) == 0 );
    CHECK( math::pow_mod(9726, 3533, 11413) == 5761 );
}

void test_extended_euclid( int a, int b, int m ) {
    math::euclid_data<int> data = math::extended_euclid( a, b );
    CHECK( data.gcd == m );
    int xabs = data.x > 0 ? data.x : -data.x;
    int yabs = data.y > 0 ? data.y : -data.y;
    for( int x = -xabs + 1; x < xabs; x++ )
        for( int y = -yabs + 1; y < yabs; y++ ) {
            CHECK( 0 == (a*x + b*y) % data.gcd );
            if( a*x + b*y > 0 )
                CHECK( (a*x + b*y) > data.gcd );
            else if( a*x + b*y < 0 )
                CHECK( (a*x + b*y) < -data.gcd );
            else {
                CHECK( (x == 0 || a == 0) );
                CHECK( (y == 0 || b == 0) );
            }
        }
}

TEST_CASE( "Extended Euclid", "[math]" ) {
    math::euclid_data<int> data;

    test_extended_euclid( 3, 5, 1 );
    test_extended_euclid( 5, 3, 1 );
    test_extended_euclid( 32, 24, 8 );
    test_extended_euclid( 24, 32, 8 );
    test_extended_euclid( 0, 5, 5 );
    test_extended_euclid( 5, 0, 5 );
}

TEST_CASE( "Modular inverse", "[math]" ) {
    CHECK( math::modular_inverse( 2, 5 ) == 3 );
    CHECK( math::modular_inverse( 18, 19 ) == 18 );
}
