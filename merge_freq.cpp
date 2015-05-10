/* Merge the frequency calculation of several files.
 *
 * Each parameter in the command line is treated as a frequency file,
 * in the output format of freq.cpp.
 * This program will scan all these files, merge the data,
 * and print to stdout the results, in the same format.
 *
 * This program was made so that we could merge information from the several files
 * inside the torrent created by http://kopiwiki.dsd.sztaki.hu/.
 */
#include <fstream>
#include <iostream>
#include <map>
#include <string>

struct sized_smaller {
    bool operator()( const std::string & lhs, const std::string & rhs ) const {
        if( lhs.size() != rhs.size() )
            return lhs.size() < rhs.size();

        return lhs < rhs;
    }
};

int main( int argc, char ** argv ) {
    std::map< std::string, long long unsigned, sized_smaller > freq;
    for( int i = 1; i < argc; i++ ) {
        std::ifstream file( argv[i] );
        std::string seq;
        long long unsigned count;
        while( (file >> seq >> count).good() )
            freq[seq] += count;
    }
    for( auto pair : freq )
        std::cout << pair.first << ' ' << pair.second << '\n';
}
