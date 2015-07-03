#include "spn.h"

namespace spn {

    spn::spn( const int * s_box_base ) {
        for( int i = 0; i < 16; i++ )
            s_box[i] = s_box_base[i];
        for( int i = 0; i < 16; i++ )
            s_box_inv[s_box_base[i]] = i;
    }

} // namespace spn
