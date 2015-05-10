INE5451 - Tópicos especiais em Algoritmos I - Introdução à Criptoanálise
========================================================================

(*Special Topics in Algorithms I - Introduction to Cryptanalysis*)

Set of tools used to aid the resolution of exercises
in the INE5451 course.


About the course
----------------

"INE5451" is a course whose syllabus change in every edition.
The 2015.1 edition, lectured by Daniel Santana de Freitas,
was about cryptanalysis.

Some of the exercises required us to break cyphered texts
ciphered with (say) affine ciphers.
This repository contains tools that automate verifications
like frequency analysis.

Building
========

This repository contains a makefile and can be built with GNU make.
Just type

    make

in the command line.

You will need a C++ compiler with support to C++14.
I have tested with `gcc 4.9.2` and with `clang 3.6.0`.

The class `letter_scanner` also depends upon Boost.Locale.
The easiest way of getting it is via your distribution's repositories;
e.g.

    sudo apt-get install libboost-locale-dev

(The makefile is already set up to link with `boost_locale`,
 assuming you got Boost.Locale this way.)
