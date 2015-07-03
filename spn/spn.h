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
    };
}

#endif // SPN_H
