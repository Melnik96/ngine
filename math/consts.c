/*
	consts.c -- Constants used in SIMDx86
	Written by Patrick Baggett, 2005 (baggett.patrick@gmail.com)
	Under LGPL License
	Part of SIMDx86 Project

*/

#include <SIMDx86/align.h>

#if defined(WIN32) || defined(__WIN32) || defined(__WIN32__)

double ALIGNMENT_PREFIX SIMDx86_double_one[4] = { 1.0, 1.0, 1.0, 1.0 };
float ALIGNMENT_PREFIX SIMDx86_float_one[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
float ALIGNMENT_PREFIX SIMDx86_float_one_w[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
float ALIGNMENT_PREFIX SIMDx86_float_one_y[4] = { 0.0f, 1.0f, 0.0f, 0.0f };

unsigned int ALIGNMENT_PREFIX SIMDx86_float_POSNEG[2] = { 0x00000000, 0x80000000 };	/* XOR Changes the signs to + - */
unsigned int ALIGNMENT_PREFIX SIMDx86_float_NEGPOS[2] = { 0x80000000, 0x00000000 };	/* XOR Changes the signs to - + */
unsigned int ALIGNMENT_PREFIX SIMDx86_float_NEGNEG[2] = { 0x80000000, 0x80000000 };	/* XOR Changes the signs to - - */
unsigned int ALIGNMENT_PREFIX SIMDx86_float_NEGPOSPOSPOS[4] = { 0x80000000, 0x00000000, 0x00000000, 0x00000000 };
unsigned int ALIGNMENT_PREFIX SIMDx86_float_POSPOSPOSNEG[4] = { 0x00000000, 0x00000000, 0x00000000, 0x80000000 };
unsigned int ALIGNMENT_PREFIX SIMDx86_float_SSE_NO_W_MASK[4] = { 0xFFFFFFFF,  0xFFFFFFFF, 0xFFFFFFFF, 0x00000000 };
unsigned int ALIGNMENT_PREFIX SIMDx86_float_SSE_NO_XYZ_MASK[4] = { 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF };
unsigned int ALIGNMENT_PREFIX SIMDx86_float_3DNOW_NO_W_MASK[2] = { 0xFFFFFFFF, 0x00000000 };
unsigned int ALIGNMENT_PREFIX SIMDx86_float_ABS[4] = { 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF,0x7FFFFFFF };

#else /* ELF format of many UNIX systems does NOT append underbar (stupid windows!) */

double ALIGNMENT_PREFIX _SIMDx86_double_one[4] ALIGNMENT_SUFFIX = { 1.0, 1.0, 1.0, 1.0 };
float ALIGNMENT_PREFIX _SIMDx86_float_one[4] ALIGNMENT_SUFFIX = { 1.0f, 1.0f, 1.0f, 1.0f };
float ALIGNMENT_PREFIX _SIMDx86_float_one_w[4] ALIGNMENT_SUFFIX = { 0.0f, 0.0f, 0.0f, 1.0f };
float ALIGNMENT_PREFIX _SIMDx86_float_one_y[4] ALIGNMENT_SUFFIX = { 0.0f, 1.0f, 0.0f, 0.0f };

unsigned int ALIGNMENT_PREFIX _SIMDx86_float_POSNEG[2] ALIGNMENT_SUFFIX = { 0x00000000, 0x80000000 };	/* XOR Changes the signs to + - */
unsigned int ALIGNMENT_PREFIX _SIMDx86_float_NEGPOS[2] ALIGNMENT_SUFFIX = { 0x80000000, 0x00000000 };	/* XOR Changes the signs to - + */
unsigned int ALIGNMENT_PREFIX _SIMDx86_float_NEGNEG[2] ALIGNMENT_SUFFIX = { 0x80000000, 0x80000000 };	/* XOR Changes the signs to - - */
unsigned int ALIGNMENT_PREFIX _SIMDx86_float_NEGPOSPOSPOS[4] ALIGNMENT_SUFFIX = { 0x80000000, 0x00000000, 0x00000000, 0x00000000 };
unsigned int ALIGNMENT_PREFIX _SIMDx86_float_POSPOSPOSNEG[4] ALIGNMENT_SUFFIX = { 0x00000000, 0x00000000, 0x00000000, 0x80000000 };
unsigned int ALIGNMENT_PREFIX _SIMDx86_float_SSE_NO_W_MASK[4] ALIGNMENT_SUFFIX = { 0xFFFFFFFF,  0xFFFFFFFF, 0xFFFFFFFF, 0x00000000 };
unsigned int ALIGNMENT_PREFIX _SIMDx86_float_SSE_NO_XYZ_MASK[4] ALIGNMENT_SUFFIX = { 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF };
unsigned int ALIGNMENT_PREFIX _SIMDx86_float_3DNOW_NO_W_MASK[2] ALIGNMENT_SUFFIX = { 0xFFFFFFFF, 0x00000000 };
unsigned int ALIGNMENT_PREFIX _SIMDx86_float_ABS[4] ALIGNMENT_SUFFIX = { 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF,0x7FFFFFFF };


#endif
