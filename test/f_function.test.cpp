/* DES f function.
 *
 * Example copied from http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm
 */

#include "des/f.h"
#include <catch.hpp>

TEST_CASE( "DES f function", "[des]" ) {
    des::subkey key = 0b000110'110000'001011'101111'111111'000111'000001'110010;
    des::half_data R = 0b1111'0000'1010'1010'1111'0000'1010'1010;
    CHECK( des::f(R, key) ==  0b0010'0011'0100'1010'1010'1001'1011'1011 );
}
