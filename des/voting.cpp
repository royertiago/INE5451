#include "des/primitives.h"
#include "voting.h"

namespace des {

    unsigned char votes::vote() const {
        unsigned char vote = 64;
        int max_votes = 0;
        for( int i = 0; i < 64; i++ )
            if( votes[i] > max_votes ) {
                max_votes = votes[i];
                vote = i;
            }
            else if( votes[i] == max_votes )
                vote = 64;
        return vote;
    }

    void vote( unsigned char input1, unsigned char input2, unsigned char output_xor,
        votes& voting_data, int s )
    {
        unsigned char input_xor = input1 ^ input2;
        int votes = 0;
        for( unsigned i = 0; i < 64; i++ ) {
            int j = i ^ input_xor;
            /* j ^ i == input_xor.
             */
            if( (s_box[s][i] ^ s_box[s][j]) == output_xor ) {
                voting_data.votes[i ^ input1]++;
                votes++;
            }
        }
    }
}
