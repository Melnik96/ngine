/*
	quaternion.h -- SIMDx86 Quaternion Library
	Written by Patrick Baggett, 2005 (baggett.patrick@gmail.com)
	Under LGPL License
	Part of SIMDx86 Project
*/

#ifndef _SIMDX86_QUATERNION_H
#define _SIMDX86_QUATERNION_H

#include <SIMDx86/align.h>
#include <SIMDx86/matrix.h>


#ifdef __cplusplus
extern "C" {
#endif


typedef struct ALIGNMENT_PREFIX SIMDx86Quaternion
{
	float x, y, z, w;
} SIMDx86Quaternion ALIGNMENT_SUFFIX;

#define TOSIMDX86QUATERNION( ptr ) 	((SIMDx86Quaternion*)(ptr))


void SIMDx86Quaternion_Normalize(SIMDx86Quaternion* pQuat);
void SIMDx86Quaternion_NormalizeOf(SIMDx86Quaternion* pOut, const SIMDx86Quaternion* pQuat);
float  SIMDx86Quaternion_Length(const SIMDx86Quaternion* pQuat);
float  SIMDx86Quaternion_LengthSq(const SIMDx86Quaternion* pQuat);
void SIMDx86Quaternion_Multiply(SIMDx86Quaternion* pLeft, const SIMDx86Quaternion* pRight);
void SIMDx86Quaternion_MultiplyOf(SIMDx86Quaternion* pOut, const SIMDx86Quaternion* pLeft, const SIMDx86Quaternion* pRight);
void SIMDx86Quaternion_Conjugate(SIMDx86Quaternion* pQuat);
void SIMDx86Quaternion_ConjugateOf(SIMDx86Quaternion* pOut, const SIMDx86Quaternion* pSrc);
void SIMDx86Quaternion_ToMatrix(SIMDx86Matrix* pMat, const SIMDx86Quaternion* pQuat);
void SIMDx86Quaternion_Rotate(SIMDx86Quaternion* pOut, float rads, float x, float y, float z);
void SIMDx86Quaternion_Slerp(SIMDx86Quaternion* pOut, const SIMDx86Quaternion* pSrc1, const SIMDx86Quaternion* pSrc2, float scalar);

#ifdef __cplusplus
}
#endif


#endif


