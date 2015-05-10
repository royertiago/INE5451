/* Incomplete implementation of letter_scanner.h.
 */
#include <istream>
#include <string>
#include "letter_scanner.h"

letter_scanner::letter_scanner( std::istream & file_source ) :
    file(file_source),
    buffer(""),
    buffer_ptr(buffer.end())
{}

letter_scanner::~letter_scanner() {
}

int letter_scanner::next() {
    if( buffer_ptr != buffer.end() )
        return *buffer_ptr++;

    if( !std::getline( file, buffer ).good() )
        return -1;

    buffer_ptr = buffer.begin();
    return next();
}
