/* This program generates integrals for the Integral Attack for AES.
 *
 * Input format:
 *  <32 hexadecimal digits representing the integral constants>
 *  <32 hexadecimal digits representing the key>
 *  <index of the saturated byte>
 *  <number of rounds>
 * This format may be repeated an arbitrary number of times.
 * Each integral will be separated by an empty line.
 */

#include <iostream>
#include "aes/aes.h"

int main() {
    aes::matrix key, integral;
    int index, i, j, rounds;

    const char * sep = "";

    while( std::cin >> integral >> key >> index >> rounds ) {
        std::cout << sep;
        sep = "\n";

        i = index % 4;
        j = index / 4;

        for( int k = 0; k < 256; k++ ) {
            integral[i][j] = aes::polynomial(k);
            std::cout << aes::aes(integral, key, rounds) << '\n';
        }
    }

    return 0;
}
