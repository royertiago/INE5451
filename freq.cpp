/* freq.cpp
 * Frequency analysis program
 */
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>

void pretty_print( std::map< std::string, unsigned > const & map ) {
    std::vector< std::pair<unsigned, std::string> > count;
    for( auto p: map )
        count.push_back( std::make_pair(p.second, p.first) );

    std::sort( count.begin(), count.end(), [](const auto& p, const auto& q){
            return p.first > q.first || p.first == q.first && p.second < q.second;
        } );
    for( auto p: count )
        if( p.first > 1 )
            std::cout << p.second << ": " << p.first << std::endl;
}

int main() {
    std::map< std::string, unsigned > letters;
    std::map< std::string, unsigned > digraphs;
    std::map< std::string, unsigned > trigraphs;
    std::map< std::string, unsigned > quadrigraphs;
    char a = -1, b = -1, c = -1, d = -1;
    while( std::cin.get( d ) ) {
        char dd[2] = {d};
        char cc[3] = {c, d};
        char bb[4] = {b, c, d};
        char aa[5] = {a, b, c, d};
        letters[std::string(dd)]++;
        if( c != -1 )
            digraphs[std::string(cc)]++;
        if( b != -1 )
            trigraphs[std::string(bb)]++;
        if( a != -1 )
            quadrigraphs[std::string(aa)]++;
        a = b;
        b = c;
        c = d;
    }

    std::cout << "Frequency analysis for letters:" << std::endl;
    pretty_print( letters );
    std::cout << std::endl;
    std::cout << "Frequency analysis for digraphs:" << std::endl;
    pretty_print( digraphs );
    std::cout << std::endl;
    std::cout << "Frequency analysis for trigraphs:" << std::endl;
    pretty_print( trigraphs );
    std::cout << std::endl;
    std::cout << "Frequency analysis for quadrigraphs:" << std::endl;
    pretty_print( quadrigraphs );

    return 0;
}
