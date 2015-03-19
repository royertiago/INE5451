/* Computes the coincidence index, for Vigenère cipher cryptanalysis.
 * Command line argument: guessed size of key.
 */
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <vector>

const char * file_name = nullptr;
double probabilities[27]; // Add extra double as sentinel.

bool read_file() {
    FILE * file = fopen( file_name, "r" );
    if( file == nullptr ) {
        fprintf( stderr, "Error opening %s: %s", file_name, strerror(errno) );
        return false;
    }

    int i = 0;
    while( fscanf( file, "%lf", &probabilities[i++] ) != EOF )
        if( i >= 27 ) {
            fprintf( stderr, "File %s is too long.\n", file_name );
            return false;
        }

    if( i <= 26 ) {
        fprintf( stderr, "Error reading file %s.\n", file_name );
        return false;
    }

    return true;
}

void print_coincidence( int index, const std::vector<unsigned>& vec ) {
    unsigned over = 0, sum = 0;
    for( auto i : vec ) {
        over += i * (i - 1);
        sum += i;
    }
    printf( "[%i] = %.3lf\n", index, over / double(sum * (sum - 1)) );

    if( file_name != nullptr ) {
        for( int i = 0; i < 26; i++ ) {
            double total = 0;
            for( int j = 0; j < 26; j++ )
                total += probabilities[(j-i+26)%26] * vec[j] / sum;
            printf( "%c:%.3lf ", 'A' + i, total );
        }
        printf( "\n" );
    }
}

int main( int argc, char ** argv ) {
    if( argc != 2 && argc != 3 ) {
        fprintf( stderr, "Usage: %s <key size> [<probability file>]\n", argv[0] );
        return 1;
    }
    int size = -1;
    sscanf( argv[1], "%d", &size );
    if( size < 1 ) {
        fprintf( stderr, "%s is an invalid number.\n", argv[1] );
        return 2;
    }

    if( argc == 3 ) {
        file_name = argv[2];
        if( !read_file() )
            return 3;
    }

    std::vector< std::vector<unsigned> > coincidence(
        size, std::vector<unsigned>(26)
    );

    int c;
    int i = -1;
    while( (c = getchar()) != EOF )
        if( isalpha(c) )
            coincidence[i = (i+1) % size][tolower(c) - 'a']++;

    for( i = 0; i < size; i++ )
        print_coincidence( i, coincidence[i] );

    return 0;
}
