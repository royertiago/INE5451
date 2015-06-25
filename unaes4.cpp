/* AES-4 integral attack.
 * Input format: same as the output format of generate_aes_integral.cpp.
 * Every integral must have been ciphered for exactly 4 rounds
 * with the same key.
 */

#include <iostream>
#include <vector>
#include "aes/aes.h"
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

bool test_key( aes::matrix candidate ) {
    /* A key is only valid if, when decryping two integral outputs,
     * the result differ exactly in one byte.
     *
     * Altough this does not guarantee that the key is the correct one,
     * we will assume the AES is sufficiently random
     * so that the false positive chance is low enough.
     */
    aes::matrix a = aes::aes_inv( integral[0], candidate, 4 );
    aes::matrix b = aes::aes_inv( integral[1], candidate, 4 );
    int differences = 0;
    for( int i = 0; i < 4; i++ )
    for( int j = 0; j < 4; j++ )
        differences += (a[i][j] != b[i][j]);

    return differences == 1;
}

/* Besides simply searching for the most voted key candidate,
 * we will also optionally do a brute-force attack
 * between all possible candidates.
 *
 * voted[i][j] is a vector that contains the list of candidates
 * for the byte [i][j] that were vote by every integral.
 */
bool process_votes() {
    std::vector<aes::polynomial> voted[4][4]; // a matrix of std::vector
    int brute_force_key_space = 1;

    for( int i = 0; i < 4; i++ )
    for( int j = 0; j < 4; j++ ) {
        bool has_candidate = false;
        for( int k = 0; k < 256; k++ )
            if( votes[i][j][k] == processed_integrals )
                voted[i][j].push_back( aes::polynomial(k) );

        if( voted[i][j].empty() ) {
            std::cerr << "Inconsistent information at index " << i << ',' << j << '\n';
            return false;
        }
        brute_force_key_space *= voted[i][j].size();
    }

    /* Hopefully, there are only a few possible candidates for each byte
     * in voted[i][j].
     * We will now test every possible candidate combination
     * if it is the searched key.
     */
    if( brute_force_key_space != 1 )
        std::cerr << "Warning: brute-forcing through " << brute_force_key_space
            << " key candidates...\n";

    std::vector<aes::polynomial>::iterator index[4][4]; // index matrix
    for( int i = 0; i < 4; i++ )
    for( int j = 0; j < 4; j++ ) {
        index[i][j] = voted[i][j].begin();
    }

    bool found = false;
    for( int k = 0; k < brute_force_key_space; k++ ) {
        aes::matrix key_candidate;
        // Build the candidate
        for( int i = 0; i < 4; i++ )
        for( int j = 0; j < 4; j++ )
            key_candidate[i][j] = *index[i][j];

        // Test the candidate
        if( test_key(aes::superkey(key_candidate, 4)) ) {
            std::cout << aes::superkey(key_candidate, 4) << std::endl;
            found = true;
        }

        // Advance index matrix
        for( int i = 0; i < 4; i++ )
        for( int j = 0; j < 4; j++ ) {
            ++index[i][j];
            if( index[i][j] == voted[i][j].end() )
                index[i][j] = voted[i][j].begin();
            else
                goto end_index_advancing_loop;
        }
end_index_advancing_loop:;
    }
    return found;
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
