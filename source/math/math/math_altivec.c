/*
	math.c -- Generic C math functions
	Written by Patrick Baggett, 2005 (baggett.patrick@gmail.com)
	Under LGPL License
	Part of SIMDx86 Project
*/
#include <math.h> /* Only needed in C version of code */

float SIMDx86_sqrtf_AltiVec(float value)
{
		return sqrtf(value);
}

float SIMDx86_rsqrtf_AltiVec(float value)
{
		return 1.0f / sqrtf(value);
}

