/* freq.cpp
 * Frequency analysis program
 *
 * Given a utf8-encoded file in stdin,
 * this program will analyze the frequency of appearance
 * of every letter, pair of letters, trio, and quadruples.
 * It will print to stdout a list of pairs 'sequence appearance_count',
 * ordered by size and then lexicographically.
 *
 * This program discard accents and put everything to lower-case before counting,
 * ignores non-letters, and unfolds characters (e.g. eszett (ß) becomes "ss").
 */
#include <iostream>
#include <string>
#include <map>
#include "utf8/letter_scanner.h"

struct sized_smaller {
    bool operator()( const std::string & lhs, const std::string & rhs ) const {
        if( lhs.size() != rhs.size() )
            return lhs.size() < rhs.size();

        return lhs < rhs;
    }
};

int main() {
    std::map< std::string, unsigned, sized_smaller > freq;
    letter_scanner scanner( std::cin );
    char a = -1, b = -1, c = -1, d = -1;
    while( (d = scanner.next()) != -1 ) {
        char dd[2] = {d};
        char cc[3] = {c, d};
        char bb[4] = {b, c, d};
        char aa[5] = {a, b, c, d};
        freq[std::string(dd)]++;
        if( c != -1 )
            freq[std::string(cc)]++;
        if( b != -1 )
            freq[std::string(bb)]++;
        if( a != -1 )
            freq[std::string(aa)]++;
        a = b;
        b = c;
        c = d;
    }
    for( auto pair : freq )
        std::cout << pair.first << ' ' << pair.second << '\n';

    return 0;
}
