/****************************************************
 * libdfloat, version 0.2 Alpha                     *
 * Description: Implements floating point numbers   *
 *              with exact decimal representations  *
 * Author: Michael Warren, a.k.a. Psycho Cod3r      *
 * Date: October 2020                               *
 * License: Micheal Warren FSL Version 1.1          *
 * Current module: Function versions that free the  *
 *                 source operand, making complex   *
 *                 expressions easier               *
 ****************************************************/

#include <stdlib.h>
#include "dfloat.h"

// Note: Because these functions free their operands,
// you can't use the same variable multiple times in
// an expression that uses them. They should only be
// used for expressions that involve directly placing
// one function inside another function's operand list,
// which would make explicitly freeing the arguments
// impossible, thus necessitating a collection of
// functions that do that for you.

#define dfloatM_castNf( M, N )\
dfloat ## N ## _t *dfloat ## M ## _cast ## N ## f( dfloat ## M ## _t *src ){\
	dfloat ## N ## _t *dst;\
	dst = dfloat ## M ## _cast ## N ( src );\
	free( src );\
	return dst;\
}

dfloatM_castNf( 16, 32 )
dfloatM_castNf( 16, 64 )
dfloatM_castNf( 16, 128 )

dfloatM_castNf( 32, 16 )
dfloatM_castNf( 32, 64 )
dfloatM_castNf( 32, 128 )

dfloatM_castNf( 64, 16 )
dfloatM_castNf( 64, 32 )
dfloatM_castNf( 64, 128 )

dfloatM_castNf( 128, 16 )
dfloatM_castNf( 128, 32 )
dfloatM_castNf( 128, 64 )

#define dfloatN_addf( N )\
dfloat ## N ## _t *dfloat ## N ## _addf( dfloat ## N ## _t *arg1, dfloat ## N ## _t *arg2 ){\
	dfloat ## N ## _add( arg1, arg2 );\
	free( arg2 );\
	return arg1;\
}

dfloatN_addf( 16 )
dfloatN_addf( 32 )
dfloatN_addf( 64 )
dfloatN_addf( 128 )

#define dfloatN_subf( N )\
dfloat ## N ## _t *dfloat ## N ## _subf( dfloat ## N ## _t *arg1, dfloat ## N ## _t *arg2 ){\
	dfloat ## N ## _sub( arg1, arg2 );\
	free( arg2 );\
	return arg1;\
}

dfloatN_subf( 16 )
dfloatN_subf( 32 )
dfloatN_subf( 64 )
dfloatN_subf( 128 )


#define dfloatN_mulf( N )\
dfloat ## N ## _t *dfloat ## N ## _mulf( dfloat ## N ## _t *arg1, dfloat ## N ## _t *arg2 ){\
	dfloat ## N ## _mul( arg1, arg2 );\
	free( arg2 );\
	return arg1;\
}

dfloatN_mulf( 16 )
dfloatN_mulf( 32 )
dfloatN_mulf( 64 )
dfloatN_mulf( 128 )

#define dfloatN_divf( N )\
dfloat ## N ## _t *dfloat ## N ## _divf( dfloat ## N ## _t *arg1, dfloat ## N ## _t *arg2, int precision ){\
	dfloat ## N ## _div( arg1, arg2, precision );\
	free( arg2 );\
	return arg1;\
}

dfloatN_divf( 16 )
dfloatN_divf( 32 )
dfloatN_divf( 64 )
dfloatN_divf( 128 )

#define dfloatN_cmpf( N )\
int dfloat ## N ## _cmpf( dfloat ## N ## _t *arg1, dfloat ## N ## _t *arg2 ){\
	int result;\
	result = dfloat ## N ## _cmp( arg1, arg2 );\
	free( arg1 );\
	free( arg2 );\
	return result;\
}

dfloatN_cmpf( 16 )
dfloatN_cmpf( 32 )
dfloatN_cmpf( 64 )
dfloatN_cmpf( 128 )

#define dfloatN_ftoaf( N )\
char *dfloat ## N ## _ftoaf( dfloat ## N ## _t *src ){\
	char *dst;\
	dst = dfloat ## N ## _ftoa( src );\
	free( src );\
	return dst;\
}

dfloatN_ftoaf( 16 )
dfloatN_ftoaf( 32 )
dfloatN_ftoaf( 64 )
dfloatN_ftoaf( 128 )
