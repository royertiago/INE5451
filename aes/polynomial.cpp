#include <bitset>
#include <ostream>
#include "bithack.hpp"
#include "polynomial.h"

namespace {
    using namespace aes;

    constexpr unsigned aes_mod = 0b1'0001'1011;

    // Cache of the multiplication function.
    unsigned char aes_multiplication[256][256];

    // Cache of the inverse function.
    unsigned char aes_inverse[256];

    class aes_cache_initializer {
        static aes_cache_initializer instance;
        aes_cache_initializer() {
            init_multiplication();
            init_inverse();
        }

        void init_multiplication() {
            for( unsigned i = 0; i < 256; i++ )
            for( unsigned j = 0; j < 256; j++ ) {
                unsigned mult = 0; // multiplication
                unsigned ii = i, jj = j;
                while( jj != 0 ) {
                    if( ii % 2 == 1 )
                        mult ^= jj;
                    jj <<= 1;
                    ii >>= 1;
                }
                /* mult contains the multiplication of i and j.
                 * We will reduce it modulo aes_mod.
                 */
                while( mult >= 0x100 ) {
                    int shift = fls(mult) - 8;
                    mult ^= (aes_mod << shift);
                }

                aes_multiplication[i][j] = mult;
            }
        }

        void init_inverse() {
            /* We will use the value 0 to mean "uninitialized".
             * Note we need not to explicitly initialize aes_inverse with zero;
             * it is a global array and the C++ Standard guarantees zero-initialization
             * for such objects.
             * (Working Draft for the C++ Standard, N3936, paragraph 3.6.2/2)
             */
            for( int i = 1; i < 256; i++ ) {
                if( aes_inverse[i] != 0 )
                    continue;

                unsigned char powers[256];
                /* To compute the inverse of all numbers in time O(n),
                 * we will compute the orbits of sucessive values
                 * instead of unsing the extended euclidean algorithm.
                 *
                 * powers[k] will contain the value of i^k.
                 */
                powers[0] = 1;
                int k = 1;
                while( true ) {
                    powers[k] = (polynomial(i) * polynomial(powers[k-1])).data;
                    if( powers[k] == 1 )
                        break;
                    k++;
                }
                // i^k == 1; so, i^a * i^b == 1 for a + b == k.
                for( int j = 0; j <= k; j++ ) {
                    aes_inverse[powers[j]] = powers[k-j];
                }
            }
            // Note that aes_inverse[0] remains 0 for the entire algorithm.
        }
    };
    aes_cache_initializer aes_cache_initializer::instance;

} // anonymous namespace

namespace aes {
    polynomial polynomial::inv() const {
        return polynomial(aes_inverse[data]);
    }

    std::ostream & operator<<( std::ostream & os, polynomial p ) {
        os << std::bitset<8>(p.data);
    }

    polynomial operator*( polynomial p, polynomial q ) {
        return polynomial( aes_multiplication[p.data][q.data] );
    }
}
