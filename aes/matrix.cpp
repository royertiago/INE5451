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
}
