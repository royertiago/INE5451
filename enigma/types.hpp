#ifndef ENIGMA_TYPES_HPP
#define ENIGMA_TYPES_HPP

/* Types used inside the enigma.
 * These typedefs exist for testing purposes only.
 */

namespace enigma {

    /* Integer type used in the permutations.
     *
     * All the indexes represent values between 0 and 25.
     *
     * Testing with GCC showed a 4% slowdown changing signed char to int.
     */
    typedef signed char index;

} // namespace enigma

#endif // ENIGMA_TYPES_HPP
