#include <bitset>
#include "spn.h"

namespace {
    int P[16] = {
        0, 4, 8, 12, 1, 5, 9, 13,
        2, 6, 10, 14, 3, 7, 11, 15,
    };

    spn::data spn_aux(
        spn::data d,
        std::vector<spn::key> subkeys,
        const spn::spn * spn,
        spn::data (spn::spn::* s_box_method)( spn::data ) const
    )
    {
        for (int r = 0; r < 3; r++) {
            d ^= subkeys[r];
            d = (spn->*s_box_method)( d );
            d = spn::P( d );
        }

        // Last round doesn't have subkey
        d ^= subkeys[3];
        d = (spn->*s_box_method)( d );

        // Whitening
        d ^= subkeys[4];

        return d;
    }
} // anonymous namespace


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

    data spn::encrypt( data d, key k ) const {
        return ::spn_aux( d,
            subkeys( k ),
            this,
            &spn::S
        );
    }

    data spn::decrypt( data d, key k ) const {
        auto subkeys = ::spn::subkeys( k );
        subkeys[1] = P(subkeys[1]);
        subkeys[2] = P(subkeys[2]);
        subkeys[3] = P(subkeys[3]);
        return ::spn_aux( d,
            std::vector<key>( subkeys.rbegin(), subkeys.rend() ),
            this,
            &spn::S_inv
        );
    }

    data P( data d ) {
        std::bitset<16> w;
        std::bitset<16> v(d);

        for( int i = 0; i < 16; i++ )
            w[::P[i]] = v[i];

        return w.to_ulong();
    }

    std::vector<key> subkeys( key k ) {
        std::vector<key> subkeys;
        for( int r = 4; r >= 0; r-- )
            subkeys.push_back( (k >> 4*r) & 0xFFFF );
        return subkeys;
    }

} // namespace spn
