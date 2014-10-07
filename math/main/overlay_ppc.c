/*
	overlay_x86.c -- Code overlaying for x86-based systems
	Written by Patrick Baggett, 2006 (baggett.patrick@gmail.com)
	Under LGPL License
	Part of SIMDx86 Project
*/

#include <SIMDx86/SIMDx86.h>
#include <memory.h>

/* This would be quite tedious... */
#define OVERLAY( funcname, simdname) \
{	\
	extern void simdname(); /* Fake function prototype */ \
	extern unsigned int size_ ## simdname; \
	SIMDx86Code_MakeReadWriteExec( funcname, size_ ##simdname); \
	memcpy( funcname, simdname, size_ ## simdname); \
	SIMDx86Code_MakeReadExec( funcname, size_ ## simdname); \
	printf("SIMDx86: overlay.c: Overlayed %u code bytes to %s()\n",size_ ## simdname, #simdname, #funcname); \
}

static void OverlayAltiVec(unsigned int Flags);
static void OverlayGeneric(unsigned int Flags);

int SIMDx86_Initialize(unsigned int WhichISA, unsigned int Flags)
{
	unsigned int ISAs = SIMDx86_GetCPUSupportedISA();	

	/* Are we supposed to pick? */
	if(WhichISA == SIMDX86ISA_USE_BEST)
	{
		if(SIMDX86ISA_ISSUPPORTED(ISAs, SIMDX86ISA_USE_ALTIVEC))
			WhichISA = SIMDX86ISA_USE_ALTIVEC;
		else if(SIMDX86ISA_ISSUPPORTED(ISAs, SIMDX86ISA_USE_GENERIC))
			WhichISA = SIMDX86ISA_USE_GENERIC;

	}
	else /* We aren't picking, the ISA was given to us */
	{
		#ifdef DEBUG /* Some extra debug checks for sanity */

		/* Is this a valid ISA identifier? */
		if(WhichISA >= SIMDX86ISA_MAX)
		{
			printf("SIMDx86: overlay.c: SIMDx86_Initialize() -- ISA %d isn't a valid ISA identifier, range is [0,%d]\n", WhichISA, SIMDX86ISA_MAX-1);
			return -1;
		}

		/* Is the ISA supported by the CPU? */
		if(SIMDX86ISA_ISSUPPORTED(ISAs, WhichISA) == 0)
		{
			printf("SIMDx86: overlay.c: SIMDx86_Initialize() -- ISA \"%s\" isn't supported by the CPU!\n", SIMDx86_GetISAString(WhichISA));
			return -1;
		}		
		#endif

		/* In release mode, there are no seatbelts here! */

	}

	switch(WhichISA)
	{
		case SIMDX86ISA_USE_ALTIVEC:
			OverlayAltivec(Flags);
		case SIMDX86ISA_USE_GENERIC:
			OverlayGeneric(Flags);
	}

	return WhichISA;
}

static void OverlayAltiVec(unsigned int Flags)
{
	/* math */
	OVERLAY(SIMDx86_sqrt, SIMDx86_sqrt_387);		/* Cannot use double-precision values until SSE2 */
	OVERLAY(SIMDx86_rsqrt, SIMDx86_rsqrt_387);		/* Cannot use double-precision values until SSE2 */

	if(Flags & SIMDX86FLAGS_HIPREC)
	{
		OVERLAY(SIMDx86_sqrtf, SIMDx86_sqrtf_HIPREC_AltiVec);
		OVERLAY(SIMDx86_rsqrtf, SIMDx86_rsqrtf_HIPREC_AltiVec);
	}
	else
	{
		OVERLAY(SIMDx86_sqrtf, SIMDx86_sqrtf_AltiVec);
		OVERLAY(SIMDx86_rsqrtf, SIMDx86_rsqrtf_AltiVec);
	}

	/* polygon */
	OVERLAY(SIMDx86Polygon_PlaneNormal, SIMDx86Polygon_PlaneNormal_AltiVec);

	/* vector */
	OVERLAY(SIMDx86Vector_Sum,		SIMDx86Vector_Sum_AltiVec);
	OVERLAY(SIMDx86Vector_SumOf,		SIMDx86Vector_SumOf_AltiVec);
	OVERLAY(SIMDx86Vector_Diff,		SIMDx86Vector_Diff_AltiVec);
	OVERLAY(SIMDx86Vector_DiffOf,		SIMDx86Vector_DiffOf_AltiVec);
	OVERLAY(SIMDx86Vector_Scale,		SIMDx86Vector_Scale_AltiVec);
	OVERLAY(SIMDx86Vector_ScaleOf,		SIMDx86Vector_ScaleOf_AltiVec);
	OVERLAY(SIMDx86Vector_Dot,		SIMDx86Vector_Dot_AltiVec);
	OVERLAY(SIMDx86Vector_Dot4,		SIMDx86Vector_Dot4_AltiVec);
	OVERLAY(SIMDx86Vector_LengthSq,		SIMDx86Vector_LengthSq_AltiVec);
	OVERLAY(SIMDx86Vector_Cross,		SIMDx86Vector_Cross_AltiVec);
	OVERLAY(SIMDx86Vector_CrossOf,		SIMDx86Vector_CrossOf_AltiVec);

	if(Flags & SIMDX86FLAGS_HIPREC)
	{
		/* High Precision Vector Functions */
		OVERLAY(SIMDx86Vector_Length,	SIMDx86Vector_Length_HIPREC_AltiVec);
		OVERLAY(SIMDx86Vector_Normalize, SIMDx86Vector_Normalize_HIPREC_AltiVec);
		OVERLAY(SIMDx86Vector_NormalizeOf, SIMDx86Vector_NormalizeOf_HIPREC_AltiVec);
		OVERLAY(SIMDx86Vector_Distance, SIMDx86Vector_Distance_HIPREC_AltiVec);
	}
	else
	{
		/* Low Precision Vector Functions */
		OVERLAY(SIMDx86Vector_Length,		SIMDx86Vector_Length_AltiVec);
		OVERLAY(SIMDx86Vector_Normalize,	SIMDx86Vector_Normalize_AltiVec);
		OVERLAY(SIMDx86Vector_NormalizeOf,	SIMDx86Vector_NormalizeOf_AltiVec);
		OVERLAY(SIMDx86Vector_Distance,		SIMDx86Vector_Distance_AltiVec);
	}

	/* matrix */
	OVERLAY(SIMDx86Matrix_Sum, SIMDx86Matrix_Sum_AltiVec);
	OVERLAY(SIMDx86Matrix_SumOf, SIMDx86Matrix_SumOf_AltiVec);
	OVERLAY(SIMDx86Matrix_Diff, SIMDx86Matrix_Diff_AltiVec);
	OVERLAY(SIMDx86Matrix_DiffOf, SIMDx86Matrix_DiffOf_AltiVec);
	OVERLAY(SIMDx86Matrix_Scale, SIMDx86Matrix_Scale_AltiVec);
}

static void OverlayGeneric(unsigned int Flags)
{
	OVERLAY(SIMDx86_sqrt, SIMDx86_sqrt_387);
	OVERLAY(SIMDx86_rsqrt, SIMDx86_rsqrt_387);
	OVERLAY(SIMDx86_sqrtf, SIMDx86_sqrtf_387);
	OVERLAY(SIMDx86_rsqrtf, SIMDx86_rsqrtf_387);
}

