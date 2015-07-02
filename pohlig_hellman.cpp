/* Pohlig-Hellman algorithm for discrete log.
 * The input format is the same as shanks.cpp.
 */
#include <stdio.h>
#include <iostream>
#include <utility> // std::pair
#include "math/factor.hpp"
#include "math/algo.hpp"

typedef long long unsigned llu;

int solve( unsigned a, unsigned b, unsigned p ) {
    unsigned n = p-1;
    unsigned a_inv = math::modular_inverse( a, p );

    auto factors = math::small_primes_brute_force( n );
    std::vector< std::pair<unsigned, unsigned> > crt_data;

    for( auto factor : factors ) {
        const unsigned q = factor.base;
        const unsigned c = factor.exponent;

        unsigned x = 0;
        unsigned bj = b;
        for( unsigned j = 0; j < c; j++ ) {
            unsigned d = math::pow_mod<llu>( bj, n/math::pow(q, j+1), p );

            unsigned aj;
            for( aj = 0; aj < q; aj++ ) // find aj by brute force
                if( d == math::pow_mod<llu>( a, aj*(n/math::pow(q, 1)), p ) )
                    break;

            // found aj!
            x = (x + aj * math::pow(q, j) );
            bj = bj * math::pow_mod(a_inv, aj * math::pow(q, j), p) % p;
        }
        crt_data.push_back({x, math::pow(q, c)});
    }
    return math::chinese_remainder_theorem( crt_data );
}

int main() {
    unsigned a, b, n;
    while( std::cin >> a >> b >> n )
        std::cout << solve( a, b, n ) << std::endl;
    return 0;
}
