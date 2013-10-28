/*
	plane.c -- SIMDx86 Plane Library
	Written by Patrick Baggett, 2005 (baggett.patrick@gmail.com)
	Under LGPL License
	Part of SIMDx86 Project
*/

#include <SIMDx86/plane.h>
#include <SIMDx86/consts.h>
#include <memory.h>
#include <math.h>	/* sqrtf() */
#include <float.h>	/* FLT_EPSILON */


void SIMDx86Plane_FromPolygon(SIMDx86Plane* pOut, const SIMDx86Polygon* pPoly)
{
	
	#if defined(USE_SSE)
	asm(
	"movups   (%0), %%xmm0\n"	/* pPoly->a */
	"movups 16(%0), %%xmm1\n"	/* pPoly->b */
	"movups 32(%0), %%xmm2\n"	/* pPoly->c */
	"movaps %%xmm0, %%xmm7\n"   /* Save 'a' into xmm7 */
	"subps %%xmm1, %%xmm0\n"
	"subps %%xmm1, %%xmm2\n"

	/* Now, just need the cross product of xmm0 and xmm2 */
	"movaps %%xmm0, %%xmm1\n"	/* xmm0 = xmm1 = Left */
	"movaps %%xmm2, %%xmm3\n"	/* xmm2 = xmm3 = Right */
	"shufps $0xC9, %%xmm0, %%xmm0\n"	/* Left.yxz */
	"shufps $0xD2, %%xmm1, %%xmm1\n"	/* Left.xzy */
	"shufps $0xD2, %%xmm2, %%xmm2\n"	/* Right.xzy */
	"shufps $0xC9, %%xmm3, %%xmm3\n"	/* Right.yxz */

	/* Multiply columns 1&2 and 3&4 */
	"mulps %%xmm0, %%xmm2\n"
	"mulps %%xmm1, %%xmm3\n"

	/* Got the cross product, OK */		
	"subps %%xmm3, %%xmm2\n"

	/* Begin calculation of 'd' component */


	/* AND off bits 96-127 (w component) */	
	"andps _SIMDx86_float_SSE_NO_W_MASK, %%xmm2\n"

	/* save xmm4 = 0 | z | y | x */
	"movaps %%xmm2, %%xmm4\n"

	/* Multiply with point 'a' on the polygon (saved in xmm7): xmm2 = 0 | a.z*z | a.y*y | a.x*x */
	"mulps %%xmm7, %%xmm2\n"

	#if USE_SSE >= 3

	/* horizontally add, xmm2 = x^2+y^2+z^2 | x^2+y^2+z^2 | x^2+y^2+z^2 | x^2+y^2+z^2  */
	"haddps %%xmm2, %%xmm2\n"
	"haddps %%xmm2, %%xmm2\n"
	
	/* change sign for top component, remove bits for others */
	"xorps _SIMDx86_float_POSPOSPOSNEG, %%xmm2\n"		/* xmm2 = -(x^2+y^2+z^2) | .... | ...*/
	"andps _SIMDx86_float_SSE_NO_XYZ_MASK, %%xmm2\n"		/* xmm2 = -(x^2+y^2+z^2) | 0 | 0 | 0 */
	"orps %%xmm2, %%xmm4\n"							/* xmm4 = -(x^2+y^2+z^2) | z | y | x */

	#else

	"movhlps %%xmm2, %%xmm3\n"		/* xmm3 = ?   | ?   | 0   |  z^2 */
	"addss %%xmm2, %%xmm3\n"		/* xmm3 = ?   | ?   | 0   | z^2 + x^2 */
	"shufps $0x55, %%xmm2, %%xmm2\n"/* xmm2 = y^2 | y^2 | y^2 | y^2 */
	"addss %%xmm2, %%xmm3\n"		/* xmm3 = ?   | ?   | ?   | x^2+y^2+z^2 */

	/* Change sign */
	"xorps _SIMDx86_float_NEGPOSPOSPOS, %%xmm3\n" /* xmm3 = ? | ? | ? | -(x^2+y^2+z^2)*/

	/* Move to w component location, mask off xyz, and OR with saved portions */
	"shufps $0x00, %%xmm3, %%xmm3\n"				/* xmm3 = -(x^2+y^2+z^2) | -(x^2+y^2+z^2) | -(x^2+y^2+z^2) | -(x^2+y^2+z^2)*/
	"andps _SIMDx86_float_SSE_NO_XYZ_MASK, %%xmm3\n"/* xmm3 = -(x^2+y^2+z^2) | 0 | 0 | 0 */
	"orps %%xmm3, %%xmm4\n"							/* xmm4 = -(x^2+y^2+z^2) | z | y | x */

	#endif /* Not using SSE3 */

	/* Save plane coefficients */
	"movups %%xmm4, (%1)\n"
	:
	: "r" (pPoly), "r" (pOut)
	);		

	#else
	SIMDx86Vector n;

	/* Get the normal for this */
	SIMDx86Polygon_PlaneNormal(&n, pPoly);
	/* Solve for d with scalar product */
	pOut->a = n.x;
	pOut->b = n.y;
	pOut->c = n.z;
	pOut->d = -(n.x*pPoly->a.x + n.y*pPoly->a.y + n.z*pPoly->a.z);
	#endif
}

void SIMDx86Plane_FromPoints(SIMDx86Plane* pOut, const SIMDx86Vector* pA, const SIMDx86Vector* pB,const SIMDx86Vector* pC)
{
	#if defined(USE_SSE)
	asm(
	"movups (%0), %%xmm0\n"	/* pA */
	"movups (%1), %%xmm1\n"	/* pB */
	"movups (%2), %%xmm2\n"	/* pC */
	"movaps %%xmm0, %%xmm7\n"   /* Save 'a' into xmm7 */
	"subps %%xmm1, %%xmm0\n"
	"subps %%xmm1, %%xmm2\n"

	/* Now, just need the cross product of xmm0 and xmm2 */
	"movaps %%xmm0, %%xmm1\n"	/* xmm0 = xmm1 = Left */
	"movaps %%xmm2, %%xmm3\n"	/* xmm2 = xmm3 = Right */
	"shufps $0xC9, %%xmm0, %%xmm0\n"	/* Left.yxz */
	"shufps $0xD2, %%xmm1, %%xmm1\n"	/* Left.xzy */
	"shufps $0xD2, %%xmm2, %%xmm2\n"	/* Right.xzy */
	"shufps $0xC9, %%xmm3, %%xmm3\n"	/* Right.yxz */

	/* Multiply columns 1&2 and 3&4 */
	"mulps %%xmm0, %%xmm2\n"
	"mulps %%xmm1, %%xmm3\n"

	/* Got the cross product, OK */
	"subps %%xmm3, %%xmm2\n"

	/* Begin calculation of 'd' component */


	/* AND off bits 96-127 (w component) */
	"andps _SIMDx86_float_SSE_NO_W_MASK, %%xmm2\n"

	/* save xmm4 = 0 | z | y | x */
	"movaps %%xmm2, %%xmm4\n"

	/* Multiply with point 'a' on the polygon (saved in xmm7): xmm2 = 0 | a.z*z | a.y*y | a.x*x */
	"mulps %%xmm7, %%xmm2\n"

	#if USE_SSE >= 3

	/* horizontally add, xmm2 = x^2+y^2+z^2 | x^2+y^2+z^2 | x^2+y^2+z^2 | x^2+y^2+z^2  */
	"haddps %%xmm2, %%xmm2\n"
	"haddps %%xmm2, %%xmm2\n"

	/* change sign for top component, remove bits for others */
	"xorps _SIMDx86_float_POSPOSPOSNEG, %%xmm2\n"		/* xmm2 = -(x^2+y^2+z^2) | .... | ...*/
	"andps _SIMDx86_float_SSE_NO_XYZ_MASK, %%xmm2\n"		/* xmm2 = -(x^2+y^2+z^2) | 0 | 0 | 0 */
	"orps %%xmm2, %%xmm4\n"							/* xmm4 = -(x^2+y^2+z^2) | z | y | x */

	#else

	"movhlps %%xmm2, %%xmm3\n"		/* xmm3 = ?   | ?   | 0   |  z^2 */
	"addss %%xmm2, %%xmm3\n"		/* xmm3 = ?   | ?   | 0   | z^2 + x^2 */
	"shufps $0x55, %%xmm2, %%xmm2\n"/* xmm2 = y^2 | y^2 | y^2 | y^2 */
	"addss %%xmm2, %%xmm3\n"		/* xmm3 = ?   | ?   | ?   | x^2+y^2+z^2 */

	/* Change sign */
	"xorps _SIMDx86_float_NEGPOSPOSPOS, %%xmm3\n" /* xmm3 = ? | ? | ? | -(x^2+y^2+z^2)*/

	/* Move to w component location, mask off xyz, and OR with saved portions */
	"shufps $0x00, %%xmm3, %%xmm3\n"				/* xmm3 = -(x^2+y^2+z^2) | -(x^2+y^2+z^2) | -(x^2+y^2+z^2) | -(x^2+y^2+z^2)*/
	"andps _SIMDx86_float_SSE_NO_XYZ_MASK, %%xmm3\n"/* xmm3 = -(x^2+y^2+z^2) | 0 | 0 | 0 */
	"orps %%xmm3, %%xmm4\n"							/* xmm4 = -(x^2+y^2+z^2) | z | y | x */

	#endif /* Not using SSE3 */

	/* Save plane coefficients */
	"movups %%xmm4, (%3)\n"
	:
	: "r" (pA), "r" (pB), "r" (pC), "r" (pOut)
	);


	#else
	SIMDx86Vector v0, v1, cross;

	SIMDx86Vector_DiffOf(&v0, pA, pB);
	SIMDx86Vector_DiffOf(&v1, pC, pB);


	SIMDx86Vector_CrossOf(&cross, &v0, &v1);
	/*
			Calculate d...
			1) ax + by + cz + d = 0
			2) ax + by + cz = -d
			3) -(ax+by+cz) = d
			-dot(p,v) = d
	*/

	pOut->a = cross.x;
	pOut->b = cross.y;
	pOut->c = cross.z;

	/* Solve for d with scalar product */
	pOut->d = -(SIMDx86Vector_Dot(&cross, pA));
	#endif
}

float SIMDx86Plane_DistToPoint(const SIMDx86Plane* pPlane, const SIMDx86Vector* pPoint)
{
	#ifdef USE_SSE
	float dummy;
	asm(
	"movups (%1), %%xmm0\n" /* xmm0 = pPlane->d | pPlane->c | pPlane->b | pPlane->a */
	"movups (%2), %%xmm1\n" /* xmm1 = ????????? | pPoint->z | pPoint->y | pPoint->x */
	
	"andps SIMDx86_float_SSE_NO_W_MASK, %%xmm1\n"   /* xmm1 = 0 | ... */
	"movaps %%xmm0, %%xmm7\n"						/* xmm7 = pPlane... */

	"mulps %%xmm0, %%xmm1\n"                        /* xmm1 = d*0.0 | c*z | b*y | a*x */
	"shufps $0xFF, %%xmm7, %%xmm7\n"				/* xmm7 = d | d | d | d */
	
	#if USE_SSE >= 3
	"haddps %%xmm1, %%xmm1\n"				/* xmm1 = ... | ... | z*c + 0 | x*a + y*b */
	"haddps %%xmm1, %%xmm1\n"       		/* xmm1 = ... | ... | dot(pPlane, pPoint) */
	"andps _SIMDx86_float_ABS, %%xmm1\n"	/* xmm1 = ??? | ??? | ??? | fabsf(dot(pPlane, pPoint)) */
	"addss %%xmm7, %%xmm1\n"				/* xmm1 = ? | ? | ? | fabsf(dot(pPlane, pPoint)) + pPlane->d */
	#else
    "movhlps %%xmm1, %%xmm2\n"      /* xmm2 = ???? | ???? | d*0.0 | z*c */
	"addss %%xmm1, %%xmm2\n"        /* xmm2 = ???? | ???? | ????  | x*a + z*c*/
	"shufps $x55, %%xmm1, %%xmm1\n" /* xmm1 = ???? | ???? | ????  | y*b */
	"andps _SIMDx86_float_ABS, %%xmm1\n"	/* xmm1 = ??? | ??? | ??? | fabsf(dot(pPlane, pPoint)) */
	"addss %%xmm2, %%xmm1\n"        /* xmm1 = ???? | ???? | ????? |  fabsf(dot(pPlane, pPoint)) + pPlane->d */
	#endif
	"movss %%xmm1, -4(%%esp)\n"
	"flds -4(%%esp)\n"

	: "=t" (dummy)
	: "r" (pPlane), "r" (pPoint)
	);
	#else
	return fabsf((pPlane->a*pPoint->x) + (pPlane->b*pPoint->y) + (pPlane->c*pPoint->z) + pPlane->d);
	#endif
}

float SIMDx86Plane_DistToSphere(const SIMDx86Plane* pPlane, const SIMDx86Sphere* pSphere)
{
	#ifdef USE_SSE
	float dummy;
	asm(
	"movups (%1), %%xmm0\n" /* xmm0 = pPlane->d | pPlane->c | pPlane->b | pPlane->a */
	"movups (%2), %%xmm1\n" /* xmm1 = ????????? | pSphere->Center.z | pSphere->Center.y | pSphere->Center.x */
	
	"andps SIMDx86_float_SSE_NO_W_MASK, %%xmm1\n"   /* xmm1 = 0 | ... */
	"movaps %%xmm0, %%xmm7\n"						/* xmm7 = pPlane... */

	"mulps %%xmm0, %%xmm1\n"                        /* xmm1 = d*0.0 | c*z | b*y | a*x */
	"shufps $0xFF, %%xmm7, %%xmm7\n"				/* xmm7 = d | d | d | d */
	
	#if USE_SSE >= 3
	"haddps %%xmm1, %%xmm1\n"				/* xmm1 = ... | ... | z*c + 0 | x*a + y*b */
	"haddps %%xmm1, %%xmm1\n"       		/* xmm1 = ... | ... | dot(pPlane, pSphere->Center) */
	"andps _SIMDx86_float_ABS, %%xmm1\n"	/* xmm1 = ??? | ??? | ??? | fabsf(dot(pPlane, pSphere->Center)) */
	"addss %%xmm7, %%xmm1\n"				/* xmm1 = ? | ? | ? | fabsf(dot(pPlane, pSphere->Center) + pPlane->d */
	#else
    "movhlps %%xmm1, %%xmm2\n"      /* xmm2 = ???? | ???? | d*0.0 | z*c */
	"addss %%xmm1, %%xmm2\n"        /* xmm2 = ???? | ???? | ????  | x*a + z*c*/
	"shufps $x55, %%xmm1, %%xmm1\n" /* xmm1 = ???? | ???? | ????  | y*b */
	"andps _SIMDx86_float_ABS, %%xmm1\n"	/* xmm1 = ??? | ??? | ??? | fabsf(dot(pPlane, pSphere->Center)) */
	"addss %%xmm2, %%xmm1\n"        /* xmm1 = ???? | ???? | ????? |  fabsf(dot(pPlane, pSphere->Center)) + pPlane->d */
	#endif

	/*
		C Code:
		if(center_dist > pSphere->radius)
			return center_dist - pSphere->radius;
		else
			return 0.0f;

	    Branchless by:

		x = dist - radius
		return max(0, x)
	*/

	"xorps %%xmm7, %%xmm7\n" /* xmm7 = 0 | 0 | 0 | 0 */
	
	/* Subtract radius */
	"subss 16(%2), %%xmm1\n" /* xmm1 = ? | ? | ? | dist - radius */
	"maxss %%xmm7, %%xmm1\n" /* xmm1 = ? | ? | ? | max(0, dist-radius) */

	/* ugh, stldf (store-to-load forwarding) */
	"movss %%xmm1, -4(%%esp)\n"
	"flds -4(%%esp)\n"

	: "=t" (dummy)
	: "r" (pPlane), "r" (pSphere)
	);
	#else
	float center_dist = SIMDx86Plane_DistToPoint(pPlane, &pSphere->Center);
	/*
		Reasoning:
		If the distance (unsigned) between the center and plane is less than the radius, then they are
		intersecting, thus the distance is zero (rather than negative). If the distance is actually
		greater than the radius, the true distance is the distance to the center minus the radius.

	*/


	if(center_dist > pSphere->radius)
		return center_dist - pSphere->radius;
	else
		return 0.0f;

	#endif
}

float SIMDx86Plane_DistToOrigin(const SIMDx86Plane* pPlane)
{
	/* This is ONLY true for normalized planes, otherwise, d / mag(n)  */
	return pPlane->d;
}

float SIMDx86Plane_Dot(const SIMDx86Plane* pPlane, const SIMDx86Vector* pVec)
{
	return (pPlane->a * pVec->x) + (pPlane->b * pVec->y) + (pPlane->c * pVec->z) + pPlane->d;
}

float SIMDx86Plane_Dot4(const SIMDx86Plane* pPlane, const float* pVec4)
{
	return (pPlane->a * pVec4[0]) + (pPlane->b * pVec4[1]) + (pPlane->c * pVec4[2]) + (pPlane->d * pVec4[3]);
}

float SIMDx86Plane_DotNormal(const SIMDx86Plane* pPlane, const SIMDx86Vector* pVec)
{
	#ifdef USE_SSE
	float dummy;
	asm(
	"movups (%1), %%xmm0\n" /* xmm0 = P->d | P->c | P->b | P->a */
	"movups (%2), %%xmm1\n" /* xmm1 = ?    | V->z | V->b | V->a */
	"andps _SIMDx86_float_SSE_NO_W_MASK, %%xmm0\n" /* 0 | P1.c | P1.b | P1.a */

	"mulps %%xmm1, %%xmm0\n"    /* xmm0 = 0 | P->c*V->z | P->b*V->y | P->a*V->x */

	#if USE_SSE >= 3
		"haddps %%xmm0, %%xmm0\n"
		"haddps %%xmm0, %%xmm0\n"

		"movss %%xmm0, -4(%%esp)\n"
		"flds -4(%%esp)\n"
	#else
		"movhlps %%xmm0, %%xmm1\n"		/* xmm1 = ?   | ?   | 0   |  z's */
		"addss %%xmm0, %%xmm1\n"		/* xmm1 = ?   | ?   | 0   | z's + x's */
		"shufps $0x55, %%xmm0, %%xmm0\n"/* xmm0 = y's | y's | y's | y's */
		"addss %%xmm0, %%xmm1\n"		/* xmm1 = ?   | ?   | ?   | x's+y's+z's */

		"movss %%xmm1, -4(%%esp)\n"
		"flds -4(%%esp)\n"
	#endif

	: "=t" (dummy)
	: "r" (pPlane), "r" (pVec)
	);

	#elif defined(USE_3DNOW)
	float dummy;

	asm(
	"movq  (%1), %%mm0\n"
	"movd 8(%1), %%mm1\n"
	"pfmul  (%2), %%mm0\n"
	"pfmul 8(%2), %%mm1\n"
	"pfadd %%mm0, %%mm1\n"
	"pfacc %%mm1, %%mm1\n"

	"movd %%mm1, -4(%%esp)\n"
	"femms\n"
	"flds -4(%%esp)\n"

	: "=t" (dummy)
	: "r" (pPlane), "r" (pVec)
	);

	return dummy;
	#else
	return (pPlane->a * pVec->x) + (pPlane->b * pVec->y) + (pPlane->c * pVec->z);
	#endif
	
}

float SIMDx86Plane_DotPlane(const SIMDx86Plane* pPlane1, const SIMDx86Plane* pPlane2)
{
	#ifdef USE_SSE
	float dummy;
	asm(
	"movups (%1), %%xmm0\n" /* xmm0 = P1.d | P1.c | P1.b | P1.a */
	"movups (%2), %%xmm1\n" /* xmm1 = P2.d | P2.c | P2.b | P2.a */
	"andps _SIMDx86_float_SSE_NO_W_MASK, %%xmm0\n" /* 0 | P1.c | P1.b | P1.a */
	
	"mulps %%xmm1, %%xmm0\n"    /* xmm0 = 0 | P1.c*P2.c | P1.b*P2.b | P1.a*P2.a */
	
	#if USE_SSE >= 3
	"haddps %%xmm0, %%xmm0\n"
	"haddps %%xmm0, %%xmm0\n"

	"subl $4(%esp)\n"
	"movss %%xmm0, (%%esp)\n"
	"flds (%%esp)\n"
	"addl $4, %%esp\n"
	#else
	"movhlps %%xmm0, %%xmm1\n"		/* xmm1 = ?   | ?   | 0   |  z's */
	"addss %%xmm0, %%xmm1\n"		/* xmm1 = ?   | ?   | 0   | z's + x's */
	"shufps $0x55, %%xmm0, %%xmm0\n"/* xmm0 = y's | y's | y's | y's */
	"addss %%xmm0, %%xmm1\n"		/* xmm1 = ?   | ?   | ?   | x's+y's+z's */

	"movss %%xmm1, -4(%%esp)\n"
	"flds -4(%%esp)\n"
	#endif
	: "=t" (dummy)
	: "r" (pPlane1), "r" (pPlane2)
	);
	
	#elif defined(USE_3DNOW)
	float dummy;
	
	asm(
	"movq  (%1), %%mm0\n"       /* mm0 = P1.y | P1.x */
	"movd 8(%1), %%mm1\n"       /* mm1 = 0    | P1.z */
	"pfmul  (%2), %%mm0\n"      /* mm0 = P1.y*P2.y | P1.x*P2.x */
	"pfmul 8(%2), %%mm1\n"      /* mm1 = 0         | P1.z*P2.z */
	"pfadd %%mm0, %%mm1\n"      /* mm1 = P1.y*P2.y | P1.x*P2.x+P1.z*P2.z */
	"pfacc %%mm1, %%mm1\n"      /* mm1 = ?         | P1.x*P2.x+P1.y*P2.y+P1.z*P2.z */
	
	"movd %%mm1, -4(%%esp)\n"
	"femms\n"
	"flds -4(%%esp)\n"
	
	: "=t" (dummy)
	: "r" (pPlane1), "r" (pPlane2)
	);
	
	return dummy;
	#else
	
	/*
		equation: cos(theta) = dot(P1, P2) / (mag(P1)*mag(p2))

		Thus, the only way the below code works if mag(P1) == mag(P2) == 1.0f
	*/

	return (pPlane1->a*pPlane2->a) + (pPlane1->b*pPlane2->b) + (pPlane1->c*pPlane2->c);
	#endif
}

void SIMDx86Plane_Normalize(SIMDx86Plane* pOut)
{

	float invmag = 1.0f / sqrtf((pOut->a * pOut->a) + (pOut->b * pOut->b) + (pOut->c * pOut->c));

	/* Note that you have to also divide the distance from origin (d) by magnitude of vector as well */
	pOut->a *= invmag;
	pOut->b *= invmag;
	pOut->c *= invmag;
	pOut->d *= invmag;
}

void SIMDx86Plane_NormalizeOf(SIMDx86Plane* pOut, SIMDx86Plane* pIn)
{
	float invmag = 1.0f / sqrtf((pIn->a * pIn->a) + (pIn->b * pIn->b) + (pIn->c * pIn->c));

	/* Note that you have to also divide the distance from origin (d) by magnitude of vector as well */
	pOut->a = pIn->a * invmag;
	pOut->b = pIn->b * invmag;
	pOut->c = pIn->c * invmag;
	pOut->d = pIn->d * invmag;
}

SIMDx86Vector* SIMDx86Plane_IntersectLineSegment(const SIMDx86Plane* pPlane, const SIMDx86Vector* pStart, const SIMDx86Vector* pEnd, SIMDx86Vector* pIntersectionPoint)
{

	float Denominator;
	float SegScalar;
	
	SIMDx86Vector diff;

	/* diff = pEnd - pStart */
	SIMDx86Vector_DiffOf(&diff, pEnd, pStart);

	Denominator = SIMDx86Plane_DotNormal(pPlane, &diff);

	/*
		If the plane's normal and line are perpendicular, then they never intersect. This
		is because the normal of a plane is perpendicular to the actual plane, thus, the
		plane is parallel to the line. I'm not sure this handles line ON the plane cases
		though.
	*/
	if(Denominator == 0.0f)
	    return NULL;

	SegScalar = (pPlane->d - SIMDx86Plane_DotNormal(pPlane, pStart)) / Denominator;

	SIMDx86Vector_ScaleOf(pIntersectionPoint, &diff, SegScalar);
	SIMDx86Vector_Sum(pIntersectionPoint, pStart);
	return pIntersectionPoint;
}
