#include "math/factor.hpp"
#include <catch.hpp>

TEST_CASE( "Brute-force number factoring", "[math]" ) {
    auto factors = math::small_primes_brute_force( 2*2*3*7 );
    REQUIRE( factors.size() == 3 );
    CHECK( factors[0].base == 2 );
    CHECK( factors[0].exponent == 2 );
    CHECK( factors[1].base == 3 );
    CHECK( factors[1].exponent == 1 );
    CHECK( factors[2].base == 7 );
    CHECK( factors[2].exponent == 1 );
}
