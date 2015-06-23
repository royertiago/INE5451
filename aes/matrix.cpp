#include <iostream>
#include <ostream>
#include "aes/matrix.h"

namespace aes {
    matrix operator+( const matrix & a, const matrix & b ) {
        matrix m;
        for( int i = 0; i < 4; i++ )
        for( int j = 0; j < 4; j++ )
            m[i][j] = a[i][j]+b[i][j];
        return m;
    }

    matrix operator*( const matrix & a, const matrix & b ) {
        matrix m;
        for( int i = 0; i < 4; i++ )
        for( int j = 0; j < 4; j++ )
        for( int k = 0; k < 4; k++ )
            m[i][j] = m[i][j] + a[i][k]*b[k][j];
        return m;
    }

    std::istream & operator>>( std::istream & is, matrix & m ) {
        for( int j = 0; j < 4; j++ )
            for( int i = 0; i < 4; i++ ) {
                unsigned char value = 0;
                char c;

                // Parse the higher half-byte
                is >> c;
                if( c >= '0' && c <= '9' )
                    value += (c - '0') << 4;
                else if( c >= 'a' && c <= 'f' )
                    value += (c - 'a' + 10) << 4;
                else if( c >= 'A' && c <= 'F' )
                    value += (c - 'A' + 10) << 4;
                else {
                    is.setstate( std::ios::failbit );
                    return is;
                }

                // Parse the lower half-byte
                is >> c;
                if( c >= '0' && c <= '9' )
                    value += c - '0';
                else if( c >= 'a' && c <= 'f' )
                    value += c - 'a' + 10;
                else if( c >= 'A' && c <= 'F' )
                    value += c - 'A' + 10;
                else {
                    is.setstate( std::ios::failbit );
                    return is;
                }
                m[i][j] = polynomial(value);
            }
        return is;
    }
    std::ostream & operator<<( std::ostream & os, const matrix & m ) {
        const char * separator = "";
        for( int j = 0; j < 4; j++ )
            for( int i = 0; i < 4; i++ ) {
                os << separator << std::hex << (int) m[i][j].data;
                separator = " ";
            }
        return os;
    }
}
