#include "precompute.h"

namespace {
    using namespace aes::detail;
    class aes_initializer {
        static aes_initializer instance;
        aes_initializer() {
            init_multiplication();
            init_inverse();
            init_s_box();
        }
    };
    aes_initializer aes_initializer::instance;
} // anonymous namespace
