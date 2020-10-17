## Documentation for libdfloat

### Data Types:

libdfloat defines the following data types:

`dfloat16_t`: 16-bit decimal float with 8-bit mantissa and exponent

`dfloat32_t`: 32-bit decimal float with 16-bit mantissa and exponent

`dfloat64_t`: 64-bit decimal float with 32-bit mantissa and exponent

`dfloat128_t`: 128-bit decimal float with 64-bit mantissa and exponent

The proper way to declare a `dfloat` is to specify a decimal literal in
string format and convert it to a `dfloat` using one of the `dfloatN_atof()`
functions.

---------------------------------------------------------------------------

### Standard Functions:

In the following function definitions, the capital letters *M* and *N* stand
for integers, either 16, 32, 64, or 128. These numbers can be substituted
as desired, as there are macros that generate the corresponding functions.

(Example: `dfloat64_add()`, no spaces)

libdfloat defines the following groups of functions:

`void dfloatN_add( dfloatN_t *dst, dfloatN_t *src )`

Add *N*-bit `src` and `dst` operands together and store the result in `dst`.

`void dfloatN_sub( dfloatN_t *dst, dfloatN_t *src )`

Subtract *N*-bit `src` from *N*-bit `dst` and store the result in `dst`.

`void dfloatN_mul( dfloatN_t *dst, dfloatN_t *src )`

Multiply *N*-bit `src` and `dst` operands together and store the result in `dst`.

`void dfloatN_div( dfloatN_t *dst, dfloatN_t *src, int precision )`

Divide *N*-bit `dst` by `src` and store the result in `src`, with up to `precision`
digits past the decimal point.

`int dfloatN_cmp( dfloatN_t *df1, dfloatN_t *df2 )`

Compares *N*-bit operands `df1` and `df2`.

Returns:

`1` if `df1 > df2`

`-1` if `df1 < df2`

`0` if `df1 == df2`

`dfloatN_t *dfloatN_atof( char *str )`

Reads an *N*-bit `dfloat` from input string `str`.

Input string must be in the following format (BNF):

`[-]<digit><digit>*[.<digit><digits>*]`

`char *dfloatN_ftoa( dfloatN_t *df )`

Generates a string representation of *N*-bit `dfloat` value `df`.

`void dfloatN_cpy( dfloatN_t *dst, dfloatN_t *src )`

Copies the mantissa and exponent from `src` to `dst`.

`dfloatN_t *dfloatM_castN( dfloatM *src )`

Takes a `dfloat` of size `M` and typecasts it, returning a `dfloat` of size `N`.

Cast functions where `M == N` have not been implemented as the author
saw no need for such functions.

*Note: Overflow errors may occur if the result of an operation is too
large to fit into the designated space. These will not be reported by
the compiler and will simply result in incorrect values. It is up to
the programmer to account for these overflows.*

---------------------------------------------------------------------------

### Free Functions:

As of Version 0.2, libdfloat has versions of some of the above functions
that free their source operands, allowing the user to build more complex
expressions using these functions without having to worry about lost
objects accumulating. These "free versions" are as follows:

`dfloatN_t *dfloatN_addf( dfloatN_t *arg1, dfloatN_t *arg2 )`

Adds `arg1` and `arg2` and returns the result

`dfloatN_t *dfloatN_subf( dfloatN_t *arg1, dfloatN_t *arg2 )`

Subtracts `arg2` from `arg1` and returns the result

`dfloatN_t *dfloatN_mulf( dfloatN_t *arg1, dfloatN_t *arg2 )`

Multiplies `arg1` by `arg2` and returns the result

`dfloatN_t *dfloatN_divf( dfloatN_t *arg1, dfloatN_t *arg2, int precision )`

Divides `arg1` by `arg2` with the given precision and returns the result

`int dfloatN_cmpf( dfloatN_t *arg1, dfloatN_t *arg2 )`

Like `dfloatN_cmp()`, but frees the source operands

`char *dfloatN_ftoaf( dfloat_t *src )`

Like `dfloatN_ftoa()`, but frees the source operand

`dfloatN_t *dfloatM_castNf( dfloatM_t *src )`

Like `dfloatM_castN()`, but frees the source operand

*Note: Because these functions free their operands, they should not be
used on variables. They should only be used on immediate operands,
where the output of one function is directly supplied as a parameter to
another.*

Example:

`dfloat64_t *sum = dfloat64_addf( dfloat64_atof( "1.2" ), dfloat64_atof( "3.4" ) );`

--------------------------------------------------------------------------

Any questions or problems? Feel free to contact me at the following:

Github: github.com/PsychoCod3r

Personal email: acidkicks@protonmail.com

Submit issues at github.com/PsychoCod3r/libdfloat
