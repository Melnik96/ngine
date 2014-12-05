/*
	polygon.h -- SIMDx86 Polygon Library
	Written by Patrick Baggett, 2005 (baggett.patrick@gmail.com)
	Under LGPL License
	Part of SIMDx86 Project
*/

#ifndef _SIMDX86_POLYGON_H
#define _SIMDX86_POLYGON_H

#include <SIMDx86/align.h>
#include <SIMDx86/vector.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ALIGNMENT_PREFIX SIMDx86Polygon{
	SIMDx86Vector a, b, c;
} SIMDx86Polygon ALIGNMENT_SUFFIX;

void SIMDx86Polygon_PlaneNormal(SIMDx86Vector* pNormal, const SIMDx86Polygon* pPoly);

#ifdef __cplusplus
}
#endif


#endif
