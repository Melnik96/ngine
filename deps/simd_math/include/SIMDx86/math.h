/*
	math.h -- SIMD accelerated math functions
	Written by Patrick Baggett, 2005 (baggett.patrick@gmail.com)
	Under LGPL License
	Part of SIMDx86 Project

*/
#ifndef _SIMDX86_MATH_H
#define _SIMDX86_MATH_H

#ifdef __cplusplus
extern "C" {
#endif


float SIMDx86_sqrtf(float value);
float SIMDx86_rsqrtf(float value);
double SIMDx86_sqrt(double value);
double SIMDx86_rsqrt(double value);

#ifdef __cplusplus
}
#endif


#endif

