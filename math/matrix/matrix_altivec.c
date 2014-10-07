/*
	matrix.c -- SIMDx86 Matrix Library
	Written by Patrick Baggett, 2005 (baggett.patrick@gmail.com)
	AltiVec code by Konstantinos Margaritis <markos@debian.gr)
	Under LGPL License
	Part of SIMDx86 Project
*/

#include <altivec.h>
#include <memory.h>

#include "SIMDx86/matrix.h"
#include "SIMDx86/SIMDx86_altivec.h"

void SIMDx86Matrix_Copy_AltiVec(SIMDx86Matrix* Out, const SIMDx86Matrix* In)
{
	vector float vm1_1, vm1_2, vm1_3, vm1_4;
 
	// Load matrix
        LOAD_MATRIX(In, vm1_1, vm1_2, vm1_3, vm1_4);

	// Store back the result
	STORE_MATRIX(Out, vm1_1, vm1_2, vm1_3, vm1_4);
}


void SIMDx86Matrix_Sum_AltiVec(SIMDx86Matrix* Out, const SIMDx86Matrix* In)
{
	vector float vm1_1, vm1_2, vm1_3, vm1_4,
                     vm2_1, vm2_2, vm2_3, vm2_4,
                     vm3_1, vm3_2, vm3_3, vm3_4;
 
	// Load both SIMDx86 matrices at once.
        LOAD_MATRIX(In, vm2_1, vm2_2, vm2_3, vm2_4);
        LOAD_MATRIX(Out, vm3_1, vm3_2, vm3_3, vm3_4);

	// Do the addition
	vm1_1 = vec_add(vm2_1, vm3_1);
        vm1_2 = vec_add(vm2_2, vm3_2);
        vm1_3 = vec_add(vm2_3, vm3_3);
        vm1_4 = vec_add(vm2_4, vm3_4);

	// Store back the result
	STORE_MATRIX(Out, vm1_1, vm1_2, vm1_3, vm1_4);

}

void SIMDx86Matrix_SumOf_AltiVec(SIMDx86Matrix* Out, const SIMDx86Matrix* In1, const SIMDx86Matrix* In2)
{
	vector float vm1_1, vm1_2, vm1_3, vm1_4,
                     vm2_1, vm2_2, vm2_3, vm2_4,
                     vm3_1, vm3_2, vm3_3, vm3_4;
 
	// Load both SIMDx86 matrices at once.
        LOAD_MATRIX(In1, vm2_1, vm2_2, vm2_3, vm2_4);
        LOAD_MATRIX(In2, vm3_1, vm3_2, vm3_3, vm3_4);

	// Do the addition
	vm1_1 = vec_add(vm2_1, vm3_1);
        vm1_2 = vec_add(vm2_2, vm3_2);
        vm1_3 = vec_add(vm2_3, vm3_3);
        vm1_4 = vec_add(vm2_4, vm3_4);

	// Store back the result
	STORE_MATRIX(Out, vm1_1, vm1_2, vm1_3, vm1_4);
}

void SIMDx86Matrix_Diff_AltiVec(SIMDx86Matrix* Out, const SIMDx86Matrix* In)
{
	// Load both SIMDx86 matrices at once.
}

void SIMDx86Matrix_DiffOf_AltiVec(SIMDx86Matrix* Out, const SIMDx86Matrix* In1, const SIMDx86Matrix* In2)
{
	// Load both SIMDx86 matrices at once.
}

void SIMDx86Matrix_Scale_AltiVec(SIMDx86Matrix* mtx, float f)
{
	float ALIGNMENT_PREFIX fscalar[4] ALIGNMENT_SUFFIX;
	vector float vscalar, v0, 
                     vm1_1, vm1_2, vm1_3, vm1_4, 
                     vm2_1, vm2_2, vm2_3, vm2_4;
 
        // Set up scalar vector
	fscalar[0] = f;
	vscalar = vec_ld(0, fscalar);
	vscalar = vec_splat(vscalar, 0);
	v0 = (vector float)vec_splat_u32(0);
 
	// Load matrix
	LOAD_MATRIX(mtx, vm2_1, vm2_2, vm2_3, vm2_4);
 
        // Do scaling
	vm1_1 = vec_madd(vm2_1, vscalar, v0);
	vm1_2 = vec_madd(vm2_2, vscalar, v0);
	vm1_3 = vec_madd(vm2_3, vscalar, v0);
	vm1_4 = vec_madd(vm2_4, vscalar, v0);
 
        // Store back the result
	STORE_MATRIX(mtx, vm1_1, vm1_2, vm1_3, vm1_4);
}

void SIMDx86Matrix_ScaleOf_AltiVec(SIMDx86Matrix* pOut, const SIMDx86Matrix* pIn, float f)
{
	float ALIGNMENT_PREFIX fscalar[4] ALIGNMENT_SUFFIX;
	vector float vscalar, v0, 
                     vm1_1, vm1_2, vm1_3, vm1_4, 
                     vm2_1, vm2_2, vm2_3, vm2_4;
 
        // Set up scalar vector
	fscalar[0] = f;
	vscalar = vec_ld(0, fscalar);
	vscalar = vec_splat(vscalar, 0);
	v0 = (vector float)vec_splat_u32(0);
 
	// Load matrix
	LOAD_MATRIX(pIn, vm2_1, vm2_2, vm2_3, vm2_4);
 
        // Do scaling
	vm1_1 = vec_madd(vm2_1, vscalar, v0);
	vm1_2 = vec_madd(vm2_2, vscalar, v0);
	vm1_3 = vec_madd(vm2_3, vscalar, v0);
	vm1_4 = vec_madd(vm2_4, vscalar, v0);
 
        // Store back the result
	STORE_MATRIX(pOut, vm1_1, vm1_2, vm1_3, vm1_4);
}

void SIMDx86Matrix_Multiply_AltiVec(SIMDx86Matrix* pLeft, const SIMDx86Matrix* pRight)
{
	vector float zero;
	vector float vA1, vA2, vA3, vA4, vB1, vB2, vB3, vB4;
	vector float vC1, vC2, vC3, vC4;
 
	zero = (vector float)vec_splat_u32(0);
	// Load matrices and multiply the first row while we wait for the next row
	LOAD_MATRIX(pLeft, vA1, vA2, vA3, vA4);
	LOAD_MATRIX(pRight, vB1, vB2, vB3, vB4);
 
	// Calculate the first column of m1
	vC1 = vec_madd( vec_splat( vA1, 0 ), vB1, zero );
	vC2 = vec_madd( vec_splat( vA2, 0 ), vB1, zero );
	vC3 = vec_madd( vec_splat( vA3, 0 ), vB1, zero );
	vC4 = vec_madd( vec_splat( vA4, 0 ), vB1, zero );
 
	// By now we should have loaded both matrices and be done with the first row
	// Multiply vA x vB2, add to previous results, vC
	vC1 = vec_madd( vec_splat( vA1, 1 ), vB2, vC1 );
	vC2 = vec_madd( vec_splat( vA2, 1 ), vB2, vC2 );
	vC3 = vec_madd( vec_splat( vA3, 1 ), vB2, vC3 );
	vC4 = vec_madd( vec_splat( vA4, 1 ), vB2, vC4 );
 
	// Multiply vA x vB3, add to previous results, vC
	vC1 = vec_madd( vec_splat( vA1, 2 ), vB3, vC1 );
	vC2 = vec_madd( vec_splat( vA2, 2 ), vB3, vC2 );
	vC3 = vec_madd( vec_splat( vA3, 2 ), vB3, vC3 );
	vC4 = vec_madd( vec_splat( vA4, 2 ), vB3, vC4 );
 
	// Multiply vA x vB3, add to previous results, vC
	vC1 = vec_madd( vec_splat( vA1, 3 ), vB4, vC1 );
	vC2 = vec_madd( vec_splat( vA2, 3 ), vB4, vC2 );
	vC3 = vec_madd( vec_splat( vA3, 3 ), vB4, vC3 );
	vC4 = vec_madd( vec_splat( vA4, 3 ), vB4, vC4 );
 
	// Store back the result
	STORE_MATRIX(pLeft, vC1, vC2, vC3, vC4);
}

void SIMDx86Matrix_MultiplyOf_AltiVec(SIMDx86Matrix* pOut, const SIMDx86Matrix* pLeft, const SIMDx86Matrix* pRight)
{
	vector float zero;
	vector float vA1, vA2, vA3, vA4, vB1, vB2, vB3, vB4;
	vector float vC1, vC2, vC3, vC4;
 
	zero = (vector float)vec_splat_u32(0);
	// Load matrices and multiply the first row while we wait for the next row
	LOAD_MATRIX(pLeft, vA1, vA2, vA3, vA4);
	LOAD_MATRIX(pRight, vB1, vB2, vB3, vB4);
 
	// Calculate the first column of m1
	vC1 = vec_madd( vec_splat( vA1, 0 ), vB1, zero );
	vC2 = vec_madd( vec_splat( vA2, 0 ), vB1, zero );
	vC3 = vec_madd( vec_splat( vA3, 0 ), vB1, zero );
	vC4 = vec_madd( vec_splat( vA4, 0 ), vB1, zero );
 
	// By now we should have loaded both matrices and be done with the first row
	// Multiply vA x vB2, add to previous results, vC
	vC1 = vec_madd( vec_splat( vA1, 1 ), vB2, vC1 );
	vC2 = vec_madd( vec_splat( vA2, 1 ), vB2, vC2 );
	vC3 = vec_madd( vec_splat( vA3, 1 ), vB2, vC3 );
	vC4 = vec_madd( vec_splat( vA4, 1 ), vB2, vC4 );
 
	// Multiply vA x vB3, add to previous results, vC
	vC1 = vec_madd( vec_splat( vA1, 2 ), vB3, vC1 );
	vC2 = vec_madd( vec_splat( vA2, 2 ), vB3, vC2 );
	vC3 = vec_madd( vec_splat( vA3, 2 ), vB3, vC3 );
	vC4 = vec_madd( vec_splat( vA4, 2 ), vB3, vC4 );
 
	// Multiply vA x vB3, add to previous results, vC
	vC1 = vec_madd( vec_splat( vA1, 3 ), vB4, vC1 );
	vC2 = vec_madd( vec_splat( vA2, 3 ), vB4, vC2 );
	vC3 = vec_madd( vec_splat( vA3, 3 ), vB4, vC3 );
	vC4 = vec_madd( vec_splat( vA4, 3 ), vB4, vC4 );
 
	// Store back the result
	STORE_MATRIX(pOut, vC1, vC2, vC3, vC4);
}

void SIMDx86Matrix_Transpose_AltiVec(SIMDx86Matrix* pIn)
{
	vector float vm_1, vm_2, vm_3, vm_4,
	             vr_1, vr_2, vr_3, vr_4;

	// Load matrix
	LOAD_MATRIX(pIn, vm_1, vm_2, vm_3, vm_4);
 
	// Do the transpose, first set of moves
	vr_1 = vec_mergeh(vm_1, vm_3);
	vr_2 = vec_mergel(vm_1, vm_3);
	vr_3 = vec_mergeh(vm_2, vm_4);
	vr_4 = vec_mergel(vm_2, vm_4);
	// Get the resulting vectors
	vm_1 = vec_mergeh(vr_1, vr_3);
	vm_2 = vec_mergel(vr_1, vr_3);
	vm_3 = vec_mergeh(vr_2, vr_4);
	vm_4 = vec_mergel(vr_2, vr_4);
 
	// Store back the result
	STORE_MATRIX(pIn, vm_1, vm_2, vm_3, vm_4);
}

void SIMDx86Matrix_TransposeOf_AltiVec(SIMDx86Matrix* pOut, const SIMDx86Matrix* pIn)
{
	vector float vm_1, vm_2, vm_3, vm_4,
	             vr_1, vr_2, vr_3, vr_4;

	// Load matrix
	LOAD_MATRIX(pIn, vm_1, vm_2, vm_3, vm_4);
 
	// Do the transpose, first set of moves
	vr_1 = vec_mergeh(vm_1, vm_3);
	vr_2 = vec_mergel(vm_1, vm_3);
	vr_3 = vec_mergeh(vm_2, vm_4);
	vr_4 = vec_mergel(vm_2, vm_4);
	// Get the resulting vectors
	vm_1 = vec_mergeh(vr_1, vr_3);
	vm_2 = vec_mergel(vr_1, vr_3);
	vm_3 = vec_mergeh(vr_2, vr_4);
	vm_4 = vec_mergel(vr_2, vr_4);
 
	// Store back the result
	STORE_MATRIX(pOut, vm_1, vm_2, vm_3, vm_4);

}

void SIMDx86Matrix_VectorMultiply_AltiVec(SIMDx86Vector* pVec, const SIMDx86Matrix* pMat)
{
	vector float vm_1, vm_2, vm_3, vm_4,
	             vec, vec_1, vec_2, vec_3, 
	             vr, vr_1, vr_2, vr_3, v0;

	// Load matrix and vector
	LOAD_MATRIX(pMat, vm_1, vm_2, vm_3, vm_4);
	LOAD_VECTOR(vec, pVec);

	v0 = (vector float) vec_splat_u32(0);
	vec_1 = vec_splat(vec, 0);
	vec_2 = vec_splat(vec, 1);
	vec_3 = vec_splat(vec, 2);

	// Do the vector x matrix multiplication
	vr_1 = vec_madd(vm_1, vec_1, v0);
	vr_2 = vec_madd(vm_2, vec_2, vr_1);
	vr_3 = vec_madd(vm_3, vec_3, vr_2);
	vr   = vec_add(vr_3, vm_4);

	// Store back the result
	STORE_VECTOR(vr, pVec);
}

void SIMDx86Matrix_VectorMultiplyOf_AltiVec(SIMDx86Vector* pOut, const SIMDx86Vector* pIn, const SIMDx86Matrix* pMat)
{
	vector float vm_1, vm_2, vm_3, vm_4,
	             vec, vec_1, vec_2, vec_3, 
	             vr, vr_1, vr_2, vr_3, v0;

	// Load matrix and vector
	LOAD_MATRIX(pMat, vm_1, vm_2, vm_3, vm_4);
	LOAD_VECTOR(vec, pIn);

	v0 = (vector float) vec_splat_u32(0);
	vec_1 = vec_splat(vec, 0);
	vec_2 = vec_splat(vec, 1);
	vec_3 = vec_splat(vec, 2);

	// Do the vector x matrix multiplication
	vr_1 = vec_madd(vm_1, vec_1, v0);
	vr_2 = vec_madd(vm_2, vec_2, vr_1);
	vr_3 = vec_madd(vm_3, vec_3, vr_2);
	vr   = vec_add(vr_3, vm_4);

	// Store back the result
	STORE_VECTOR(vr, pOut);
}

void SIMDx86Matrix_Vector4Multiply_AltiVec(float* pOut4D, const SIMDx86Matrix* pMat)
{
	vector float vm_1, vm_2, vm_3, vm_4,
	             vec, vec_1, vec_2, vec_3, vec_4,
	             vr, vr_1, vr_2, vr_3, v0;

	// Load matrix and vector
	LOAD_MATRIX(pMat, vm_1, vm_2, vm_3, vm_4);
	LOAD_VECTOR(vec, pOut4D);

	v0 = (vector float) vec_splat_u32(0);
	vec_1 = vec_splat(vec, 0);
	vec_2 = vec_splat(vec, 1);
	vec_3 = vec_splat(vec, 2);
	vec_4 = vec_splat(vec, 3);

	// Do the vector x matrix multiplication
	vr_1 = vec_madd(vm_1, vec_1, v0);
	vr_2 = vec_madd(vm_2, vec_2, vr_1);
	vr_3 = vec_madd(vm_3, vec_3, vr_2);
	vr   = vec_madd(vm_4, vec_4, vr_3);

	// Store back the result
	STORE_VECTOR(vr, pOut4D);
}

void SIMDx86Matrix_Vector4MultiplyOf_AltiVec(float* pOut4D, const float* pIn4D, const SIMDx86Matrix* pMat)
{
	vector float vm_1, vm_2, vm_3, vm_4,
	             vec, vec_1, vec_2, vec_3, vec_4,
	             vr, vr_1, vr_2, vr_3, v0;

	// Load matrix and vector
	LOAD_MATRIX(pMat, vm_1, vm_2, vm_3, vm_4);
	LOAD_VECTOR(vec, pIn4D);

	v0 = (vector float) vec_splat_u32(0);
	vec_1 = vec_splat(vec, 0);
	vec_2 = vec_splat(vec, 1);
	vec_3 = vec_splat(vec, 2);
	vec_4 = vec_splat(vec, 3);

	// Do the vector x matrix multiplication
	vr_1 = vec_madd(vm_1, vec_1, v0);
	vr_2 = vec_madd(vm_2, vec_2, vr_1);
	vr_3 = vec_madd(vm_3, vec_3, vr_2);
	vr   = vec_madd(vm_4, vec_4, vr_3);

	// Store back the result
	STORE_VECTOR(vr, pOut4D);
}

void SIMDx86Matrix_ToIdentity_AltiVec(SIMDx86Matrix* pMat)
{
	vector float vi1, vi2, vi3, vi4;
	vector unsigned int sh;
 
	vi4 = vec_ctf(vec_splat_u32(1),0);
	sh = vec_splat_u32(12);
	sh = vec_sll(sh, vec_splat_u32(3));
	vi4 = vec_sro(vi4, (vector char)sh);
	vi3 = vec_sld(vi4, vi4, 4);
	vi2 = vec_sld(vi3, vi3, 4);
	vi1 = vec_sld(vi2, vi2, 4);
 
	// Store back the identity matrix
	STORE_MATRIX(pMat, vi1, vi2, vi3, vi4);
}

void SIMDx86Matrix_ToTranslate_AltiVec(SIMDx86Matrix* pMat, float x, float y, float z)
{
	vector float v0 = (vector float)vec_splat_u32(0);

	STORE_VECTOR(v0, &pMat->m[0]);
	STORE_VECTOR(v0, &pMat->m[4]);
	STORE_VECTOR(v0, &pMat->m[8]);
	pMat->m[12] = x; pMat->m[13] = y; pMat->m[14] = z; pMat->m[15] = 1.0f;
}

void SIMDx86Matrix_ToTranslateOf_AltiVec(SIMDx86Matrix* pMat, const SIMDx86Vector* pVec)
{
	vector float vec;
	vector float v0 = (vector float)vec_splat_u32(0);
	LOAD_VECTOR(vec, pVec);

	STORE_VECTOR(v0, &pMat->m[0]);
	STORE_VECTOR(v0, &pMat->m[4]);
	STORE_VECTOR(v0, &pMat->m[8]);
	STORE_VECTOR(vec, &pMat->m[12]);
	pMat->m[15] = 1.0f;
}

SIMDx86Matrix *SIMDx86Matrix_InverseOf_AltiVec(SIMDx86Matrix* pOut, const SIMDx86Matrix* pIn) {

	// Calculate the determinant, using the following formula:
	// detM = detP * det(S - R*P^(-1)*Q)
	// where:   | a1 a2 a3 a4 |   
	//      M = | b1 b2 b3 b4 | = | P Q |
	//          | c1 c2 c3 c4 |   | R S |
	//          | d1 d2 d3 d4 |
	// We use Block matrices and Liebniz Formula:
	// http://en.wikipedia.org/wiki/Determinant
	
	// Calculate detP first. if detP = 0 just return 0
	// Make sure we align it properly to be used later in a vector
	// detSRPQ will in fact hold det(S - R*P^(-1)*Q)
	// 
	//float ALIGNMENT_PREFIX dummy[4] ALIGNMENT_SUFFIX;

	vector float vm_1, vm_2, vm_3, vm_4, vp_1, vp_2, vq_1, vq_2, 
		     vpq_1, vpq_2, vrp_1, vrp_2,
		     vrpq_1, vrpq_2, vsrpq_1, vsrpq_2, vt_1, vt_2, vt_3, vt_4,
		     vdet, vdetSRPQ, invdet, v0f, v05;
	vector unsigned int v1_, v0, v0_, u_znzn, u_nznz;
//	vector char v8, v08, perm;
	vector char perm = { 0, 1, 2, 3, 4, 5, 6, 7, 16, 17, 18, 19, 20, 21, 22, 23 };

	// Useful constants, esp the v0_ is used to fix the +/- sign to some float vectors
	v0 = vec_splat_u32(0);
	v1_ = vec_splat_u32(-1);
	v0_ = vec_sl(v1_, v1_);
	v0f = (vector float)v0;
	u_nznz = vec_mergeh(v0_, v0);
	u_znzn = vec_mergeh(v0, v0_);
	// This trick suggested by Grzegorz Kraszewski, thanks :)
/*	v8 = vec_splat_u8(8);
	v08 = vec_sld((vector char)v0, v8, 8);
	perm = vec_add(vec_lvsl(0, &pIn->m[0]), v08);*/

	// Set up some constants for inverse reciprocals
	// Use Altivec vec_ctf to splat 0.5.
/*	v05 = vec_ctf(vec_splat_u32(2), 2);

	vector float y, v1, v05;
	v1 = vec_ctf(vec_splat_u32(1), 0);*/

	// Load SIMDx86 matrix
	LOAD_MATRIX(&pIn->m[0], vm_1, vm_2, vm_3, vm_4);

	// Calculate determinant of submatrix P
	// | a1 a2 a3 a4 | -> mergeh -> | b1 a1 b2 a2 |
	// | b1 b2 b3 b4 |
	vt_1 = vec_mergeh(vm_2, vm_1);

	// shift left by 32-bits -> | a1 b2 a2 b1 |
	vt_2 = vec_sld(vt_1, vm_2, 4);
	// multiply add vt_1 x vt_2 -> | a1b1 | a1b2 | b2a2 | a2b1 |
	vt_3 = vec_madd(vt_1, vt_2, v0f);
	// shift left vt_3 by 64-bits - > | b2a2 | a2b1 | 0 | 0 |
	vt_4 = vec_sld(vt_3, vt_3, 8);
	// subtract vt_3 from vt_4 -> | .. | a1b2-a2b1 | .. | .. |
	vdet = vec_sub(vt_3, vt_4);

	// Splat det
	vdet = vec_splat(vdet, 1);

	if (vec_all_eq(vdet, v0f)) return NULL; // FIXME: there are cases where detP = 0 !=> detM = 0

	// Get 1/detP
	invdet = vec_re(vdet);

	// Now calculate S - R*P^(-1)*Q.
	// Or to make advantage of the SIMD data layout, we could use 2x4 matrix:
	// we first have to multiply [R 0 ] * [P^(-1) 0] and the result with [Q 0]
	// and finally subtract the result from [S 0]
	// But first we have to find the inverse of P^(-1) (since detP != 0 it is certain it exists)
	// The inverse of a 2x2 matrix is:
	// P^(-1) =  |  b2 -a2 |/detP
	//           | -b1  a1 |
	// We need to permute, but to save loading the permute masks from memory, we'll use mergeh
	// vp_2 -> mergeh(vm_2, vm_1) -> | b1 a1 b2 a2 |
	// vp_1 -> vp_2 << 64 = | b2 a2 0 0 |
	vp_2 = vec_mergeh(vm_2, vm_1);
	vp_1 = vec_sld(vp_2, vp_2, 8);

	// Fix the signs in vp_1:
	// vp_1 -> |  b2 -a2 |
	// vp_2 -> | -b1  a1 |
	// This part inspired from http://www.cellperformance.com/articles/2006/06/a_4x4_matrix_inverse_1.html
	vp_1 = (vector float) vec_xor((vector unsigned int) vp_1, u_znzn);
	vp_2 = (vector float) vec_xor((vector unsigned int) vp_2, u_nznz);

	// We now have the adjoint of P
	// Multiply each element with inverse detP to get P^(-1)
	vp_1 = vec_madd(vp_1, invdet, v0f);
	vp_2 = vec_madd(vp_2, invdet, v0f);

	// Now P^(-1) is calculated, we can proceed to the first product: R*P^(-1) (1)
	// The product is done like for a 4x4 matrix but only for the first 2 lines
	// and the first 2 columns
	// Calculate the first column of p1
	vt_1 = vec_madd( vec_splat( vm_3, 0 ), vp_1, v0f );
	vt_2 = vec_madd( vec_splat( vm_4, 0 ), vp_1, v0f );
 
	// Multiply the 2nd column of p1, add to previous result
	vrp_1 = vec_madd( vec_splat( vm_3, 1 ), vp_2, vt_1 );
	vrp_2 = vec_madd( vec_splat( vm_4, 1 ), vp_2, vt_2 );

	// Calculate R*P^(-1)*Q, just multiply previous result with Q
	// using same method
	vrpq_1 = vec_madd( vec_splat( vrp_1, 0 ), vm_1, v0f );
	vrpq_2 = vec_madd( vec_splat( vrp_2, 0 ), vm_1, v0f );
 
	// Multiply the 2nd column of p1, add to previous result
	vrpq_1 = vec_madd( vec_splat( vrp_1, 1 ), vm_2, vrpq_1 );
	vrpq_2 = vec_madd( vec_splat( vrp_2, 1 ), vm_2, vrpq_2 );

	// Calculate P^(-1)*Q also 
	vq_1 = vec_sld(vm_1, v0f, 8);
	vq_2 = vec_sld(vm_2, v0f, 8);
	vpq_1 = vec_madd( vec_splat( vp_1, 0 ), vq_1, v0f );
	vpq_2 = vec_madd( vec_splat( vp_2, 0 ), vq_1, v0f );
 
	// Multiply the 2nd column of p1, add to previous result
	vpq_1 = vec_madd( vec_splat( vp_1, 1 ), vq_2, vpq_1 );
	vpq_2 = vec_madd( vec_splat( vp_2, 1 ), vq_2, vpq_2 );

	// S - R*P^(-1)*Q
	// Finally, just subtract the previous result from S
	vsrpq_1 = vec_sub(vm_3, vrpq_1);
	vsrpq_2 = vec_sub(vm_4, vrpq_2);

	vt_2 = vec_sld(vsrpq_2, v0f, 8);
	vt_1 = vec_sld(vsrpq_1, vt_2, 8);
	
	// Get the determinant of (S - R*P^(-1)*Q) and multiply with detSRPQ
        vt_3 = vec_sld(vt_1, vt_1, 4);
        vt_4 = vec_nmsub(vt_1, vt_3, v0f);
        vt_3 = vec_sld(vt_4, vt_4, 8);
        vdetSRPQ = vec_sub(vt_3, vt_4);
	vdetSRPQ = vec_splat(vdetSRPQ, 3);

	// Multiply with detP and get the full determinant
	vdet = vec_madd(vdet, vdetSRPQ, v0f);

	// If determinant is equal to 0.0 then we have no inverse and return NULL
	if (vec_all_eq(vdet, v0f)) return NULL;

	// determinant != 0.0 so inverse exists, calculate it
	// Get the inverse of (S - R*P^(-1)*Q), repeat the procedure
	// Get 1/detSRPQ
	invdet = vec_re(vdetSRPQ);

	vt_2 = vec_mergeh(vt_2, vt_1);
	vt_1 = vec_sld(vt_2, vt_2, 8);

	vector float vP_1, vP_2, vQ_1, vQ_2, vR_1, vR_2, vS_1, vS_2;
	// Fix the signs in vS_1:
	vS_1 = (vector float) vec_xor((vector unsigned int) vt_1, u_znzn);
	vS_2 = (vector float) vec_xor((vector unsigned int) vt_2, u_nznz);

	// We now have the adjoint of P
	// Multiply each element with inverse detP to get (S - R*P^(-1)*Q)^(-1)
	vS_1 = vec_madd(vS_1, invdet, v0f);
	vS_2 = vec_madd(vS_2, invdet, v0f);
	// Checkpoint #1: We got S' 

	// R' = -S'*(R*P^(-1))
	// Just multiply previous result with vrp 
	// using same method
	// Since we have to negate the result, we use instead vec_nmsub()
	vR_1 = vec_nmsub( vec_splat( vS_1, 0 ), vrp_1, v0f );
	vR_2 = vec_nmsub( vec_splat( vS_2, 0 ), vrp_1, v0f );
 
	// Multiply the 2nd column of p1, add to previous result (using nmsub()
	vR_1 = vec_nmsub( vec_splat( vS_1, 1 ), vrp_2, vR_1 );
	vR_2 = vec_nmsub( vec_splat( vS_2, 1 ), vrp_2, vR_2 );
	// Checkpoint #2: We got R' 

	// Q' = -(P^(-1)*Q)*S'
	vQ_1 = vec_nmsub( vec_splat( vpq_1, 0 ), vS_1, v0f );
	vQ_2 = vec_nmsub( vec_splat( vpq_2, 0 ), vS_1, v0f );
 
	// Multiply the 2nd column of p1, add to previous result
	vQ_1 = vec_nmsub( vec_splat( vpq_1, 1 ), vS_2, vQ_1 );
	vQ_2 = vec_nmsub( vec_splat( vpq_2, 1 ), vS_2, vQ_2 );
	// Checkpoint #3: We got Q' 

	// P' = P^(-1) - (P^(-1)*Q)*R'
	vP_1 = vec_madd( vec_splat( vpq_1, 0 ), vR_1, v0f );
	vP_2 = vec_madd( vec_splat( vpq_2, 0 ), vR_1, v0f );
 
	// Multiply the 2nd column of p1, add to previous result
	vP_1 = vec_madd( vec_splat( vpq_1, 1 ), vR_2, vP_1 );
	vP_2 = vec_madd( vec_splat( vpq_2, 1 ), vR_2, vP_2 );

	vP_1 = vec_sub(vp_1, vP_1);
	vP_2 = vec_sub(vp_2, vP_2);
	// Checkpoint #4: We got P' 

	// Finished, now let's put these back together to one matrix (4 vectors)
	// all P', Q', R', S' matrices have the needed block in the left 2x2 part
	// in the vP_*, vQ_*, vR_*, vS_* vectors. We need to shift right by 64 bits
	// the vQ_* and vS_* vectors and merge left 2x2 block of vP_* with the right
	// 2x2 block of vQ_*. Same with vR_* and vS_*. And then we have our inverse
	// matrix
	vm_1 = vec_perm(vP_1, vQ_1, perm);
	vm_2 = vec_perm(vP_2, vQ_2, perm);
	vm_3 = vec_perm(vR_1, vS_1, perm);
	vm_4 = vec_perm(vR_2, vS_2, perm);

	// Store the resulting inverse matrix
	STORE_MATRIX(&pOut->m[0], vm_1, vm_2, vm_3, vm_4);
}

