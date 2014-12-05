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




static void Fixup3DNowFEMMS(void* pCodeSegment, unsigned int CodeSegmentSize);
static void OverlaySSE4(unsigned int Flags);
static void OverlaySSSE3(unsigned int Flags);
static void OverlaySSE3(unsigned int Flags);
static void OverlaySSE2(unsigned int Flags);
static void OverlaySSE(unsigned int Flags);
static void Overlay3DNowPlus(unsigned int Flags);
static void Overlay3DNow(unsigned int Flags);
static void OverlayEMMX(unsigned int Flags);
static void OverlayMMX(unsigned int Flags);
static void OverlayGeneric(unsigned int Flags);

int SIMDx86_Initialize(unsigned int WhichISA, unsigned int Flags)
{
	unsigned int ISAs = SIMDx86_GetCPUSupportedISA();	

	/* Are we supposed to pick? */
	if(WhichISA == SIMDX86ISA_USE_BEST)
	{
		if(SIMDX86ISA_ISSUPPORTED(ISAs, SIMDX86ISA_USE_SSE4))
			WhichISA = SIMDX86ISA_USE_SSE4;
		else if(SIMDX86ISA_ISSUPPORTED(ISAs, SIMDX86ISA_USE_SSSE3))
			WhichISA = SIMDX86ISA_USE_SSSE3;
		else if(SIMDX86ISA_ISSUPPORTED(ISAs, SIMDX86ISA_USE_SSE3))
			WhichISA = SIMDX86ISA_USE_SSE3;
		else if(SIMDX86ISA_ISSUPPORTED(ISAs, SIMDX86ISA_USE_SSE2))
			WhichISA = SIMDX86ISA_USE_SSE2;
		else if(SIMDX86ISA_ISSUPPORTED(ISAs, SIMDX86ISA_USE_SSE))
			WhichISA = SIMDX86ISA_USE_SSE;
		else if(SIMDX86ISA_ISSUPPORTED(ISAs, SIMDX86ISA_USE_3DNOWPLUS))
			WhichISA = SIMDX86ISA_USE_3DNOWPLUS;
		else if(SIMDX86ISA_ISSUPPORTED(ISAs, SIMDX86ISA_USE_3DNOW))
			WhichISA = SIMDX86ISA_USE_3DNOW;
		else if(SIMDX86ISA_ISSUPPORTED(ISAs, SIMDX86ISA_USE_EMMX))
			WhichISA = SIMDX86ISA_USE_EMMX;
		else if(SIMDX86ISA_ISSUPPORTED(ISAs, SIMDX86ISA_USE_MMX))
			WhichISA = SIMDX86ISA_USE_MMX;
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


	/* Check if AMDOPT and INTELOPT flags were set together (they are mutually exclusive) */
	if((Flags & (SIMDX86FLAGS_OPTAMD | SIMDx86FLAGS_OPTINTEL)) == (SIMDX86FLAGS_OPTAMD | SIMDx86FLAGS_OPTINTEL))
	{
		#ifdef DEBUG /* Debug build displays a reason this function is failing */
		printf("SIMDx86: overlay.c: SIMDx86_Initialize() -- OPTAMD and OPTINTEL flags were both set -- they are mutually exclusive\n");
		#endif
		return -1;
	}

	switch(WhichISA)
	{
		case SIMDX86ISA_USE_SSE4:
			OverlaySSE4(Flags);
		case SIMDX86ISA_USE_SSSE3:
			OverlaySSSE3(Flags);
		case SIMDX86ISA_USE_SSE3:
			OverlaySSE3(Flags);
		case SIMDX86ISA_USE_SSE2:
			OverlaySSE2(Flags);
		case SIMDX86ISA_USE_SSE:
			OverlaySSE(Flags);
		case SIMDX86ISA_USE_3DNOWPLUS:
			Overlay3DNowPlus(Flags);
		case SIMDX86ISA_USE_3DNOW:
			Overlay3DNow(Flags);
		case SIMDX86ISA_USE_EMMX:
			OverlayEMMX(Flags);
		case SIMDX86ISA_USE_MMX:
			OverlayMMX(Flags);
		case SIMDX86ISA_USE_GENERIC:
			OverlayGeneric(Flags);
	}

	return WhichISA;
}

static void OverlaySSE4(unsigned int Flags)
{
	OVERLAY(SIMDx86Polygon_PlaneNormal, SIMDx86Polygon_PlaneNormal_SSE);
}

static void OverlaySSSE3(unsigned int Flags)
{
	OVERLAY(SIMDx86Polygon_PlaneNormal, SIMDx86Polygon_PlaneNormal_SSE);
}

static void OverlaySSE3(unsigned int Flags)
{
	OVERLAY(SIMDx86Polygon_PlaneNormal, SIMDx86Polygon_PlaneNormal_SSE);
}

static void OverlaySSE2(unsigned int Flags)
{
	OverlaySSE(Flags);
}

static void OverlaySSE(unsigned int Flags)
{
	/* math */
	OVERLAY(SIMDx86_sqrt, SIMDx86_sqrt_387);		/* Cannot use double-precision values until SSE2 */
	OVERLAY(SIMDx86_rsqrt, SIMDx86_rsqrt_387);		/* Cannot use double-precision values until SSE2 */

	if(Flags & SIMDX86FLAGS_HIPREC)
	{
		OVERLAY(SIMDx86_sqrtf, SIMDx86_sqrtf_HIPREC_SSE);
		OVERLAY(SIMDx86_rsqrtf, SIMDx86_rsqrtf_HIPREC_SSE);
	}
	else
	{
		OVERLAY(SIMDx86_sqrtf, SIMDx86_sqrtf_SSE);
		OVERLAY(SIMDx86_rsqrtf, SIMDx86_rsqrtf_SSE);
	}

	/* polygon */
	OVERLAY(SIMDx86Polygon_PlaneNormal, SIMDx86Polygon_PlaneNormal_SSE);

	/* vector */
	OVERLAY(SIMDx86Vector_Sum,			SIMDx86Vector_Sum_SSE);
	OVERLAY(SIMDx86Vector_SumOf,		SIMDx86Vector_SumOf_SSE);
	OVERLAY(SIMDx86Vector_Diff,			SIMDx86Vector_Diff_SSE);
	OVERLAY(SIMDx86Vector_DiffOf,		SIMDx86Vector_DiffOf_SSE);
	OVERLAY(SIMDx86Vector_Scale,		SIMDx86Vector_Scale_SSE);
	OVERLAY(SIMDx86Vector_ScaleOf,		SIMDx86Vector_ScaleOf_SSE);
	OVERLAY(SIMDx86Vector_Dot,			SIMDx86Vector_Dot_SSE);
	OVERLAY(SIMDx86Vector_Dot4,			SIMDx86Vector_Dot4_SSE);
	OVERLAY(SIMDx86Vector_LengthSq,		SIMDx86Vector_LengthSq_SSE);
	OVERLAY(SIMDx86Vector_Cross,		SIMDx86Vector_Cross_SSE);
	OVERLAY(SIMDx86Vector_CrossOf,		SIMDx86Vector_CrossOf_SSE);


	if(Flags & SIMDX86FLAGS_HIPREC)
	{
		/* High Precision Vector Functions */
		OVERLAY(SIMDx86Vector_Length,	SIMDx86Vector_Length_HIPREC_SSE);
		OVERLAY(SIMDx86Vector_Normalize, SIMDx86Vector_Normalize_HIPREC_SSE);
		OVERLAY(SIMDx86Vector_NormalizeOf, SIMDx86Vector_NormalizeOf_HIPREC_SSE);
		OVERLAY(SIMDx86Vector_Distance, SIMDx86Vector_Distance_HIPREC_SSE);
	}
	else
	{
		/* Low Precision Vector Functions */
		OVERLAY(SIMDx86Vector_Length,		SIMDx86Vector_Length_SSE);
		OVERLAY(SIMDx86Vector_Normalize,	SIMDx86Vector_Normalize_SSE);
		OVERLAY(SIMDx86Vector_NormalizeOf,	SIMDx86Vector_NormalizeOf_SSE);
		OVERLAY(SIMDx86Vector_Distance,		SIMDx86Vector_Distance_SSE);
	}

	/* matrix */
	OVERLAY(SIMDx86Matrix_Sum, SIMDx86Matrix_Sum_SSE);
	OVERLAY(SIMDx86Matrix_SumOf, SIMDx86Matrix_SumOf_SSE);
	OVERLAY(SIMDx86Matrix_Diff, SIMDx86Matrix_Diff_SSE);
	OVERLAY(SIMDx86Matrix_DiffOf, SIMDx86Matrix_DiffOf_SSE);
	OVERLAY(SIMDx86Matrix_Scale, SIMDx86Matrix_Scale_SSE);
}

static void Overlay3DNowPlus(unsigned int Flags)
{
	Overlay3DNow(Flags);
}

static void Overlay3DNow(unsigned int Flags)
{
	OVERLAY(SIMDx86Vector_Sum,      SIMDx86Vector_Sum_3DNow);
	OVERLAY(SIMDx86Vector_SumOf,    SIMDx86Vector_SumOf_3DNow);
	OVERLAY(SIMDx86Vector_Diff,     SIMDx86Vector_Diff_3DNow);
	OVERLAY(SIMDx86Vector_DiffOf,   SIMDx86Vector_DiffOf_3DNow);
	OVERLAY(SIMDx86Vector_Scale,    SIMDx86Vector_Scale_3DNow);
	OVERLAY(SIMDx86Vector_ScaleOf,  SIMDx86Vector_ScaleOf_3DNow);
	OVERLAY(SIMDx86Vector_Dot,      SIMDx86Vector_Dot_3DNow);
	OVERLAY(SIMDx86Vector_Dot4,     SIMDx86Vector_Dot4_3DNow);
	OVERLAY(SIMDx86Vector_LengthSq, SIMDx86Vector_LengthSq_3DNow);
	OVERLAY(SIMDx86Vector_Cross,    SIMDx86Vector_Cross_3DNow);
	OVERLAY(SIMDx86Vector_CrossOf,  SIMDx86Vector_CrossOf_3DNow);

	if(Flags & SIMDX86FLAGS_HIPREC)
	{
		/* High Precision Vector Functions */
		OVERLAY(SIMDx86Vector_Length,      SIMDx86Vector_Length_HIPREC_3DNow);
		OVERLAY(SIMDx86Vector_Normalize,   SIMDx86Vector_Normalize_HIPREC_3DNow);
		OVERLAY(SIMDx86Vector_NormalizeOf, SIMDx86Vector_NormalizeOf_HIPREC_3DNow);
		OVERLAY(SIMDx86Vector_Distance,    SIMDx86Vector_Distance_HIPREC_3DNow);
	}
	else
	{
		/* Low Precision Vector Functions */
		OVERLAY(SIMDx86Vector_Length,      SIMDx86Vector_Length_3DNow);
		OVERLAY(SIMDx86Vector_Normalize,   SIMDx86Vector_Normalize_3DNow);
		OVERLAY(SIMDx86Vector_NormalizeOf, SIMDx86Vector_NormalizeOf_3DNow);
		OVERLAY(SIMDx86Vector_Distance,    SIMDx86Vector_Distance_3DNow);
	}

	/* matrix */
	OVERLAY(SIMDx86Matrix_Sum, SIMDx86Matrix_Sum_3DNow);
	OVERLAY(SIMDx86Matrix_SumOf, SIMDx86Matrix_SumOf_3DNow);
	OVERLAY(SIMDx86Matrix_Diff, SIMDx86Matrix_Diff_3DNow);
	OVERLAY(SIMDx86Matrix_DiffOf, SIMDx86Matrix_DiffOf_3DNow);
	OVERLAY(SIMDx86Matrix_Scale, SIMDx86Matrix_Scale_3DNow);
}

static void OverlayEMMX(unsigned int Flags)
{
}

static void OverlayMMX(unsigned int Flags)
{
}

static void OverlayGeneric(unsigned int Flags)
{
	OVERLAY(SIMDx86_sqrt, SIMDx86_sqrt_387);
	OVERLAY(SIMDx86_rsqrt, SIMDx86_rsqrt_387);
	OVERLAY(SIMDx86_sqrtf, SIMDx86_sqrtf_387);
	OVERLAY(SIMDx86_rsqrtf, SIMDx86_rsqrtf_387);
}

/*
	All of the 3DNow! functions include an FEMMS/RET combination reguardless of if SIMDX86FLAGS_NOEMMS is set
	This function replaces FEMMS/RET with just a RET/NOP/NOP combination at runtime. Some functions
	require FEMMS because they return a value in the FPU, so those will not be changed.

	FEMMS 0x0F, 0x0E -> RET 0xC9
	RET   0xC9       -> NOP 0x90 (The code shouldn't ever get here, technically...)
	                    NOP 0x90
*/
static void Fixup3DNowFEMMS(void* pCodeSegment, unsigned int CodeSegmentSize)
{
	unsigned char* pCodeBytes = (unsigned char*)pCodeSegment;
	
	/* Debug mode checks the proper sequence of machine code */
	#if defined(DEBUG)
	if(	pCodeBytes[CodeSegmentSize-3] != 0x0F &&	/* FEMMS: 0x0F, 0x0E */
		pCodeBytes[CodeSegmentSize-2] != 0x0E &&
		pCodeBytes[CodeSegmentSize-1] != 0xC9)		/* RET: 0xC9 */
	{
		printf(
			"SIMDx86: overlay.c: Fixup3DNow() -- Did not find 0x0F, 0x0E, 0xC9 sequence (femms/ret). This a bug "
			"in the library itself. Please report it at http://www.sourceforge.net/projects/simdx86\n"
			);
	}
	#endif

	pCodeBytes[CodeSegmentSize-3] = 0xC9;	/* RET: 0xC9 */
	pCodeBytes[CodeSegmentSize-2] = 0x90;	/* NOP: 0x90 -- Shouldn't actually get to here */
	pCodeBytes[CodeSegmentSize-1] = 0x90;	/* NOP: 0x90 */

}
