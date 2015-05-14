/* Partial implementation of the Enigma machine,
 * without the ringstellung nor the plugboard.
 */
#include <iostream>
#include <string>
#include <vector>
#include "enigma/machine.hpp"

constexpr char rotorI[] = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
constexpr char rotorII[] = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
constexpr char rotorIII[] = "BDFHJLCPRTXVZNYEIWGAKMUSQO";
constexpr char rotorIV[] = "ESOVPZJAYQUIRHXLNFTGKDCMWB";
constexpr char rotorV[] = "VZBRGITYUPSDNHLXAWMJQOFECK";
constexpr char reflectorA[] = "EJMZALYXVBWFCRQUONTSPIKHGD";
constexpr char reflectorB[] = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
constexpr char reflectorC[] = "FVPJIAOYEDRZXWGCTKUQSBNMHL";

constexpr const char * rotor_str[] = {
    rotorI, rotorII, rotorIII, rotorIV, rotorV
};
constexpr const char * reflectors[] = {
    reflectorA, reflectorB, reflectorC
};
constexpr unsigned notch[] = {
    16, 4, 21, 9, 25
};

enigma::rotor rotors[] = {
    enigma::rotor( rotor_str[0], notch[0] ),
    enigma::rotor( rotor_str[1], notch[1] ),
    enigma::rotor( rotor_str[2], notch[2] ),
    enigma::rotor( rotor_str[3], notch[3] ),
    enigma::rotor( rotor_str[4], notch[4] ),
};

bool is_vowel( enigma::index i ) {
    return i == 'A' - 'A' ||
           i == 'E' - 'A' ||
           i == 'I' - 'A' ||
           i == 'O' - 'A' ||
           i == 'U' - 'A';
}

double index_of_coincidence( const std::vector<enigma::index> & text ) {
    int count[26] = {0};
    for( auto c : text )
        count[c]++;
    int sum = 0;
    for( int i : count )
        sum += i * (i - 1);
    return sum / double(text.size() * (text.size() - 1));
}

std::string to_string( std::vector<enigma::index> plain ) {
    std::string out(plain.size(), 'A');
    for( int i = 0; i < plain.size(); i++ )
        out[i] += plain[i];
    return out;
}

int main() {
    std::string input, part;
    while( std::getline(std::cin, part) )
        input += part;

    std::cout << "Breaking the cipher for " << input << std::endl;

    std::vector<enigma::index> text(input.size());
    std::vector<enigma::index> plain(input.size());
    for( int i = 0; i < text.size(); i++ )
        text[i] = input[i] - 'A';

    enigma::machine E( reflectorB );
    for( int r1 = 0; r1 < 5; r1++ )
    for( int r2 = 0; r2 < 5; r2++ )
    for( int r3 = 0; r3 < 5; r3++ ) {
        if( r1 == r2 || r1 == r3 || r2 == r3 )
            continue;
        std::cout << "Trying rotors " << r1 << "-" << r2 << "-" << r3 << "\n";

        E.set_rotors(rotors[r1], rotors[r2], rotors[r3]);

        for( int d1 = 0; d1 <= 25; d1++ )
        for( int d2 = 0; d2 <= 25; d2++ )
        for( int d3 = 0; d3 <= 25; d3++ ) {
            E.set_key( d1, d2, d3 );

            for( int i = 0; i < text.size(); i++ )
                plain[i] = E.cipher(text[i]);

            double index = index_of_coincidence(plain);
            if( index > 0.05 )
                std::cout << "Key "
                    << (char) (d1 + 'A')
                    << (char) (d2 + 'A')
                    << (char) (d3 + 'A')
                    << " - Index: " << index << '\n'
                    << to_string(plain) << '\n';
        }
    }
}
