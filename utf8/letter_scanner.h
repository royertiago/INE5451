#ifndef UTF8_LETTER_SCANNER_H
#define UTF8_LETTER_SCANNER_H

/* Class that reads a file and "abstracts away" diacritics and UTF8 encoding.
 * It scans a UTF8-encoded file and returns only single letters.
 * letter_scanner::next() does "all the magic":
 *  - converts every letter to lower case;
 *  - removes all diacritics;
 *  - treats the german eszett (ß) as two 's',
 *    each returned in one call to letter_scanner::next;
 *  - simply discards any other character (e.g. punctuation and digits.)
 */

#include <iosfwd>
#include <string>

class letter_scanner {
    std::istream & file;
    std::string buffer;
    std::string::iterator buffer_ptr;

public:
    /* Altough I marketed the letter_scanner as geared toward file scanning,
     * it can, in fact, work with any std::istream.
     */
    letter_scanner( std::istream & file_source );
    ~letter_scanner();

    /* Gets the next character in the file,
     * according to the description above.
     *
     * Returns -1 if there is no more characters to extract.
     */
    int next();
};

#endif // UTF8_LETTER_SCANNER_H
