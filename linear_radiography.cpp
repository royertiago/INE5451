/* Exposes all the linear weaknesses of a S-box.
 *
 * Input format:
 * <input_bits> <output_bits>
 * <output_0>
 * <output_1>
 * ...
 * <output_n>
 *
 * where each output_i is a binary string of size output_bits
 * and n == 2 ^ (input_bits).
 */
#include <bitset>
#include <iostream>
#include <limits>
#include <vector>

int main() {
    int input_bits, output_bits;
    std::vector< std::bitset<64> > bitsets;
    std::cin >> input_bits >> output_bits;
    for( long long i = 0; i < (1llu << input_bits); i++ ) {
        std::string str;
        std::cin >> str;
        bitsets.emplace_back(str);
    }

    /* Radiography is a matrix[2^input_bits][2^output_bits].
     */
    std::vector< std::vector<long long> > radiography(
        1llu << input_bits,
        std::vector<long long>( 1llu << output_bits, 0 )
    );

    for( unsigned long long input_mask = 0;
        input_mask < (1llu << input_bits);
        input_mask++
    )
    for( unsigned long long output_mask = 0;
        output_mask < (1llu << output_bits);
        output_mask++
    )
    for( unsigned long long input = 0;
        input < (1llu << input_bits);
        input++
    ) {
        radiography[input_mask][output_mask] += 1 -
            __builtin_parityll(input & input_mask) ^
            __builtin_parityll(bitsets[input].to_ullong() & output_mask);
    }

    for( unsigned long long input_mask = 0;
        input_mask < (1llu << input_bits);
        input_mask++
    )
    for( unsigned long long output_mask = 0;
        output_mask < (1llu << output_bits);
        output_mask++
    )
        std::cout << "[" << input_mask << "][" << output_mask << "] - "
            << radiography[input_mask][output_mask] << '\n';

    return 0;
}
