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
 *
 * This program will output a table of vaules
 * that try to capture good linear approximations
 * to specific expressions in the input.
 *
 * The table is indexed by a, in the row, and b, in the column.
 * Both a and b are bitsets;
 * a represents a subset of the input bits,
 * b represents a subset of the output bits.
 * The value at position [a][b] is how many times the xor
 * of all bits in a and all bits in b was zero,
 * when iterating through all the possible input values.
 *
 * Thus, an high value at position [a][b]
 * shows that this configuration is almost always zero;
 * conversely, a low value shows it is almost always one.
 *
 * These patterns are exploited in the linear cryptanalysis.
 */
#include <bitset>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

/* Print the radiography in tabular form.
 */
void pretty_print( std::vector< std::vector<long long> > vec ) {
    /* digits is the number of digits that the entry with more digits has.
     *
     * For this specific algorithm, vec[0][0] is guaranteed
     * to be the greatest possible value.
     */
    int digits = 1;
    long long target = vec[0][0];
    while( (target /= 10) > 0 )
        digits++;

    std::cout << std::string( digits + 2, ' ' );
    for( int j = 0; j < vec[0].size(); j++ )
        std::cout << std::setw(digits + 1) << j;
    std::cout << '\n';

    for( int i = 0; i < vec.size(); i++ ) {
        std::cout << std::setw(digits + 1) << i << ' ';
        for( int j = 0; j < vec[i].size(); j++ )
            std::cout << std::setw(digits + 1) << vec[i][j];
        std::cout << '\n';
    }
}

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

    /* Here is the code that do the "real work".
     *
     * The first two 'for's iterate through every possible [a][b] value
     * described above.
     * The last 'for' iterate through every possible input.
     *
     * __builtin_parity returns __builtin_popcount % 2;
     * that is, 1 if the number of bits 1 in the argument is odd,
     * and 0 if it is even.
     * Note that this is exactly the exclusive-or of every bit in the argument.
     *
     * Since we need to compute the number of zeros,
     * we simply "negate" the return value,
     * by computing "1 - value".
     */
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

    pretty_print( radiography );

    return 0;
}
