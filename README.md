**Introduction:**

libdfloat is a floating point library for C that represents decimal
numbers precisely with no rounding errors. It provides four types for
representing decimal floating point numbers, as well as functions for
reading/writing these numbers to/from strings and performing arithmetic
operations with the numbers. These arithmetic operations are carried out
in roughly the same way arithmetic is done on floating point numbers in
the IEEE-754 standard, except the numbers have a decimal base.

---------------------------------------------------------------------------

**Why did I write this library?**

Reading and writing decimal numbers from/to a CSV database or other text
file can result in problems when numbers are represented in a binary
format by the C program. Rounding errors can occur, resulting in values
getting truncated during conversion between the decimal and binary
bases. Also, the textual representation of floating point numbers via
a function like `fprintf()` can often have trailing zeros and other
problems that make a number difficult to write back to the file in the
same format it was read from. The goal of libdfloat is to preserve the
representation of decimal numbers so that they are written back to the
text file in the same format they were in when read.

---------------------------------------------------------------------------

**Who is this library for?**

libdfloat is intended for programmers who work with text-based flat-file
databases in their programs, but it can theoretically be used by anyone
who wants to do precise calculations with floating point numbers in a
decimal base.

---------------------------------------------------------------------------

**Files included in this repository:**

- README: This file

- LICENSE - the Michael Warren Free Software License under which this and
  all my other software is released

- dfloat.h: Header file containing typedefs and function prototypes

- dfloat.c: C module containing all function definitions

- doc.txt: Documentation for all types and functions defined in libdfloat

- change.log: Log of changes made with each release of libdfloat

- syntax.vim: Additional syntax highlighting for Vim users

---------------------------------------------------------------------------

**Dependencies:**

None

---------------------------------------------------------------------------

**Installation and usage instructions:**

1. Download libdfloat using the clone feature.

2. Run the following commands:

   `gcc -c dfloat.c`

   `ar -rsv libdfloat.a dfloat.o`

3. To link the libdfloat library to a project, run the following command:

   `gcc myproject -L dir -ldfloat`

   (where `dir` is the directory containing libdfloat.a)

---------------------------------------------------------------------------

If you have any feedback or want to report any issues, please don't
hesitate to notify me. You are helping me make these libraries
better. This library is currently in its alpha stage and needs people
to alpha-test it. Your participation is greatly appreciated.
