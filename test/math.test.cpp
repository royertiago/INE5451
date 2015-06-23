#include "math/algo.hpp"
#include <catch.hpp>

TEST_CASE( "Square and Multiply algorithm", "[math]" ) {
    CHECK( math::pow(1, 98) == 1 );
    CHECK( math::pow(2, 5) == 32 );
    CHECK( math::pow(3, 2) == 9 );
    CHECK( math::pow(5, 3) == 125 );
}
