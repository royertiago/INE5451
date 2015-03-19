/* Deciphers vigenère texts, given key. */
#include <ctype.h>
#include <stdio.h>

int main( int argc, char ** argv ) {
    if( argc != 2 ) {
        fprintf( stderr, "Usage: %s <Vigenère key>\n", argv[0] );
        return 1;
    }

    char * key = argv[1];
    int c;
    while( (c = getchar()) != EOF ) {
        char a = c;
        if( isalpha(c) ) {
            a = tolower(c) - 'a';
            a += 26;
            a -= tolower(*key) - 'a';
            a %= 26;
            a += 'a';
            key++;
            if( *key == '\0' )
                key = argv[1];
        }
        putchar(a);
    }

    return 0;
}
