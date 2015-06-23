#include "aes/matrix.h"
#include <sstream>
#include <stdexcept>
#include <catch.hpp>

using p = aes::polynomial;
using aes::matrix;

TEST_CASE( "aes::matrix constructors", "[aes]" ) {
    matrix a{
        p(0xd4), p(0xe0), p(0xb8), p(0x1e),
        p(0xbf), p(0xb4), p(0x41), p(0x27),
        p(0x5d), p(0x52), p(0x11), p(0x98),
        p(0x30), p(0xae), p(0xf1), p(0xe5),
    };

    std::string a_str = "d4 bf 5d 30 e0 b4 52 ae b8 41 11 f1 1e 27 98 e5";
    std::stringstream stream( a_str );

    matrix b;
    stream >> b;
    CHECK( a == b );

    stream.str("");
    stream << b;
    CHECK( stream.str() == a_str );

    matrix c( a_str );
    CHECK( c == b );

    matrix d{
        0xd4, 0xe0, 0xb8, 0x1e,
        0xbf, 0xb4, 0x41, 0x27,
        0x5d, 0x52, 0x11, 0x98,
        0x30, 0xae, 0xf1, 0xe5,
    };
    CHECK( a == d );

    CHECK_THROWS_AS( matrix("Error"), std::invalid_argument );
    CHECK_THROWS_AS( matrix{0x100}, std::out_of_range );
    CHECK_THROWS_AS( (matrix{1u,1u,1u,1u,1u,1u,1u,1u,1u,1u,1u,1u,1u,1u,1u,1u,1u,}),
            std::out_of_range );
}

TEST_CASE( "aes::matrix multiplication", "[aes]" ) {
    matrix a{
        p(0xd4), p(0xe0), p(0xb8), p(0x1e),
        p(0xbf), p(0xb4), p(0x41), p(0x27),
        p(0x5d), p(0x52), p(0x11), p(0x98),
        p(0x30), p(0xae), p(0xf1), p(0xe5),
    };
    matrix m{
        p(0x02),  p(0x03),  p(0x01),  p(0x01),
        p(0x01),  p(0x02),  p(0x03),  p(0x01),
        p(0x01),  p(0x01),  p(0x02),  p(0x03),
        p(0x03),  p(0x01),  p(0x01),  p(0x02),
    };
    matrix r{
        p(0x04), p(0xe0), p(0x48), p(0x28),
        p(0x66), p(0xcb), p(0xf8), p(0x06),
        p(0x81), p(0x19), p(0xd3), p(0x26),
        p(0xe5), p(0x9a), p(0x7a), p(0x4c),
    };

    CHECK( (m * a) == r );
}
