/*
	matrix.h -- SIMDx86 Matrix Library
	Written by Patrick Baggett, 2005 (baggett.patrick@gmail.com)
	Under LGPL License
	Part of SIMDx86 Project
*/

#ifndef _SIMDX86_MATRIX_H
#define _SIMDX86_MATRIX_H

#include <SIMDx86/align.h>
#include <SIMDx86/vector.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ALIGNMENT_PREFIX SIMDx86Matrix
{
	float m[16];
} SIMDx86Matrix ALIGNMENT_SUFFIX;

#define TOSIMDX86MATRIX( ptr ) 	((SIMDx86Matrix*)(ptr))

void SIMDx86Matrix_Sum(SIMDx86Matrix* pMat, const SIMDx86Matrix* pIn);
void SIMDx86Matrix_SumOf(SIMDx86Matrix* pMat, const SIMDx86Matrix* pIn1, const SIMDx86Matrix* pIn2);
void SIMDx86Matrix_Diff(SIMDx86Matrix* pMat, const SIMDx86Matrix* pIn);
void SIMDx86Matrix_DiffOf(SIMDx86Matrix* pMat, const SIMDx86Matrix* pLeft, const SIMDx86Matrix* pRight);
void SIMDx86Matrix_Scale(SIMDx86Matrix* pMat, float scalar);
void SIMDx86Matrix_ScaleOf(SIMDx86Matrix* pOut, const SIMDx86Matrix* pIn, float scalar);
void SIMDx86Matrix_Multiply(SIMDx86Matrix* pLeft, const SIMDx86Matrix* pRight);
void SIMDx86Matrix_MultiplyOf(SIMDx86Matrix* pOut, const SIMDx86Matrix* pLeft, const SIMDx86Matrix* pRight);
void SIMDx86Matrix_Transpose(SIMDx86Matrix* pIn);
void SIMDx86Matrix_TransposeOf(SIMDx86Matrix* pOut, const SIMDx86Matrix* pIn);
void SIMDx86Matrix_VectorMultiply(SIMDx86Vector* pOut, const SIMDx86Matrix* pIn);
void SIMDx86Matrix_VectorMultiplyOf(SIMDx86Vector* pOut, const SIMDx86Vector* pIn, const SIMDx86Matrix* pMat);
void SIMDx86Matrix_Vector4Multiply(float* pOut4D, const SIMDx86Matrix* pIn);
void SIMDx86Matrix_Vector4MultiplyOf(float* pOut4D, const float* pIn4D, const SIMDx86Matrix* pMat);
void SIMDx86Matrix_ToIdentity(SIMDx86Matrix* pMat);
void SIMDx86Matrix_ToScale(SIMDx86Matrix* pMat, float x, float y, float z);
void SIMDx86Matrix_ToScaleOf(SIMDx86Matrix* pMat, const SIMDx86Vector* pVec);
void SIMDx86Matrix_ToTranslate(SIMDx86Matrix* pMat, float x, float y, float z);
void SIMDx86Matrix_ToTranslateOf(SIMDx86Matrix* pMat, const SIMDx86Vector* pVec);
void SIMDx86Matrix_ToRotate(SIMDx86Matrix* pMat, float yaw, float pitch, float roll);
void SIMDx86Matrix_ToRotateOf(SIMDx86Matrix* pMat, const SIMDx86Vector* pYawPitchRoll);
SIMDx86Matrix* SIMDx86Matrix_Inverse(SIMDx86Matrix* pMat);
SIMDx86Matrix* SIMDx86Matrix_InverseOf(SIMDx86Matrix* pOut, const SIMDx86Matrix* pIn);

void SIMDx86Matrix_AlignedSum(SIMDx86Matrix* pMat, const SIMDx86Matrix* pIn);
void SIMDx86Matrix_AlignedSumOf(SIMDx86Matrix* pMat, const SIMDx86Matrix* pIn1, const SIMDx86Matrix* pIn2);
void SIMDx86Matrix_AlignedDiff(SIMDx86Matrix* pMat, const SIMDx86Matrix* pIn);
void SIMDx86Matrix_AlignedDiffOf(SIMDx86Matrix* pMat, const SIMDx86Matrix* pLeft, const SIMDx86Matrix* pRight);
void SIMDx86Matrix_AlignedScale(SIMDx86Matrix* pMat, float scalar);
void SIMDx86Matrix_AlignedScaleOf(SIMDx86Matrix* pOut, const SIMDx86Matrix* pIn, float scalar);
void SIMDx86Matrix_AlignedMultiply(SIMDx86Matrix* pLeft, const SIMDx86Matrix* pRight);
void SIMDx86Matrix_AlignedMultiplyOf(SIMDx86Matrix* pOut, const SIMDx86Matrix* pLeft, const SIMDx86Matrix* pRight);
void SIMDx86Matrix_AlignedTranspose(SIMDx86Matrix* pIn);
void SIMDx86Matrix_AlignedTransposeOf(SIMDx86Matrix* pOut, const SIMDx86Matrix* pIn);
void SIMDx86Matrix_AlignedVectorMultiply(SIMDx86Vector* pOut, const SIMDx86Matrix* pIn);
void SIMDx86Matrix_AlignedVectorMultiplyOf(SIMDx86Vector* pOut, const SIMDx86Vector* pIn, const SIMDx86Matrix* pMat);
void SIMDx86Matrix_AlignedVector4Multiply(float* pOut4D, const SIMDx86Matrix* pIn);
void SIMDx86Matrix_AlignedVector4MultiplyOf(float* pOut4D, const float* pIn4D, const SIMDx86Matrix* pMat);
void SIMDx86Matrix_AlignedToIdentity(SIMDx86Matrix* pMat);
void SIMDx86Matrix_AlignedToScale(SIMDx86Matrix* pMat, float x, float y, float z);
void SIMDx86Matrix_AlignedToScaleOf(SIMDx86Matrix* pMat, const SIMDx86Vector* pVec);
void SIMDx86Matrix_AlignedToTranslate(SIMDx86Matrix* pMat, float x, float y, float z);
void SIMDx86Matrix_AlignedToTranslateOf(SIMDx86Matrix* pMat, const SIMDx86Vector* pVec);
void SIMDx86Matrix_AlignedToRotate(SIMDx86Matrix* pMat, float yaw, float pitch, float roll);
void SIMDx86Matrix_AlignedToRotateOf(SIMDx86Matrix* pMat, const SIMDx86Vector* pYawPitchRoll);
SIMDx86Matrix* SIMDx86Matrix_AlignedInverse(SIMDx86Matrix* pMat);
SIMDx86Matrix* SIMDx86Matrix_AlignedInverseOf(SIMDx86Matrix* pOut, const SIMDx86Matrix* pIn);


#ifdef __cplusplus
}
#endif


#endif
