#include <stdio.h>
#include <ctype.h>

int main( int argc, char** argv ) {
    if( argc != 3 ) {
        fprintf( stderr, "Wrong number of arguments.\n" );
        return 1;
    }

    int a, b;
    sscanf( argv[1], "%i", &a );
    sscanf( argv[2], "%i", &b );

    int inv = -1;
    for( int i = 1; i < 26; i++ )
        if( a * i % 26 == 1 ) {
            inv = i;
            break;
        }

    if( inv == -1 ) {
        fprintf( stderr, "a = %i is not invertible (modulo 26).\n", a );
        return 2;
    }

    int c;
    while( (c = getchar()) != EOF ) {
        if( isalpha(c) ) {
            c = tolower(c) - 'a';
            c = (c - b + 26) * inv % 26 + 'a';
        }
        putchar(c);
    }
    return 0;
}
