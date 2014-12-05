/*
	consts.h -- Constants used in SIMDx86
	Written by Patrick Baggett, 2005 (baggett.patrick@gmail.com)
	Under LGPL License
	Part of SIMDx86 Project
*/

#ifndef _SIMDX86_CONSTS_H
#define _SIMDX86_CONSTS_H

#if defined(WIN32)
extern double SIMDx86_double_one[4];	/* 1.0  | 1.0  | 1.0  | 1.0  */
extern float SIMDx86_float_one[4];		/* 1.0f | 1.0f | 1.0f | 1.0f */
extern float SIMDx86_float_one_w[4];	/* 0.0f | 0.0f | 0.0f | 1.0f */
extern float SIMDx86_float_one_y[3];    /* 0.0f | 1.0f | 0.0f | 0.0f */

extern unsigned int SIMDx86_float_POSNEG[2];	/* XOR Changes the signs to + - */
extern unsigned int SIMDx86_float_NEGPOS[2];	/* XOR Changes the signs to - + */
extern unsigned int SIMDx86_float_NEGNEG[2];	/* XOR Changes the signs to - - */
extern unsigned int SIMDx86_float_SSE_NO_W_MASK[4]; /* AND removes w component of a vector */
extern unsigned int SIMDx86_float_3DNOW_NO_W_MASK[2]; /* AND removes w component of a vector */
extern unsigned int _SIMDx86_float_ABS[4];

#else
extern double _SIMDx86_double_one[4];	/* 1.0  | 1.0  | 1.0  | 1.0  */
extern float _SIMDx86_float_one[4];		/* 1.0f | 1.0f | 1.0f | 1.0f */
extern float _SIMDx86_float_one_w[4];	/* 0.0f | 0.0f | 0.0f | 1.0f */
extern float _SIMDx86_float_one_y[2];   /* 0.0f | 1.0f | 0.0f | 0.0f  */

extern unsigned int _SIMDx86_float_POSNEG[2];	/* XOR Changes the signs to + - */
extern unsigned int _SIMDx86_float_NEGPOS[2];	/* XOR Changes the signs to - + */
extern unsigned int _SIMDx86_float_NEGNEG[2];	/* XOR Changes the signs to - - */
extern unsigned int _SIMDx86_float_SSE_NO_W_MASK[4]; /* AND removes w component of a vector */
extern unsigned int _SIMDx86_float_3DNOW_NO_W_MASK[2]; /* AND removes w component of a vector */
extern unsigned int _SIMDx86_float_ABS[4];

#endif

#endif
