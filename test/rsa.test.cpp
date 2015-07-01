#include "rsa/rsa.hpp"
#include <catch.hpp>

TEST_CASE( "RSA algorithm", "[rsa]" ) {
    int p = 101, q = 113, b = 3533;
    rsa::public_key<int> public_key = rsa::build_public_key( p, q, b );
    CHECK( public_key.n == 11413 );
    CHECK( public_key.b == 3533 );

    rsa::private_key<int> private_key = rsa::build_private_key( p, q, b );
    CHECK( private_key.n == 11413 );
    CHECK( private_key.a == 6597 );

    int x = 9726;
    CHECK( public_key.encrypt(x) == 5761 );
    CHECK( private_key.decrypt(5761) == x );
}
