/*
	vector.h -- SIMDx86 3D Vector Library
	Written by Patrick Baggett, 2005 (baggett.patrick@gmail.com)
	Under LGPL License
	Part of SIMDx86 Project
*/

#ifndef _SIMDX86_VECTOR_H
#define _SIMDX86_VECTOR_H

#include <SIMDx86/align.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct ALIGNMENT_PREFIX SIMDx86Vector
{
	float x, y, z;
	float __SIMD_pad__; /* Padding to 16th byte for SIMD operations (3DNow!/SSE) */
} SIMDx86Vector ALIGNMENT_SUFFIX;

void SIMDx86Vector_Sum(SIMDx86Vector* pOut, const SIMDx86Vector* pIn);
void SIMDx86Vector_SumOf(SIMDx86Vector* pOut, const SIMDx86Vector* pIn1, const SIMDx86Vector* pIn2);
void SIMDx86Vector_Diff(SIMDx86Vector* pLeft, SIMDx86Vector* pRight);
void SIMDx86Vector_DiffOf(SIMDx86Vector* pOut, const SIMDx86Vector* pLeft, const SIMDx86Vector* pRight);
void SIMDx86Vector_Scale(SIMDx86Vector* pOut, float scalar);
void SIMDx86Vector_ScaleOf(SIMDx86Vector* pOut, const SIMDx86Vector* pIn, float scalar);
float SIMDx86Vector_Dot(const SIMDx86Vector* pSrc1, const SIMDx86Vector* pSrc2);
float SIMDx86Vector_Dot4(const float* pSrc4D1, const float* pSrc4D2);
float SIMDx86Vector_LengthSq(const SIMDx86Vector* pVec);
float SIMDx86Vector_Length(const SIMDx86Vector* pVec);
void SIMDx86Vector_Cross(SIMDx86Vector* pLeft, const SIMDx86Vector* pRight);
void SIMDx86Vector_CrossOf(SIMDx86Vector* pOut, const SIMDx86Vector* pLeft, const SIMDx86Vector* pRight);
void SIMDx86Vector_Normalize(SIMDx86Vector* pVec);
void SIMDx86Vector_NormalizeOf(SIMDx86Vector* pOut, const SIMDx86Vector* pVec);
float SIMDx86Vector_Distance(const SIMDx86Vector* pVec1, const SIMDx86Vector* pVec2);

#ifdef __cplusplus
}
#endif


#endif
