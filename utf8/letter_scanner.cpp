#include <boost/locale.hpp>
#include <istream>
#include <string>
#include "letter_scanner.h"

namespace {
    class letter_scanner_initializer {
        static letter_scanner_initializer instance;
        letter_scanner_initializer() {
            boost::locale::generator gen;
            std::locale::global( gen("") );
        }
    };
    letter_scanner_initializer letter_scanner_initializer::instance;
} // anonymous namespace

letter_scanner::letter_scanner( std::istream & file_source ) :
    file(file_source),
    buffer(""),
    buffer_ptr(buffer.end())
{}

letter_scanner::~letter_scanner() {
}

int letter_scanner::next() {
    /* First, we will iterate until the end of the buffer,
     * returning if we find any valid character.
     */
    while( buffer_ptr != buffer.end() ) {
        char c = *buffer_ptr++;
        if( c >= 'a' && c <= 'z' )
            return c;
    }

    /* No valid characters found, replace the buffer,
     * and try again.
     */
    if( !std::getline( file, buffer ).good() )
        return -1;

    /* First, run boost::locale::fold_case (to map e.g. ß to 'ss')
     * then run boost::locale::to_lower,
     * and, finally, boost::locale::normalize (to separate letters from accents).
     */
    buffer = boost::locale::fold_case( buffer );
    buffer = boost::locale::to_lower( buffer );
    buffer = boost::locale::normalize( buffer, boost::locale::norm_nfkd );

    /* Now, reset the buffer_ptr and use recursion to try again.
     */
    buffer_ptr = buffer.begin();
    return next();
}
