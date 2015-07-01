/* Shanks algorithm for discrete log.
 * This algorithm is best known as baby-step giant-step.
 *
 * Input format: several lines with the numbers a, b and n,
 * with 1 <= a, b, n <= 2^32
 * and 'a' a primitive root modulo n.
 *
 * Output format: for each line, the value of log_a(b) (mod n).
 */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>
#include "math/algo.hpp"

unsigned solve( unsigned a, unsigned b, unsigned n ) {
    static std::pair<unsigned, unsigned> baby[1u << 16 + 1];
    static std::pair<unsigned, unsigned> giant[1u << 16 + 1];
    // on pair.first we will store the value, and on pair.second, the index.

    unsigned m = std::sqrt( n );
    if( m*m < n ) m++; // this rounds m up.

    unsigned a_inv = math::modular_inverse( a, n );
    unsigned am = math::pow_mod<long long unsigned>( a, m, n );
    // The cast to long long unsigned is needed to avoid overflow.

    giant[0] = {1, 0};
    for( int i = 1; i < m; i++ )
        giant[i] = {(long long unsigned) giant[i-1].first * am % n, i};
    
    baby[0] = {b, 0};
    for( int i = 1; i < m; i++ )
        baby[i] = {(long long unsigned) baby[i-1].first * a_inv % n, i};

    std::sort( giant, giant + m );
    std::sort( baby, baby + m );

    int baby_index = 0, giant_index = 0;
    baby[m] = {n, m};
    giant[m] = {n, m}; // sentinels
    while( true ) {
        if( baby[baby_index].first < giant[giant_index].first )
            baby_index++;
        else if( baby[baby_index].first > giant[giant_index].first )
            giant_index++;
        else
            /* This is guaranteed to happen for baby_index == giant_index == m,
             * so we do not have to worry about that 'while( true )'.
             */
            return m*giant[giant_index].second + baby[baby_index].second;
    }
}

int main() {
    unsigned a, b, n;
    while( std::cin >> a >> b >> n )
        std::cout << solve( a, b, n ) << std::endl;
    return 0;
}
