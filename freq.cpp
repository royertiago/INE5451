/* freq.cpp
 * Frequency analysis program
 *
 * Given a utf8-encoded file in stdin,
 * this program will analyze the frequency of appearance
 * of every letter and pair of letters.
 * It will print to stdout a list of pairs 'sequence appearance_count',
 * ordered by size and then lexicographically.
 *
 * This program discard accents and put everything to lower-case before counting,
 * ignores non-letters, and unfolds characters (e.g. eszett (ß) becomes "ss").
 */
#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include "utf8/letter_scanner.h"

int main() {
    long long unsigned singles[26];
    long long unsigned doubles[26][26];
    for( int i = 0; i < 26; i++ )
        singles[i] = 0;
    for( int i = 0; i < 26; i++ )
        for( int j = 0; i < 26; i++ )
            doubles[i][j] = 0;

    letter_scanner scanner( std::cin );

    char a = -1, b = -1;
    while( (b = scanner.next()) != -1 ) {

        singles[b - 'a']++;
        if( a != -1 )
            doubles[a - 'a'][b - 'a']++;
        a = b;
    }
    for( int i = 0; i < 26; i++ )
        std::cout << (char) ('a' + i) << ' ' << singles[i] << '\n';
    for( int i = 0; i < 26; i++ )
        for( int j = 0; i < 26; i++ )
            std::cout << (char) ('a' + i) << (char)('a' + j)
                << ' ' << doubles[i][j] << '\n';

    return 0;
}
