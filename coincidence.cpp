/* Computes the coincidence index, for Vigenère cipher cryptanalysis.
 * Command line argument: guessed size of key.
 */
#include <stdio.h>
#include <ctype.h>
#include <vector>

double compute_coincidence( const std::vector<unsigned>& vec ) {
    unsigned over = 0, sum = 0;
    for( auto i : vec ) {
        over += i * (i - 1);
        sum += i;
    }
    return over / double(sum * (sum - 1));
}

int main( int argc, char ** argv ) {
    if( argc != 2 ) {
        fprintf( stderr, "Usage: %s <probable Vigenère key size>\n", argv[0] );
        return 1;
    }
    int size = -1;
    sscanf( argv[1], "%d", &size );
    if( size < 1 ) {
        fprintf( stderr, "%s is an invalid number.\n", argv[1] );
        return 2;
    }

    std::vector< std::vector<unsigned> > coincidence(
        size, std::vector<unsigned>(26)
    );

    int c;
    int i = 0;
    while( (c = getchar()) != EOF )
        if( isalpha(c) )
            coincidence[i = (i+1) % size][tolower(c) - 'a']++;

    for( i = 0; i < size; i++ )
        printf( "[%i] = %.3lf\n", i, compute_coincidence(coincidence[i]) );

    return 0;
}
