/* Implementation of factor.hpp
 */

#include "factor.hpp"

namespace {
    int primes[] = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
        71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139,
        149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223,
    };
}

namespace math {
    std::vector< factor<int> > small_primes_brute_force( int n ) {
        std::vector< factor<int> > ans;
        for( int i = 0; i < sizeof(primes)/sizeof(primes[0]); i++ ) {
            factor<int> f = {primes[i], 0};
            while( n % primes[i] == 0 ) {
                n /= primes[i];
                f.exponent++;
            }
            if( f.exponent >= 1 )
                ans.push_back( f );
            if( n == 1 )
                return ans;
        }
        ans.push_back( {n, -1} );
        return ans;
    }
}
