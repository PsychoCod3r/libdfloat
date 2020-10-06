libdfloat is a floating point library for C, designed to address the
issue of rounding errors when converting floating point numbers between
a textual format (e.g. in a CSV file) and the data type used by C. The
issue is that floating point numbers are typically represented in a
decimal format in the data file, but in the C program they are represented
in a binary format, and rounding errors when converting between the
two can lead to imprecise values being written back to the file when
data processing is finished. libdfloat allows for exact representation of
decimal numbers, where accuracy and precision are preserved through every
step of the program. It is designed with CSV and other data files
in mind.  Functions are provided for reading and writing decimal floats
to/from files, as well as performing common arithmetic operations. These
arithmetic operations are performed in roughly the same way arithmetic
is done on floating point numbers in the IEEE-754 standard, except that
everything is in decimal format.

To compile:
Place dfloat.c and dfloat.h in the same directory as your project.
Create linkable object file: gcc -c dfloat.c
#include "dfloat.h" in any C files that use libdfloat.
Make linkable object files from your own project files.
Run the following command: gcc -o project_name *.o

Be sure to credit me and include the Michael Warren FSL with any project
that uses libdfloat. See the license for details.

I will be adding a Makefile in the future to automate this whole process,
and hopefully I can find a way to make libdfloat into a shared object
file on all major platforms.


Included files:
README: This file
LICENSE: The Michael Warren FSL under which this software is released
dfloat.h: Header file containing typedefs and function prototypes
dfloat.c: C module containing all function definitions
doc.txt: Documentation for all types and functions defined in libdfloat
change.log: Log of changes made with each release of libdfloat
