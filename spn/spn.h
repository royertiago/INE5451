#ifndef SPN_H
#define SPN_H

namespace spn {
    typedef unsigned char index;
    typedef unsigned key;
    typedef unsigned data;

    struct spn {
        index s_box[16];
        index s_box_inv[16];

        /* Constructs the S-box and its inverse from the given vector.
         * The vector is assumed to have at least 16 positions.
         */
        spn( const int * );

        // Applies the S-box of this SPN to each block of 4 bits of the given data.
        data S( data ) const;
    };
}

#endif // SPN_H
