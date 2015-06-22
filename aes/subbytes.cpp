#include "subbytes.h"
#include "aes/polynomial.h"

namespace aes {
    unsigned char s_box[256];
} // namespace aes

namespace {
    using namespace aes;

    class aes_subbytes_initializer {
        static aes_subbytes_initializer instance;
        aes_subbytes_initializer() {
            init_s_box();
        }

        void init_s_box() {
            bool c[] = {1, 1, 0, 0, 0, 1, 1, 0}; // fixed constant

            for( int i = 0; i < 256; i++ ) {
                polynomial b; // s-box output for i

                /* Note we do not need to check if i != 0
                 * because polynomial(0).inv() == 0.
                 */
                polynomial a = polynomial(i).inv();

                for( int i = 0; i < 8; i++ )
                    b[i] = a[i] ^ a[(i+4) % 8] ^ a[(i+5) % 8] ^
                        a[(i+6) % 8] ^ a[(i+7) % 8] ^ c[i];

                s_box[i] = b.data;
            }
        }
    };
    aes_subbytes_initializer aes_subbytes_initializer::instance;
}
