/****************************************************
 * libdfloat, version 0.1 Alpha                     *
 * Description: Implements floating point numbers   *
 *              with exact decimal representations  *
 * Current file: Header file for entire project     *
 * Author: Michael Warren, a.k.a. Psycho Cod3r      *
 * Date: October 2020                               *
 * License: Micheal Warren FSL                      *
 ****************************************************/

#ifndef _DFLOAT_H_
#define _DFLOAT_H_

#include <stdint.h>

typedef struct {
	int8_t mantissa;
	int8_t exponent;
} dfloat16_t;

typedef struct {
	int16_t mantissa;
	int16_t exponent;
} dfloat32_t;

typedef struct {
	int32_t mantissa;
	int32_t exponent;
} dfloat64_t;

typedef struct {
	int64_t mantissa;
	int64_t exponent;
} dfloat128_t;

__BEGIN_DECLS
void dfloat16_add( dfloat16_t *, dfloat16_t * );
void dfloat16_sub( dfloat16_t *, dfloat16_t * );
void dfloat16_mul( dfloat16_t *, dfloat16_t * );
void dfloat16_div( dfloat16_t *, dfloat16_t *, int );
void dfloat16_cpy( dfloat16_t *, dfloat16_t * );
dfloat32_t *dfloat16_cast32( dfloat16_t * );
dfloat64_t *dfloat16_cast64( dfloat16_t * );
dfloat128_t *dfloat16_cast128( dfloat16_t * );
dfloat16_t *dfloat16_atof( char * );
char *dfloat16_ftoa( dfloat16_t * );
void dfloat32_add( dfloat32_t *, dfloat32_t * );
void dfloat32_sub( dfloat32_t *, dfloat32_t * );
void dfloat32_mul( dfloat32_t *, dfloat32_t * );
void dfloat32_div( dfloat32_t *, dfloat32_t *, int );
void dfloat32_cpy( dfloat32_t *, dfloat32_t * );
dfloat16_t *dfloat32_cast16( dfloat32_t * );
dfloat64_t *dfloat32_cast64( dfloat32_t * );
dfloat128_t *dfloat32_cast128( dfloat32_t * );
dfloat32_t *dfloat32_atof( char * );
char *dfloat32_ftoa( dfloat32_t * );
void dfloat64_add( dfloat64_t *, dfloat64_t * );
void dfloat64_sub( dfloat64_t *, dfloat64_t * );
void dfloat64_mul( dfloat64_t *, dfloat64_t * );
void dfloat64_div( dfloat64_t *, dfloat64_t *, int );
void dfloat64_cpy( dfloat64_t *, dfloat64_t * );
dfloat16_t *dfloat64_cast16( dfloat64_t * );
dfloat32_t *dfloat64_cast32( dfloat64_t * );
dfloat128_t *dfloat64_cast128( dfloat64_t * );
dfloat64_t *dfloat64_atof( char * );
char *dfloat64_ftoa( dfloat64_t * );
void dfloat128_add( dfloat128_t *, dfloat128_t * );
void dfloat128_sub( dfloat128_t *, dfloat128_t * );
void dfloat128_mul( dfloat128_t *, dfloat128_t * );
void dfloat128_div( dfloat128_t *, dfloat128_t *, int );
void dfloat128_cpy( dfloat128_t *, dfloat128_t * );
dfloat16_t *dfloat128_cast16( dfloat128_t * );
dfloat32_t *dfloat128_cast32( dfloat128_t * );
dfloat64_t *dfloat128_cast64( dfloat128_t * );
dfloat128_t *dfloat128_atof( char * );
char *dfloat128_ftoa( dfloat128_t * );
__END_DECLS

#endif
