/****************************************************
 * libdfloat, version 0.1 Alpha                     *
 * Description: Implements floating point numbers   *
 *              with exact decimal representations  *
 * Current file: All libdfloat function definitions *
 * Author: Michael Warren, a.k.a. Psycho Cod3r      *
 * Date: October 2020                               *
 * License: Micheal Warren FSL                      *
 ****************************************************/

// Note: This file is a work in progress. Don't expect it to work.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dfloat.h"

// TODO: TEST
// Copies the second operand to the first operand
#define dfloatN_cpy( small, big )\
void dfloat ## big ## _cpy( dfloat ## big ## _t *dst, dfloat ## big ## _t *src ){\
	dst->mantissa = src->mantissa;\
	dst->exponent = src->exponent;\
}

dfloatN_cpy( 8, 16 )
dfloatN_cpy( 16, 32 )
dfloatN_cpy( 32, 64 )
dfloatN_cpy( 64, 128 )

// TODO: TEST
// Casts a dfloat of width M to a dfloat of width N
#define dfloatM_castN( smallM, bigM, smallN, bigN )\
dfloat ## bigN ## _t *dfloat ## bigM ## _cast ## bigN ( dfloat ## bigM ##_t *src ){\
	dfloat ## bigN ## _t *dst;\
	dst = (dfloat ## bigN ## _t *) malloc( sizeof( dfloat ## bigN ## _t ) );\
	dst->mantissa = (int ## smallN ## _t) src->mantissa;\
	dst->exponent = (int ## smallN ## _t) src->exponent;\
	return dst;\
}

dfloatM_castN( 8, 16, 16, 32 )
dfloatM_castN( 8, 16, 32, 64 )
dfloatM_castN( 8, 16, 64, 128 )

dfloatM_castN( 16, 32, 8, 16 )
dfloatM_castN( 16, 32, 32, 64 )
dfloatM_castN( 16, 32, 64, 128 )

dfloatM_castN( 32, 64, 8, 16 )
dfloatM_castN( 32, 64, 16, 32 )
dfloatM_castN( 32, 64, 64, 128 )

dfloatM_castN( 64, 128, 8, 16 )
dfloatM_castN( 64, 128, 16, 32 )
dfloatM_castN( 64, 128, 32, 64 )

// TESTED AND WORKING
// Adds the two operands and stores the result in the first operand
#define dfloatN_add( small, big )\
void dfloat ## big ## _add( dfloat ## big ## _t *dst, dfloat ## big ## _t *src ){\
	int i;\
	long log_max, log_diff;\
	/* log_max gives the maximum number of times  */\
	/* you can multiply by 10 before overflowing. */\
	int ## small ## _t src_mantissa, dst_mantissa;\
	int ## small ## _t src_magnitude, dst_magnitude;\
	int ## small ## _t smaller_exponent;\
	int ## small ## _t larger_magnitude;\
	int ## small ## _t target_mantissa, target_exponent;\
	int ## small ## _t larger_mag_exponent;\
	src_mantissa = src->mantissa;\
	dst_mantissa = dst->mantissa;\
	src_magnitude = ceil( log10( abs( src->mantissa ) * pow( 10, src->exponent ) ) );\
	dst_magnitude = ceil( log10( abs( dst->mantissa ) * pow( 10, dst->exponent ) ) );\
	/* magnitude is the number of digits before the decimal point */\
	/* or the number of zeros after the decimal point if negative */\
	if( src_mantissa == 1 )\
		src_magnitude++;\
	if( dst_mantissa == 1 )\
		dst_magnitude++;\
	/* Increment accounts for exact powers of 10 */\
	smaller_exponent = (src->exponent < dst->exponent)?src->exponent:dst->exponent;\
	/* A lower exponent indicates a higher degree of precision for a number. */\
	larger_magnitude = (src_magnitude > dst_magnitude)?src_magnitude:dst_magnitude;\
	larger_mag_exponent = (src_magnitude > dst_magnitude)?src->exponent:dst->exponent;\
\
	/* Next part figures out the target exponent for each number to    */\
	/* be shifted to so they can be added.                             */\
	/* If log_diff <= log_max then the exponent should be log_diff.    */\
	/* Otherwise (if there's overflow and some digits need to be cut   */\
	/* off) the exponent should be equal to the exponent of the number */\
	/* with the larger magnitude, minus abs(log_diff-log_max).         */\
	log_max = ceil( log10( ((int ## small ## _t) 1) << (small-3) ) );\
	log_diff = larger_magnitude - smaller_exponent;\
	target_exponent = (log_diff <= log_max)?smaller_exponent:larger_mag_exponent-abs(log_diff-log_max)+1;\
\
	/* Shift both src and dst until they have the same exponent:       */\
	/* Changes to mantissa and exponent should cancel each other out.  */\
	src_mantissa *= pow( 10, src->exponent - target_exponent );\
	dst_mantissa *= pow( 10, dst->exponent - target_exponent );\
\
	target_mantissa = src_mantissa + dst_mantissa;\
\
	/* Count number of trailing zeros and adjust */\
	/* mantissa and exponent accordingly:        */\
	for( i = 0; i < log_max; i++ ){\
		if( target_mantissa % 10 ) break;\
		target_mantissa /= 10;\
		target_exponent++;\
	}\
	dst->mantissa = target_mantissa;\
	dst->exponent = target_exponent;\
}

dfloatN_add( 8, 16 )
dfloatN_add( 16, 32 )
dfloatN_add( 32, 64 )
dfloatN_add( 64, 128 )

// TODO: TEST
// Subtracts the second operand from the first operand
#define dfloatN_sub( small, big )\
void dfloat ## big ## _sub( dfloat ## big ## _t *dst, dfloat ## big ## _t *src ){\
	dfloat ## big ## _t *tmp;\
	tmp = (dfloat ## big ## _t *) malloc( sizeof( dfloat ## big ## _t ) );\
	dfloat ## big ## _cpy( tmp, src );\
	tmp->mantissa *= -1;\
	dfloat ## big ## _add( dst, tmp );\
	free( tmp );\
}

dfloatN_sub( 8, 16 )
dfloatN_sub( 16, 32 )
dfloatN_sub( 32, 64 )
dfloatN_sub( 64, 128 )

// TODO: TEST
// Multiplies the two operands and stores the result in the first operand
#define dfloatN_mul( small, big )\
void dfloat ## big ## _mul( dfloat ## big ## _t *dst, dfloat ## big ## _t *src ){\
	dst->mantissa *= src->mantissa;\
	dst->exponent += src->exponent;\
}

dfloatN_mul( 8, 16 )
dfloatN_mul( 16, 32 )
dfloatN_mul( 32, 64 )
dfloatN_mul( 64, 128 )

// TODO: TEST
// Divides the first operand by the second operand
#define dfloatN_div( small, big )\
void dfloat ## big ## _div( dfloat ## big ## _t *dst, dfloat ## big ## _t *src, int precision ){\
	/* First section shifts the destination mantissa */\
	/* so it doesn't become zero when divided.       */\
	long log_max;\
	int ## small ## _t dst_magnitude;\
	int ## small ## _t shift_factor;\
	log_max = ceil( log10( ((int ## small ## _t) 1) << (small-3) ) );\
	dst_magnitude = ceil( log10( dst->mantissa * pow( 10, dst->exponent ) ) );\
	shift_factor = pow( 10, log_max - dst_magnitude );\
	dst->mantissa *= shift_factor;\
\
	dst->mantissa /= src->mantissa;\
	dst->exponent -= (src->exponent+precision);\
	dst->mantissa /= (shift_factor/pow( 10, precision ));\
}

dfloatN_div( 8, 16 )
dfloatN_div( 16, 32 )
dfloatN_div( 32, 64 )
dfloatN_div( 64, 128 )

// TESTED AND WORKING
// Reads a dfloat value from a string
#define dfloatN_atof( small, big )\
dfloat ## big ## _t *dfloat ## big ## _atof( char *src ){\
	int i, len;\
	int point = 0;\
	char *cpy;\
	dfloat ## big ## _t *dst;\
	len = strlen( src );\
	cpy = (char *) malloc( len+1 );\
	strncpy( cpy, src, len+1 );\
	dst = (dfloat ## big ## _t *) malloc( sizeof( dfloat ## big ## _t ) );\
	dst->exponent = 0;\
\
	/* Search for decimal point: */\
	for( i = 0; i < len; i++ ){\
		if( cpy[i] == '.' ) point = i;\
	}\
\
	/* Determine exponent: */\
	i = len;\
	while( cpy[--i] == '0' );\
	if( !point ){\
		dst->exponent = len - i - 1;\
	}\
	else if( i == point ){\
		while( cpy[--i] == '0' )\
			dst->exponent++;\
	}\
	else{\
		dst->exponent = point - i;\
	}\
\
	/* Determine mantissa: */\
	if( point ){\
		for( i = point; i < len; i++ )\
			cpy[i] = cpy[i+1];\
		len--;\
	}\
	i = len;\
	while( cpy[--i] == '0' )\
		cpy[i] = '\0';\
	dst->mantissa = (int ## small ## _t) atoi( cpy );\
\
	free( cpy );\
	return dst;\
}

dfloatN_atof( 8, 16 )
dfloatN_atof( 16, 32 )
dfloatN_atof( 32, 64 )
dfloatN_atof( 64, 128 )

// TODO: TEST
// Writes a dfloat value to a string and returns that string
#define dfloatN_ftoa( small, big )\
char *dfloat ## big ## _ftoa( dfloat ## big ## _t *src ){\
	int ## small ## _t size1, size2;\
	int ## small ## _t whole_part, frac_part;\
	int ## small ## _t shift_factor;\
	int ## small ## _t whole_magnitude, frac_magnitude;\
	int i;\
	char *buf;\
	size1 = ceil( log10( abs( src->mantissa ) ) );\
	if( src->exponent == 0 ){\
		/* This code simply prints the mantissa. */\
		size2 = size1 + 2;\
		buf = (char *) malloc( size2 );\
		sprintf( buf, "%d\0", src->mantissa );\
	}\
	else if( src->exponent > 0 ){\
		/* This code prints the mantissa and then a number of zeros */\
		/* equal to the exponent.                                   */\
		size2 = size1 + src->exponent;\
		buf = (char *) malloc( size2 + 2 );\
		sprintf( buf, "%d", src->mantissa );\
		if( src->mantissa < 0 ){\
		/* Accounts for a minus sign at the beginning */\
			size1++;\
			size2++;\
		}\
		for( i = size1; i < size2; i++ ){\
			buf[i] = '0';\
		}\
		buf[size2] = '\0';\
	}\
	else if( src->exponent < 0 ){\
		/* This code shifts the fractional part out of the mantissa */\
		/* to get the whole part, then shifts in zeros and subtracts*/\
		/* from the original mantissa to get the fractional part.   */\
		shift_factor = pow( 10, src->exponent );\
		whole_part = abs( src->mantissa ) * shift_factor;\
		frac_part = abs( src->mantissa ) - whole_part / shift_factor;\
\
		whole_magnitude = ceil( log10( whole_part ) );\
		frac_magnitude = ceil( log10( frac_part ) );\
\
		/* This code accounts for exact powers of 10. */\
		if( whole_magnitude = log10( whole_part ) )\
			whole_magnitude++;\
		if( frac_magnitude = log10( frac_part ) )\
			frac_magnitude++;\
\
		size2 = whole_magnitude + frac_magnitude + 3;\
		buf = (char *) malloc( size2 );\
		sprintf( buf, "%s%d.%d\0", (src->mantissa < 0)?"-":"", whole_part, frac_part );\
	}\
	return buf;\
}

dfloatN_ftoa( 8, 16 )
dfloatN_ftoa( 16, 32 )
dfloatN_ftoa( 32, 64 )
dfloatN_ftoa( 64, 128 )
