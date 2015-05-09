Makefile naming conventions
===========================

`file.cpp`: Some file that contains source code of implementations.
If this file has a `main` function,
ideally it should be the only function of the file.

`file.h`: Some file that contains mainly declarations.

`file.hpp`: Some file that contains mainly template code.

`file.dep.mk`: Makefile dependency file.
Generated and updated automatically.
These are only generated for cpp files.

`file.o`: Intermediate object file, created from a .cpp.
Generated and updated automatically.

`file`: A program.
Generated and updated automatically.
The makefile generates it if `file.cpp` contains a `main` function.

Other file types
----------------

`language.freq`: A newline-separated list of floating point values.
The i-th line corresponds to the frequency of appearance
of the i-th letter in the respectitve language.
This file is used by coincidence.cpp.
