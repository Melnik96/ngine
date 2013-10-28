/*
	vector.c -- SIMDx86 3D Vector Library (Standard C)
	Written by Patrick Baggett, 2005 (baggett.patrick@gmail.com)
	Under LGPL License
	Part of SIMDx86 Project
*/

#include <SIMDx86/vector.h>
#include <SIMDx86/consts.h>
#include <math.h> /* sqrtf() */

void SIMDx86Vector_Sum(SIMDx86Vector* pOut, const SIMDx86Vector* pIn)
{
	pOut->x += pIn->x;
	pOut->y += pIn->y;
	pOut->z += pIn->z;
}

void SIMDx86Vector_SumOf(SIMDx86Vector* pOut, const SIMDx86Vector* pIn1, const SIMDx86Vector* pIn2)
{
	pOut->x = pIn1->x + pIn2->x;
	pOut->y = pIn1->y + pIn2->y;
	pOut->z = pIn1->z + pIn2->z;
}


void SIMDx86Vector_Diff(SIMDx86Vector* pLeft, SIMDx86Vector* pRight)
{
	pLeft->x -= pRight->x;
	pLeft->y -= pRight->y;
	pLeft->z -= pRight->z;
}

void SIMDx86Vector_DiffOf(SIMDx86Vector* pOut, const SIMDx86Vector* pLeft, const SIMDx86Vector* pRight)
{
	pOut->x = pLeft->x - pRight->x;
	pOut->y = pLeft->y - pRight->y;
	pOut->z = pLeft->z - pRight->z;
}

void SIMDx86Vector_Scale(SIMDx86Vector* pOut, float scalar)
{
	pOut->x *= scalar;
	pOut->y *= scalar;
	pOut->z *= scalar;
}

void SIMDx86Vector_ScaleOf(SIMDx86Vector* pOut, const SIMDx86Vector* pIn, float scalar)
{
	pOut->x = pIn->x * scalar;
	pOut->y = pIn->y * scalar;
	pOut->z = pIn->z * scalar;
}

float SIMDx86Vector_Dot(const SIMDx86Vector* pSrc1, const SIMDx86Vector* pSrc2)
{
	return (pSrc1->x * pSrc2->x) + (pSrc1->y * pSrc2->y) + (pSrc1->z * pSrc2->z);
}

float SIMDx86Vector_Dot4(const float* pSrc4D1, const float* pSrc4D2)
{
	return (pSrc4D1[0]*pSrc4D2[0]) + (pSrc4D1[1]*pSrc4D2[1]) + (pSrc4D1[2]*pSrc4D2[2]) + (pSrc4D1[3]*pSrc4D2[3]);
}

float SIMDx86Vector_LengthSq(const SIMDx86Vector* pVec)
{
	return (pVec->x*pVec->x) + (pVec->y*pVec->y) + (pVec->z*pVec->z);
}

float SIMDx86Vector_Length(const SIMDx86Vector* pVec)
{
	return sqrtf((pVec->x*pVec->x) + (pVec->y*pVec->y) + (pVec->z*pVec->z));
}

void SIMDx86Vector_Cross(SIMDx86Vector* pLeft, const SIMDx86Vector* pRight)
{
	SIMDx86Vector tmp;

	tmp.x = pLeft->x;
	tmp.y = pLeft->y;
	tmp.z = pLeft->z;

	pLeft->x = (tmp.y * pRight->z) - (tmp.z * pRight->y);
	pLeft->y = (tmp.z * pRight->x) - (tmp.x * pRight->z);
	pLeft->z = (tmp.x * pRight->y) - (tmp.y * pRight->x);
}

void SIMDx86Vector_CrossOf(SIMDx86Vector* pOut, const SIMDx86Vector* pLeft, const SIMDx86Vector* pRight)
{
	pOut->x = (pLeft->y * pRight->z) - (pLeft->z * pRight->y);
	pOut->y = (pLeft->z * pRight->x) - (pLeft->x * pRight->z);
	pOut->z = (pLeft->x * pRight->y) - (pLeft->y * pRight->x);
}
void SIMDx86Vector_Normalize(SIMDx86Vector* pVec)
{
	float inv_mag = 1.0f / sqrtf((pVec->x*pVec->x) + (pVec->y*pVec->y) + (pVec->z*pVec->z));

	pVec->x *= inv_mag;
	pVec->y *= inv_mag;
	pVec->z *= inv_mag;
}
void SIMDx86Vector_NormalizeOf(SIMDx86Vector* pOut, const SIMDx86Vector* pVec)
{
	float inv_mag = 1.0f / (sqrtf((pVec->x*pVec->x) + (pVec->y*pVec->y) + (pVec->z*pVec->z)));

	pOut->x = pVec->x * inv_mag;
	pOut->y = pVec->y * inv_mag;
	pOut->z = pVec->z * inv_mag;
}

float SIMDx86Vector_Distance(const SIMDx86Vector* pVec1, const SIMDx86Vector* pVec2)
{
	SIMDx86Vector diff;

	SIMDx86Vector_DiffOf(&diff, pVec1, pVec2);
	return SIMDx86Vector_Length(&diff);
}

