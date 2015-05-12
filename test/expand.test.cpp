/* DES expansion function.
 *
 * Example copied from http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm
 */
#include "des/f.h"
#include <catch.hpp>

TEST_CASE( "DES expansion function", "[des]" ) {
    CHECK( des::expand( 0b1111'0000'1010'1010'1111'0000'1010'1010 )
        ==  0b011110'100001'010101'010101'011110'100001'010101'010101 );
}
