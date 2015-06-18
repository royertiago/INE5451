#ifndef AES_POLYNOMIAL_H
#define AES_POLYNOMIAL_H

/* Struct that represents a polynomial in the finite field GF(2^8).
 */

namespace aes {
    struct polynomial {
        unsigned char data;
    };

    polynomial operator+( polynomial, polynomial );
    polynomial operator-( polynomial, polynomial );
    polynomial operator*( polynomial, polynomial );
    polynomial operator/( polynomial, polynomial );
    polynomial operator==( polynomial, polynomial );
    polynomial operator!=( polynomial, polynomial );
}

#endif // AES_POLYNOMIAL_H
