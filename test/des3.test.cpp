/* DES with 3 iterations.
 */
#include "des/des3.h"
#include <catch.hpp>

TEST_CASE( "DES-3 algorithm", "[des][des3]" ) {
    unsigned long long key = 0x1A624C89520DEC46;
    CHECK( des::des3( 0x748502CD38451097, key ) == 0x03C70306D8A09F10 );
    CHECK( des::des3( 0x3874756438451097, key ) == 0x78560A0960E6D4CB );
    CHECK( des::des3( 0x486911026ACDFF31, key ) == 0x45FA285BE5ADC730 );
    CHECK( des::des3( 0x375BD31F6ACDFF31, key ) == 0x134F7915AC253457 );
    CHECK( des::des3( 0x357418DA013FEC86, key ) == 0xD8A31B2F28BBC5CF );
    CHECK( des::des3( 0x12549847013FEC86, key ) == 0x0F317AC2B23CB944 );
}
