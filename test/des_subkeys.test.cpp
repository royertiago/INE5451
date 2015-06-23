/* DES subkey extraction
 * 
 * Example copied from http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm
 */
#include "des/subkeys.h"
#include <catch.hpp>

TEST_CASE( "DES parity bit extraction", "[des]" ) {
    unsigned long long key =
        0b00010011'00110100'01010111'01111001'10011011'10111100'11011111'11110001;
    CHECK( des::extract_key(key) ==
        0b1111000'0110011'0010101'0101111'0101010'1011001'1001111'0001111 );

    CHECK( des::restore_parity(des::extract_key(key)) == key );
}

TEST_CASE( "DES subkey generation", "[des]" ) {
    des::input_key key = 
        0b1111000'0110011'0010101'0101111'0101010'1011001'1001111'0001111;

    auto subkeys = des::subkeys( key );
    CHECK(  subkeys[0] == 0b000110'110000'001011'101111'111111'000111'000001'110010 );
    CHECK(  subkeys[1] == 0b011110'011010'111011'011001'110110'111100'100111'100101 );
    CHECK(  subkeys[2] == 0b010101'011111'110010'001010'010000'101100'111110'011001 );
    CHECK(  subkeys[3] == 0b011100'101010'110111'010110'110110'110011'010100'011101 );
    CHECK(  subkeys[4] == 0b011111'001110'110000'000111'111010'110101'001110'101000 );
    CHECK(  subkeys[5] == 0b011000'111010'010100'111110'010100'000111'101100'101111 );
    CHECK(  subkeys[6] == 0b111011'001000'010010'110111'111101'100001'100010'111100 );
    CHECK(  subkeys[7] == 0b111101'111000'101000'111010'110000'010011'101111'111011 );
    CHECK(  subkeys[8] == 0b111000'001101'101111'101011'111011'011110'011110'000001 );
    CHECK(  subkeys[9] == 0b101100'011111'001101'000111'101110'100100'011001'001111 );
    CHECK( subkeys[10] == 0b001000'010101'111111'010011'110111'101101'001110'000110 );
    CHECK( subkeys[11] == 0b011101'010111'000111'110101'100101'000110'011111'101001 );
    CHECK( subkeys[12] == 0b100101'111100'010111'010001'111110'101011'101001'000001 );
    CHECK( subkeys[13] == 0b010111'110100'001110'110111'111100'101110'011100'111010 );
    CHECK( subkeys[14] == 0b101111'111001'000110'001101'001111'010011'111100'001010 );
    CHECK( subkeys[15] == 0b110010'110011'110110'001011'000011'100001'011111'110101 );

    for( int i = 0; i < 16; i++ ) {
        auto pair = des::reconstruct_key(subkeys[i], i);
        CHECK( __builtin_popcountll(pair.second) == 8 );
        CHECK( pair.first == (key & ~pair.second) );
    }
}
