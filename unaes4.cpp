/* AES-4 integral attack.
 * Input format: same as the output format of generate_aes_integral.cpp.
 * Every integral must have been ciphered for exactly 4 rounds
 * with the same key.
 */

#include <iostream>
#include <vector>
#include "aes/primitives.h"
#include "aes/subkeys.h"

/* Beginning the fourth round, which consists of SB, SR and ARK,
 * every position in the integral is balanced.
 * To help explaining, we will swap SB and SR; so, the fourth round is
 * SR -> SB -> ARK.
 * Since SR and SB commute, this swap does not change the algorithm.
 * We thus advance through SR, which keeps the balancing of the integral,
 * and reach only SB and ARK.
 *
 * Note that each integral position might not be saturated anymore;
 * therefore, SB will likely destroy the fact that it is balanced.
 * But the balanced-ness is a local property, inside a byte;
 * we can thus, for each byte,
 * test every possible round key.
 * We have the output after ARK; just xor the byte with the current key guess
 * and undo the SB, for every element in the integral.
 * If the resulting position is not balanced
 * (which will happen with probability 1 - 2^-8 for a random key),
 * we can discard that key as a candidate.
 *
 * votes[i][j][k] is the number of integrals in wich the byte k
 * for the position i,j of the key passed on the test.
 * There is a small possibility that a random key passes on the test,
 * so it might be prudent to repeat the attack with two integrals
 * to raise the "acceptance threshold" to two votes.
 */
aes::matrix integral[256];
int votes[4][4][256] = {0};
int processed_integrals;

void process_integral() {
    for( int i = 0; i < 4; i++ )
    for( int j = 0; j < 4; j++ )
    for( int k = 0; k < 256; k++ ) { // [k]ey candidate
        unsigned sum = 0;
        for( int t = 0; t < 256; t++ )
            sum = sum ^ aes::s_box_inv[integral[t][i][j].data ^ k];
        votes[i][j][k] += (sum == 0);
    }
}

bool process_votes() {
    aes::matrix key;
    for( int i = 0; i < 4; i++ )
    for( int j = 0; j < 4; j++ ) {
        bool has_candidate = false;
        for( int k = 0; k < 256; k++ ) {
            if( votes[i][j][k] == processed_integrals ) {
                if( has_candidate ) {
                    std::cerr << "Insuficient data to determine index " << i << ',' << j
                        << " of the key.\n";
                    return false;
                }
                has_candidate = true;
                key[i][j] = aes::polynomial( k );
            }
        }
        if( !has_candidate ) {
            std::cerr << "Inconsistent information at index " << i << ',' << j << '\n';
            return false;
        }
    }
    std::cout << aes::superkey(key, 4) << std::endl;
    return true;
}

int main() {
    int i = 0;
    while( std::cin >> integral[i] ) {
        i++;
        if( i == 256 ) {
            process_integral();
            processed_integrals++;
            i = 0;
        }
    }
    if( i != 0 )
        std::cerr << "Warning: discarded incomplete integral "
            << "(remaining " << 256 - i << " texts)" << std::endl;

    return process_votes() ? 0 : 1;
}
