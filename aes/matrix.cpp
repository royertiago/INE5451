#include <iostream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include "aes/matrix.h"

namespace aes {
    matrix::matrix( const std::string & str ) {
        std::stringstream stream(str);
        stream >> *this;
        if( !stream )
            throw std::invalid_argument( "aes::matrix: Invalid string" );
    }

    matrix::matrix( std::initializer_list<polynomial> list ) {
        auto it = list.begin();
        polynomial * ptr = &data[0][0];
        for( int i = 0; i < 16 && it != list.end(); ++i, ++ptr, ++it )
            *ptr = *it;
        if( it != list.end() )
            throw std::out_of_range( "aes::matrix: Initializer list is too large" );
    }
            
    matrix::matrix( std::initializer_list<unsigned> list ) {
        auto it = list.begin();
        polynomial * ptr = &data[0][0];
        for( int i = 0; i < 16 && it != list.end(); ++i, ++ptr, ++it ) {
            if( *it > 255 )
                throw std::out_of_range( "aes::matrix: \"byte\" is greater than 256" );

            *ptr = polynomial(*it);
        }
        if( it != list.end() )
            throw std::out_of_range( "aes::matrix: Initializer list is too large" );
    }

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
