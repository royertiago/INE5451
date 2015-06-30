#include "math/algo.hpp"
#include <catch.hpp>

TEST_CASE( "Square and Multiply algorithm", "[math]" ) {
    CHECK( math::pow(1, 98) == 1 );
    CHECK( math::pow(2, 5) == 32 );
    CHECK( math::pow(3, 2) == 9 );
    CHECK( math::pow(5, 3) == 125 );
    CHECK( math::pow(7, 0) == 1 );
}

TEST_CASE( "Extended Euclid", "[math]" ) {
    math::euclid_data<int> data;

    data = math::extended_euclid( 3, 5 );
    CHECK( 1 == data.gcd );
    CHECK( 1 == data.x * 3 + data.y * 5 );
    data = math::extended_euclid( 5, 3 );
    CHECK( 1 == data.gcd );
    CHECK( 1 == data.x * 5 + data.y * 3 );

    data = math::extended_euclid( 32, 24 );
    CHECK( 8 == data.gcd );
    CHECK( 8 == data.x * 32 + data.y * 24 );
    data = math::extended_euclid( 24, 32 );
    CHECK( 8 == data.gcd );
    CHECK( 8 == data.x * 24 + data.y * 32 );
}
