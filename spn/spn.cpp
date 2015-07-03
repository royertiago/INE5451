#include "spn.h"

namespace spn {

    spn::spn( const int * s_box_base ) {
        for( int i = 0; i < 16; i++ )
            s_box[i] = s_box_base[i];
        for( int i = 0; i < 16; i++ )
            s_box_inv[s_box_base[i]] = i;
    }

    data spn::S( data d ) const {
        data r(0);
        for( int i = 0; i < 4; i++ )
            r |= s_box[(d >> 4*i) & 0b1111] << 4*i;
        return r;
    }

    data spn::S_inv( data d ) const {
        data r(0);
        for( int i = 0; i < 4; i++ )
            r |= s_box_inv[(d >> 4*i) & 0b1111] << 4*i;
        return r;
    }

} // namespace spn
