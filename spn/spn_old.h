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

#endif
