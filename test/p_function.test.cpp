/* DES P function.
 *
 * Example copied from http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm
 */

#include "des/f.h"
#include <catch.hpp>

TEST_CASE( "DES P function", "[des]" ) {
    des::half_data data = 0b0101'1100'1000'0010'1011'0101'1001'0111;
    CHECK( des::p( data ) == 0b0010'0011'0100'1010'1010'1001'1011'1011 );
    CHECK( des::p_inv( des::p(data) ) == data );
}
