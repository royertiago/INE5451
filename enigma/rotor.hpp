#ifndef ENIGMA_ROTOR_HPP
#define ENIGMA_ROTOR_HPP

/* A single Enigma rotor.
 */

#include "enigma/types.hpp"

namespace enigma {

    class rotor {
        /* zero-indexed permutation of this rotor and its inverse.
         */
        index p[26];
        index p_inv[26];
        index _notch;
        index pos;

    public:
        /* Constructs the permutations p and p_inv
         * from the given rotor text.
         */
        rotor( const char * input, index notch ) {
            for( int i = 0; i < 26; i++ )
                p[i] = input[i] - 'A';
            for( int i = 0; i < 26; i++ )
                p_inv[p[i]] = i;

            _notch = notch;
            pos = 0;
        }

        /* Sets the initial position of the vector.
         */
        void set_pos( index new_pos ) {
            pos = new_pos;
        }

        /* Advances the rotor.
         */
        void step() {
            pos = z(pos + 1);
        }

        /* True if and only if the rotor is in 'notch' position.
         */
        bool notch() const {
            return pos == _notch;
        }

        /* Passes the given signal either through the normal rotor permutation
         * (rotor::in) or through its inverse (rotor::out).
         */
        index in( index i ) const {
            /* Instead of rotating the rotor, we will rotate the input,
             * and then 'derotate' the output.
             */
            return z( p[ z(i + pos) ] - pos );
        }
        index out( index i ) const {
            /* Note we also need to sum,
             * since it is also a rotor we are passing through.
             */
            return z( p_inv[ z(i + pos) ] - pos );
        }

        /* Utility function: Normalizes the output to Z_26,
         * the group of the integers modulo 26.
         *
         * The function only accepts integers in the range [-26, 2*26-1];
         * the reason is that it uses a vector to avoid the modulo operation.
         */
        static inline index z( index i ) {
            static constexpr index helper[3*26] = {
                 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12,
                13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
                 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12,
                13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
                 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12,
                13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
            };
            static constexpr const index * z_vector = helper + 26;
            return z_vector[i];
        }
    };

} // namespace enigma

#endif // ENIGMA_ROTOR_HPP
