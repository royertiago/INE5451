#include <iostream>
#include <iomanip>
#include "spn/spn.h"

int s_box[16] = {
    8, 4, 2, 1, 12, 6, 3, 13,
    10, 5, 14, 7, 15, 11, 9, 0
};

int votes[256];

int abs( int i ) {
    return i > 0 ? i : -i;
}

int main() {
    spn::spn spn(s_box);

    spn::data input, output;
    int count = 0;
    while( std::cin >> std::hex >> input >> std::hex >> output ) {
        count++;
        unsigned pre_S3 = (output >> 4) % 16;
        unsigned pre_S1 = (output >> 12);
        /* These are the values of the outputs
         * before undoing the last parts of the SPN.
         */
        bool X16 = input & 0b1;

        for( int i = 0; i < 256; i++ ) {
            unsigned high = i / 16;
            unsigned low = i % 16;
            bool U1 = spn.s_box_inv[pre_S1 ^ high] & 0b1000;
            bool U9 = spn.s_box_inv[pre_S3 ^ low] & 0b1000;

            votes[i] += U1 ^ U9 ^ X16;
        }
    }
    // Find the most distant from the mean
    int mean = count/2;
    int best = 0;
    int best_index = 0;
    for( int i = 0; i < 256; i++ )
        if( abs(votes[i] - mean) > best ) {
            best_index = i;
            best = abs(votes[i] - mean);
        }

    std::cout << std::hex << best_index << std::endl;
}
