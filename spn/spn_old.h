#ifndef __SPN_H_
#define __SPN_H_
#include <vector>
#include <bitset>

typedef std::uint_least32_t dword;
typedef std::uint_least16_t word;

#ifdef TRABALHO_2
/* Exercicio 1 / Trabalho 2 */
int permutation_s[16] = {
    8, 4, 2, 1, 12, 6, 3, 13,
    10, 5, 14, 7, 15, 11, 9, 0
};

int permutation_s_inv[16] = {
    15, 3, 2, 6, 1, 9, 5, 11,
    0, 14, 8, 13, 4, 7, 10, 12
};
#endif

word spn_cypher (word plain, dword key)
{
    //creating sub keys
    std::vector<word> keys;
    sub_keys(keys, key);

    word wr = plain; // w0
    word ur,vr;

    for (int r = 0; r < 3; r++) {
        ur = wr ^ keys[r];
        vr = execute_s_box(ur);
        wr = execute_permutation(vr);
    }

    //last round does'nt have permutation
    ur = wr ^ keys[3];
    vr = execute_s_box(ur);

    word crypt = vr ^ keys[4];

    return crypt;
    //TODO: Test this function
}


word spn_decrypt (word crypt, dword key)
{
    //creating sub keys
    std::vector<word> keys;
    sub_keys_inv(keys, key);

    word wr = crypt; // w0
    word ur,vr;

    ur = wr ^ keys[0];
    vr = execute_s_box_inv(ur);

    for (int r = 1; r < 4; r++) {
        ur = wr ^ keys[r];
        wr = execute_permutation_inv(ur);
        vr = execute_s_box_inv(wr);
    }

    //last round does'nt have permutation


    word plain = vr ^ keys[4];

    return plain;
    //TODO: Test this function
}

#endif
