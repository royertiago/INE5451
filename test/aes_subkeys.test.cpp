/* AES subkey extraction
 * Example copied from http://www.kavaliro.com/wp-content/uploads/2014/03/AES.pdf
 *
 * Actually, the example has a typo in the 6th round:
 * the 4th byte is 87, not B7.
 */
#include "aes/subkeys.h"
#include <catch.hpp>

using aes::matrix;

TEST_CASE( "AES subkey generation", "[aes]" ) {
    matrix key("54 68 61 74 73 20 6D 79 20 4B 75 6E 67 20 46 75");
    auto vec = aes::subkeys(key);
    CHECK( vec[0] == matrix("54 68 61 74 73 20 6D 79 20 4B 75 6E 67 20 46 75") );
    CHECK( vec[1] == matrix("E2 32 FC F1 91 12 91 88 B1 59 E4 E6 D6 79 A2 93") );
    CHECK( vec[2] == matrix("56 08 20 07 C7 1A B1 8F 76 43 55 69 A0 3A F7 FA") );
    CHECK( vec[3] == matrix("D2 60 0D E7 15 7A BC 68 63 39 E9 01 C3 03 1E FB") );
    CHECK( vec[4] == matrix("A1 12 02 C9 B4 68 BE A1 D7 51 57 A0 14 52 49 5B") );
    CHECK( vec[5] == matrix("B1 29 3B 33 05 41 85 92 D2 10 D2 32 C6 42 9B 69") );
    CHECK( vec[6] == matrix("BD 3D C2 87 B8 7C 47 15 6A 6C 95 27 AC 2E 0E 4E") );
    CHECK( vec[7] == matrix("CC 96 ED 16 74 EA AA 03 1E 86 3F 24 B2 A8 31 6A") );
    CHECK( vec[8] == matrix("8E 51 EF 21 FA BB 45 22 E4 3D 7A 06 56 95 4B 6C") );
    CHECK( vec[9] == matrix("BF E2 BF 90 45 59 FA B2 A1 64 80 B4 F7 F1 CB D8") );
    CHECK( vec[10] == matrix("28 FD DE F8 6D A4 24 4A CC C0 A4 FE 3B 31 6F 26") );

    for( int i = 0; i <= 10; i++ ) {
        INFO( "i = " << i );
        CHECK( aes::superkey(vec[i], i) == key );
    }
}
