/* Toy example for the RSA algorithm.
 * This function decyphers 3-char words.
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include "rsa/rsa.hpp"

rsa::public_key<int> public_key;
rsa::private_key<int> private_key;

std::string decypher( int x ) {
    x = private_key.decrypt( x );
    int a = x % 26;
    x /= 26;
    int b = x % 26;
    int c = x / 26;
    return std::string{ (char)(c + 'A'), (char)(b + 'A'), (char)(a + 'A') };
}

int main( int argc, char ** argv ) {
    if( argc != 4 ) {
        std::cerr << "Usage: char_rsa p q b\n";
        return 1;
    }

    int p = std::atoi( argv[1] );
    int q = std::atoi( argv[2] );
    int b = std::atoi( argv[3] );

    public_key = rsa::build_public_key( p, q, b );
    private_key = rsa::build_private_key( p, q, b );

    std::clog << "a == " << private_key.a << std::endl;

    int x;
    while( std::cin >> x )
        std::cout << decypher( x );
}
