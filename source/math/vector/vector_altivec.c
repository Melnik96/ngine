/*
	vector.c -- SIMDx86 3D Vector Library
	Written by Patrick Baggett, 2005 (baggett.patrick@gmail.com)
	AltiVec code by Konstantinos Margaritis <markos@debian.gr)
	Under LGPL License
	Part of SIMDx86 Project
*/

#include <altivec.h>
#include <memory.h>
#include <math.h> /* sqrtf() */

#include <SIMDx86/align.h>
#include <SIMDx86/vector.h>
#include <SIMDx86/consts.h>
#include "SIMDx86/SIMDx86_altivec.h"

void SIMDx86Vector_Sum_AltiVec(SIMDx86Vector* pOut, const SIMDx86Vector* pIn)
{
	// Load SIMDx86 vectors
	vector float vin, vout, vres;
	LOAD_VECTOR(vin, pIn);
	LOAD_VECTOR(vout, pOut); 

	// Add the vectors
	vres = vec_add(vin, vout);

	// Store back the result
	STORE_VECTOR(vres, pOut);
}

void SIMDx86Vector_SumOf_AltiVec(SIMDx86Vector* pOut, const SIMDx86Vector* pIn1, const SIMDx86Vector* pIn2)
{
	// Load SIMDx86 vectors
	vector float vin, vout, vres;
	LOAD_VECTOR(vin, pIn1);
	LOAD_VECTOR(vout, pIn2); 

	// Add the vectors
	vres = vec_add(vin, vout);

	// Store back the result
	STORE_VECTOR(vres, pOut);
}

void SIMDx86Vector_Diff_AltiVec(SIMDx86Vector* pLeft, SIMDx86Vector* pRight)
{
	// Load SIMDx86 vectors
	vector float vleft, vright, vres;
	LOAD_VECTOR(vleft, pLeft);
	LOAD_VECTOR(vright, pRight); 

	// Add the vectors
	vres = vec_add(vleft, vright);

	// Store back the result
	STORE_VECTOR(vres, pLeft);
}

void SIMDx86Vector_DiffOf_AltiVec(SIMDx86Vector* pOut, const SIMDx86Vector* pLeft, const SIMDx86Vector* pRight)
{
	// Load SIMDx86 vectors
	vector float vleft, vright, vres;
	LOAD_VECTOR(vleft, pLeft);
	LOAD_VECTOR(vright, pRight); 

	// Add the vectors
	vres = vec_add(vleft, vright);

	// Store back the result
	STORE_VECTOR(vres, pOut);
}

void SIMDx86Vector_Scale_AltiVec(SIMDx86Vector* pOut, float scalar)
{
	// Load SIMDx86 vector and scalar at once.
	vector float vin = vec_ld(0, (float *)pOut);
	vector float vscalar = {scalar, scalar, scalar, 0.0};
	vector float v0 = (vector float) vec_splat_u32(0);
	vector float vres;

	// Do the scaling
	vres = vec_madd(vin, vscalar, v0);

        // Store back the result
	vec_st(vres, 0, (float *)pOut);
}

void SIMDx86Vector_ScaleOf_AltiVec(SIMDx86Vector* pOut, const SIMDx86Vector* pIn, float scalar)
{
	// Load SIMDx86 vector and scalar at once.
	vector float vin = vec_ld(0, (float *)pIn);
	vector float vscalar = {scalar, scalar, scalar, 0.0};
	vector float v0 = (vector float) vec_splat_u32(0);
	vector float vres;

	// Do the scaling
	vres = vec_madd(vin, vscalar, v0);

        // Store back the result
	vec_st(vres, 0, (float *)pOut);
}

float SIMDx86Vector_Dot_AltiVec(const SIMDx86Vector* pSrc1, const SIMDx86Vector* pSrc2)
{
	// Load SIMDx86 vector and scalar at once.
	vector float vsrc1 = vec_ld(0, (float *)pSrc1);
	vector float vsrc2 = vec_ld(0, (float *)pSrc2);
	vector float v0 = (vector float) vec_splat_u32(0);
	vector float vres1, vres2;
	float ALIGNMENT_PREFIX res[4];

	// do the multiplication
	vres1 = vec_madd(vsrc1, vsrc2, v0);
	// rotate the vector by two floats and add it to itself
	vres2 = vec_sld(vres1, vres1, 8);
	vres1 = vec_add(vres1, vres2);
	// rotate the vector one more float and again add it to itself
	vres2 = vec_sld(vres1, vres1, 4);
	vres1 = vec_add(vres1, vres2);

        // store back the result
	vec_st(vres1, 0, (float *)res);
	return res[0];
}

float SIMDx86Vector_Dot4_AltiVec(const float* pSrc4D1, const float* pSrc4D2)
{
	// Load SIMDx86 vector and scalar at once.
	vector float vsrc1 = vec_ld(0, (float *)pSrc4D1);
	vector float vsrc2 = vec_ld(0, (float *)pSrc4D2);
	vector float v0 = (vector float) vec_splat_u32(0);
	vector float vres1, vres2;
	float ALIGNMENT_PREFIX res[4];

	// do the multiplication
	vres1 = vec_madd(vsrc1, vsrc2, v0);
	// rotate the vector by two floats and add it to itself
	vres2 = vec_sld(vres1, vres1, 8);
	vres1 = vec_add(vres1, vres2);
	// rotate the vector one more float and again add it to itself
	vres2 = vec_sld(vres1, vres1, 4);
	vres1 = vec_add(vres1, vres2);

        // store back the result
	vec_st(vres1, 0, (float *)res);
	return res[0];
}

float SIMDx86Vector_LengthSq_AltiVec(const SIMDx86Vector* pVec)
{
	// Load SIMDx86 vector and scalar at once.
	vector float vvec = vec_ld(0, (float *)pVec);
	vector float v0 = (vector float) vec_splat_u32(0);
	vector float vres1, vres2;
	float ALIGNMENT_PREFIX res[4];

	// do the multiplication
	vres1 = vec_madd(vvec, vvec, v0);
	// rotate the vector by two floats and add it to itself
	vres2 = vec_sld(vres1, vres1, 8);
	vres1 = vec_add(vres1, vres2);
	// rotate the vector one more float and again add it to itself
	vres2 = vec_sld(vres1, vres1, 4);
	vres1 = vec_add(vres1, vres2);

        // store back the result
	vec_st(vres1, 0, (float *)res);
	return res[0];
}

float SIMDx86Vector_Length_AltiVec(const SIMDx86Vector* pVec)
{
	// Load SIMDx86 vector 
	vector float vvec = vec_ld(0, (float *)pVec);
	vector float v0 = (vector float) vec_splat_u32(0), v1 = (vector float) vec_splat_u32(1), v05 = {0.5f, 0.5f, 0.5f, 0.5f};
	vector float vres1, vres2;
	float ALIGNMENT_PREFIX res[4];

	// do the multiplication
	vres1 = vec_madd(vvec, vvec, v0);
	// rotate the vector by two floats and add it to itself
	vres2 = vec_sld(vres1, vres1, 8);
	vres1 = vec_add(vres1, vres2);
	// rotate the vector one more float and again add it to itself
	vres2 = vec_sld(vres1, vres1, 4);
	vres1 = vec_add(vres1, vres2);

	// Get the square root using the following trick
	// Calculate -0.0 and put it in a vector (needed for IEEE754 compliance)
	vector unsigned int vtmp = vec_splat_u32(-1);
	vector float _0 = (vector float)(vec_sl(vtmp, vtmp));
	vector float y = vec_rsqrte(vres1);
	// two rounds of Newton-Raphson
	y = vec_madd(vec_nmsub(vres1,vec_madd(y,y,_0),v1),vec_madd(y,v05,_0),y);
	y = vec_madd(vec_nmsub(vres1,vec_madd(y,y,_0),v1),vec_madd(y,v05,_0),y);
	vres1 = vec_sel(vec_madd(vres1,y,_0),_0,vec_cmpeq(vres1,_0));
	
        // store back the result
	vec_st(vres1, 0, (float *)res);
	return res[0];
}

void SIMDx86Vector_Cross_AltiVec(SIMDx86Vector* pLeft, const SIMDx86Vector* pRight)
{
	// Load SIMDx86 vector and scalar at once.
	vector float vleft  = vec_ld(0, (float *)pLeft);
	vector float vright = vec_ld(0, (float *)pRight);
	vector float v0 = (vector float) vec_splat_u32(0);
	vector float vtmp1, vtmp2, vtmp3, vtmp4, vres;
	vector unsigned char perm1 = { 4, 5, 6, 7, 8, 9, 10, 11, 0, 1, 2, 3, 0, 1, 2, 3};
	vector unsigned char perm2 = { 8, 9, 10, 11, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3};
	float ALIGNMENT_PREFIX res[4];

	// get the temporary vectors (y, z, x, PAD) and (z, x, y, PAD)
	vtmp1 = vec_perm(vleft, vleft, perm1);
	vtmp2 = vec_perm(vleft, vleft, perm2);
	vtmp3 = vec_perm(vright, vleft, perm2);
	vtmp4 = vec_perm(vright, vleft, perm1);

	// Multiply vtmp1 x vtmp3 and vtmp2 x vtmp4
	vtmp1 = vec_madd(vtmp1, vtmp3, v0);
	vtmp2 = vec_madd(vtmp2, vtmp4, v0);

	// Subtract the products
	vres = vec_sub(vtmp1, vtmp2);

	// Store the result
	vec_st(vres, 0, (float *)pLeft);
}

void SIMDx86Vector_CrossOf_AltiVec(SIMDx86Vector* pOut, const SIMDx86Vector* pLeft, const SIMDx86Vector* pRight)
{
	// Load SIMDx86 vector and scalar at once.
	vector float vleft  = vec_ld(0, (float *)pLeft);
	vector float vright = vec_ld(0, (float *)pRight);
	vector float v0 = (vector float) vec_splat_u32(0);
	vector float vtmp1, vtmp2, vtmp3, vtmp4, vres;
	vector unsigned char perm1 = { 4, 5, 6, 7, 8, 9, 10, 11, 0, 1, 2, 3, 0, 1, 2, 3};
	vector unsigned char perm2 = { 8, 9, 10, 11, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3};
	float ALIGNMENT_PREFIX res[4];

	// get the temporary vectors (y, z, x, PAD) and (z, x, y, PAD)
	vtmp1 = vec_perm(vleft, vleft, perm1);
	vtmp2 = vec_perm(vleft, vleft, perm2);
	vtmp3 = vec_perm(vright, vleft, perm2);
	vtmp4 = vec_perm(vright, vleft, perm1);

	// Multiply vtmp1 x vtmp3 and vtmp2 x vtmp4
	vtmp1 = vec_madd(vtmp1, vtmp3, v0);
	vtmp2 = vec_madd(vtmp2, vtmp4, v0);

	// Subtract the products
	vres = vec_sub(vtmp1, vtmp2);

	// Store the result
	vec_st(vres, 0, (float *)pOut);
}

void SIMDx86Vector_Normalize_AltiVec(SIMDx86Vector* pVec)
{
	// Load SIMDx86 vector 
	vector float vvec = vec_ld(0, (float *)pVec);
	vector float vc0 = vec_ctf(vec_splat_u32(0), 0);
	vector float v1, v2, vsqrt, vres;
	float ALIGNMENT_PREFIX res[4];

	// do the multiplication
	v1 = vec_madd(vvec, vvec, vc0);
	// rotate the vector by two floats and add it to itself
	v2 = vec_sld(v1, v1, 8);
	v1 = vec_add(v1, v2);
	// rotate the vector one more float and again add it to itself
	v2 = vec_sld(v1, v1, 4);
	v1 = vec_add(v1, v2);

	// calculate the reciprocal square root estimate
	// This is not SSE, AltiVec doesn't provide square root and division
	// instructions. We'll start with the estimate and if HIPREC is #defined
	// we'll do a couple of Newton-Raphson approximations -usually this gives
	// pretty good precision.
	vsqrt = vec_rsqrte(v1);

	#ifdef HIPREC
	// If high precision is required we can accomplish this with 2 consecutive
	// Newton-Raphson methods. Taken from Ian Ollman's PDF at:
	// http://cluster.earlham.edu/detail/home/joshh/doc/Altivec.pdf
	vector float vneg_zero, vc1, vc1half, vre_est, vsqrt_hre_est;
	// Calculate -0.0 and put it in a vector (needed for IEEE754 compliance)
	vector unsigned int vtmp = vec_splat_u32(-1);
	vneg_zero = (vector float)(vec_sl(vtmp, vtmp));

	// We need a couple more constants
	vc1 = vec_ctf(vec_splat_u32(1), 0);
	vc1half = vec_ctf( vec_splat_u32(1), 1 );
	// Calculate reciprocal estimate
	vre_est = vec_madd(vsqrt, vsqrt, vneg_zero);
	vsqrt_hre_est = vec_madd( vsqrt, vc1half, vneg_zero );

	// First term in Newton-Raphson approximation
	vector float term1 = vec_nmsub( v1, vre_est, vc1 );
	// multiply with the vector elements to get the normalized vector
        vsqrt = vec_madd( term1, vsqrt_hre_est, vsqrt );
	#endif
	// multiply with the vector elements to get the normalized vector
	vres = vec_madd(vvec, vsqrt, vc0);
        // store back the result
	vec_st(vres, 0, (float *)pVec);
}

void SIMDx86Vector_NormalizeOf_AltiVec(SIMDx86Vector* pOut, const SIMDx86Vector* pVec)
{
	// Load SIMDx86 vector 
	vector float vvec = vec_ld(0, (float *)pVec);
	vector float vc0 = vec_ctf(vec_splat_u32(0), 0);
	vector float v1, v2, vsqrt, vres;
	float ALIGNMENT_PREFIX res[4];

	// do the multiplication
	v1 = vec_madd(vvec, vvec, vc0);
	// rotate the vector by two floats and add it to itself
	v2 = vec_sld(v1, v1, 8);
	v1 = vec_add(v1, v2);
	// rotate the vector one more float and again add it to itself
	v2 = vec_sld(v1, v1, 4);
	v1 = vec_add(v1, v2);

	// calculate the reciprocal square root estimate
	// This is not SSE, AltiVec doesn't provide square root and division
	// instructions. We'll start with the estimate and if HIPREC is #defined
	// we'll do a couple of Newton-Raphson approximations -usually this gives
	// pretty good precision.
	vsqrt = vec_rsqrte(v1);

	#ifdef HIPREC
	// If high precision is required we can accomplish this with 2 consecutive
	// Newton-Raphson methods. Taken from Ian Ollman's PDF at:
	// http://cluster.earlham.edu/detail/home/joshh/doc/Altivec.pdf
	vector float vneg_zero, vc1, vc1half, vre_est, vsqrt_hre_est;
	// Calculate -0.0 and put it in a vector (needed for IEEE754 compliance)
	vector unsigned int vtmp = vec_splat_u32(-1);
	vneg_zero = (vector float)(vec_sl(vtmp, vtmp));

	// We need a couple more constants
	vc1 = vec_ctf(vec_splat_u32(1), 0);
	vc1half = vec_ctf( vec_splat_u32(1), 1 );
	// Calculate reciprocal estimate
	vre_est = vec_madd(vsqrt, vsqrt, vneg_zero);
	vsqrt_hre_est = vec_madd( vsqrt, vc1half, vneg_zero );

	// First term in Newton-Raphson approximation
	vector float term1 = vec_nmsub( v1, vre_est, vc1 );
	// multiply with the vector elements to get the normalized vector
        vsqrt = vec_madd( term1, vsqrt_hre_est, vsqrt );
	#endif
	// multiply with the vector elements to get the normalized vector
	vres = vec_madd(vvec, vsqrt, vc0);
        // store back the result
	vec_st(vres, 0, (float *)pOut);
}
