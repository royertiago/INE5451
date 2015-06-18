#include <bitset>
#include <ostream>
#include "polynomial.h"

namespace aes {
    std::ostream & operator<<( std::ostream & os, polynomial p ) {
        os << std::bitset<8>(p.data);
    }
}
