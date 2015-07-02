#define TRABALHO_2

#include "spn.h"
#include <iostream>
#include <bitset>

using namespace std;

void print_NL(int**);
void calcular_NL();
int NL(const bitset<4> & a, const bitset<4> & b);

int main(void) {
    // letra a)
    calcular_NL();

    // letra b)
    return 0;
}

int NL(const bitset<4> & a, const bitset<4> & b) {
    int count = 0;
    for (int i = 0; i < 16; i++) {
        bitset<4> x = bitset<4>(i);
        x &= a;
        bitset<4> y =(permutation_s[i]);
        y &= b;

        bool ocorrencia = (x[0]^x[1]^x[2]^x[3]^y[0]^y[1]^y[2]^y[3]==0);

        count = (ocorrencia ? count + 1 : count);
    }

    return count;
}

void calcular_NL() {

    cout << "n\t0\t1\t2\t3\t4\t5\t6\t7\t8\t9\tA\tB\tC\tD\tE\tF" << endl;
    for (int i = 0; i < 16; i++) {
        cout << i << "\t";
        for (int j = 0; j < 16; j++)
            cout << NL(bitset<4>(i),bitset<4>(j)) << "\t";
        cout << endl;
    }
}
