#ifndef ENIGMA_MACHINE_HPP
#define ENIGMA_MACHINE_HPP

/* Class that encapsulates an Enigma machine.
 */

#include "enigma/rotor.hpp"
#include "enigma/types.hpp"

namespace enigma {

    class machine {
        rotor * left;
        rotor * middle;
        rotor * right;
        index reflector[26];

        void step_rotors() {
            /* The Enigma's "rodor advancing algorithm" has a "bug".
             * Due to the orgatization of the ratchets,
             * the middle rotor will advance not only when the right rotor's notch
             * is in the turn position, but also when the middle's own notch
             * is in the turn position.
             *
             * We need to produce a "bug-compatible" Enigma machine
             * to be able to break Enigma ciphers.
             */
            bool advance_left = middle->notch();
            bool advance_middle = middle->notch() || right->notch();

            right->step();
            if( advance_middle )
                middle->step();
            if( advance_left )
                left->step();
        }
    public:

        /* Constructs the Enigma machine using the given reflector string.
         * Rotors and initial positions can be set later,
         * via machine::set_rotors and machine::set_window.
         */
        machine( const char * reflector_str ) {
            for( int i = 0; i < 26; i++ )
                reflector[i] = reflector_str[i] - 'A';
        }

        void set_rotors( rotor& left, rotor& middle, rotor& right ) {
            this->left = &left;
            this->middle = &middle;
            this->right = &right;
        }

        void set_key( index l, index m, index r ) {
            left->set_pos( l );
            middle->set_pos( m );
            right->set_pos( r );
        }

        index cipher( index value ) {
            step_rotors();
            value = right->in  ( value );
            value = middle->in ( value );
            value = left->in   ( value );
            value = reflector  [ value ];
            value = left->out  ( value );
            value = middle->out( value );
            value = right->out ( value );
            return value;
        }
    };

} // namespace enigma

#endif // ENIGMA_MACHINE_HPP
