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
#else
int permutation_s[16] = {
    14, 4, 13, 1, 2, 15, 11, 8,
    3, 10, 6, 12, 5, 9, 0, 7
};

int permutation_s_inv[16] = {
    14, 3, 4, 8, 1, 12, 10, 15,
    7, 13, 9, 6, 11, 2, 0, 5
};
#endif

int permutation_p[16] = {
    1, 5, 9, 13, 2, 6, 10, 14,
    3, 7, 11, 15, 4, 8, 12, 16
};

int * permutation_p_inv = permutation_p;

void sub_keys(std::vector<word> & sub_keys, dword key)
{
    for (int r = 1; r < 6; r++) {
        word kr = (key << (4*r-4)) >> 16;
        sub_keys.insert( sub_keys.end(), kr);
    }
}

void sub_keys_inv(std::vector<word> & sub_keys, dword key)
{
    ::sub_keys(sub_keys,key);
    sub_keys = std::vector<word>(sub_keys.rbegin(), sub_keys.rend());
}

word execute_s_box (word u)
{
    word v = 0;

    for (int i = 0; i < 4; i++)
    {
        word s_index = ((u << i*4) >> 12) & 0xF;
        word nibble = permutation_s [s_index];
        v = v | (nibble << (3-i)*4);
    }

    return v;
}

word execute_s_box_inv (word u)
{
    word v = 0;

    for (int i = 0; i < 4; i++)
    {
        word s_index = ((u << i*4) >> 12) & 0xF;
        word nibble = permutation_s_inv [s_index];
        v = v | (nibble << (3-i)*4);
    }

    return v;
}

word execute_permutation (word input)
{
    std::bitset<16> w;
    std::bitset<16> v(input);

    for (int i = 0; i < 16; i++)
        w[16 - permutation_p[i]] = v[15 - i];

    return w.to_ulong();
}

word execute_permutation_inv (word input)
{
    std::bitset<16> w;
    std::bitset<16> v(input);

    for (int i = 0; i < 16; i++)
        w[16 - permutation_p_inv[i]] = v[15 - i];

    return w.to_ulong();
}

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
