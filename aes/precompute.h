#ifndef AES_PRECOMPUTE_H
#define AES_PRECOMPUTE_H

/* List of functions that precompute look-up tables for the AES algorithm.
 *
 * This list exists to avoid the static initialization order fiasco:
 * since the initialization e.g. of the S-box needs inverses,
 * we need some guarantee that the init_s_box function
 * will be called after init_inverse.
 */

namespace aes {
    namespace detail {
        void init_multiplication();
        void init_inverse();
        void init_s_box();
    }
}

#endif // AES_PRECOMPUTE_H
