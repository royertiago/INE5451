#include "bithack.hpp"
#include <catch.hpp>

TEST_CASE( "Find last set (fls)", "[bithack]" ) {
    CHECK( fls(1) == 0 );
    CHECK( fls(2) == 1 );
    CHECK( fls(3) == 1 );
    CHECK( fls(4) == 2 );
    CHECK( fls(0x30) == 5 );
    CHECK( fls(0x40) == 6 );
}
