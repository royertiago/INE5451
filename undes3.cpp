/* DES-3 chosen plaintext attack algorithm.
 */

#include <iomanip>
#include <iostream>
#include "des/des3.h"
#include "des/f.h"
#include "des/subkeys.h"
#include "des/voting.h"

#include <bitset>

int main() {
    unsigned l0, r0, l3, r3;
    unsigned l0s, r0s, l3s, r3s;

    des::votes votes[8] = {0};

    unsigned long long in1, out1, in2, out2;
    while( std::cin >> std::hex >> in1 >> out1 >> in2 >> out2 ) {
        constexpr unsigned long long mask = (1llu << 32) - 1;
        r0 = in1 & mask;
        l0 = in1 >> 32;
        r3 = out1 & mask;
        l3 = out1 >> 32;
        r0s = in2 & mask;
        l0s = in2 >> 32;
        r3s = out2 & mask;
        l3s = out2 >> 32;

        if( r0 != r0s ) {
            std::cerr << "The algorithm requires the last 32 bits to be equal\n"
                "in both input samples. Ignoring this entry...\n";
            continue;
        }

        unsigned long long C = des::p_inv( r3 ^ r3s ^ l0 ^ l0s );
        unsigned long long E = des::expand( l3 );
        unsigned long long Es = des::expand( l3s );

        for( int i = 0; i < 8; i++ ) {
            unsigned input1 = (E >> (42 - 6 * i)) & 0b111'111;
            unsigned input2 = (Es >> (42 - 6 * i)) & 0b111'111;
            unsigned output_xor = (C >> (28 - 4 * i)) & 0b1111;
            des::vote( input1, input2, output_xor, votes[i], i );
        }
    }

    unsigned long long known_bits;
    for( int i = 0; i < 8; i++ ) {
        unsigned long long vote = votes[i].vote();
        if( vote == 64 ) {
            std::cout << "Problem in the S-box " << i << '\n';
            return 1;
        }
        known_bits = (known_bits << 6) | vote;
    }

    auto pair = des::reconstruct_key( known_bits, 2 );
    unsigned long long key = des::brute_force_8(in1, out1, pair.first, pair.second);

    if( key == -1llu ) {
        std::cout << "Could not decipher the message;"
            " maybe I need more (input,output) pairs.\n";
        return 1;
    }

    std::cout << std::hex << des::restore_parity( key ) << '\n';
    return 0;
}
