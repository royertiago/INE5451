#include <bitset>
#include <ostream>
#include "bithack.hpp"
#include "polynomial.h"

namespace {
    constexpr unsigned aes_mod = 0b1'0001'1011;

    // Cache of the multiplication function.
    unsigned char aes_multiplication[256][256];

    class aes_multiplication_initializer {
        static aes_multiplication_initializer instance;
        aes_multiplication_initializer() {
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
    };
    aes_multiplication_initializer aes_multiplication_initializer::instance;

} // anonymous namespace

namespace aes {
    std::ostream & operator<<( std::ostream & os, polynomial p ) {
        os << std::bitset<8>(p.data);
    }

    polynomial operator*( polynomial p, polynomial q ) {
        return polynomial( aes_multiplication[p.data][q.data] );
    }
}
