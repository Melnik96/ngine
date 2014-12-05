/*
	math.c -- Generic C math functions
	Written by Patrick Baggett, 2005 (baggett.patrick@gmail.com)
	Under LGPL License
	Part of SIMDx86 Project
*/
#define SIMDX86_LEAN
#include <math.h> /* Only needed in C version of code */
#include <SIMDx86/SIMDx86.h>

float SIMDx86_sqrtf_C(float value)
{
	return sqrtf(value);
}

float SIMDx86_rsqrtf_C(float value)
{
		return 1.0f / sqrtf(value);
}


double SIMDx86_sqrt_C(double value)
{
	return sqrt(value);
}

double SIMDx86_rsqrt_C(double value)
{
	return 1.0 / sqrt(value);
}


#define MATH_OVERLAY_SIZE OVERLAY_SIZE_MEDIUM /* Hopefully, C version uses less instructions than this */

unsigned int size_SIMDx86_sqrtf_C = MATH_OVERLAY_SIZE;
unsigned int size_SIMDx86_rsqrtf_C = MATH_OVERLAY_SIZE;
unsigned int size_SIMDx86_sqrt_C = MATH_OVERLAY_SIZE; 
unsigned int size_SIMDx86_rsqrt_C = MATH_OVERLAY_SIZE;

/* These buffers are made executable at runtime. */
char SIMDx86_sqrtf[OVERLAY_SIZE_MEDIUM];
char SIMDx86_rsqrtf[OVERLAY_SIZE_MEDIUM];
char SIMDx86_sqrt[OVERLAY_SIZE_MEDIUM];
char SIMDx86_rsqrt[OVERLAY_SIZE_MEDIUM];


