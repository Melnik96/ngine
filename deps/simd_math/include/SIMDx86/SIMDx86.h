/*
	SIMDx86.h -- Main include for SIMDx86
	Written by Patrick Baggett, 2005 (baggett.patrick@gmail.com)
	Under LGPL License
	Part of SIMDx86 Project
*/

#ifndef _SIMDX86_SIMDX86_H
#define _SIMDX86_SIMDX86_H

#if !defined(SIMDX86_LEAN)	/* Do not implicitly include anything */

#include <SIMDx86/align.h> /* ALIGNED keyword */
#include <SIMDx86/consts.h> /* Constants */
#include <SIMDx86/image.h> /* Image routines */
#include <SIMDx86/math.h> /* Math routines */
#include <SIMDx86/matrix.h> /* Matrix routines */
#include <SIMDx86/plane.h> /* Plane routines */
#include <SIMDx86/polygon.h> /* Polygon (rather, traingle) routines */
#include <SIMDx86/quaternion.h> /* Quaternion routines */
#include <SIMDx86/sphere.h> /* Sphere routines */
#include <SIMDx86/vector.h> /* Vector routines */
#include <SIMDx86/version.h>

#if defined(__i386__)
#  if defined(__GNUC__)
	#define SIMDx86_emms()	asm("\t emms\n")
	#define SIMDx86_femms() asm("\t femms\n")
#  elif defined(_MSC_VER)
	#define SIMDx86_emms()	__asm { emms }
	#define SIMDx86_femms()	__asm { femms }
#  else
	/* Cannot determine which compiler, so just using out-of-line versions, defined in emms.asm */
	void SIMDx86_emms();
	void SIMDx86_femms();
#  endif
#endif

#endif

/* Code size constants. If you change these, you MUST change SIMDx86asm.inc */
#define OVERLAY_SIZE_SMALL		32
#define OVERLAY_SIZE_MEDIUM		128
#define OVERLAY_SIZE_LARGE		512
#define OVERLAY_SIZE_HUGE		1024


/*
	Definitions of SIMDx86's ISA (Instruct Set Architecture, e.g. MMX, SSE)

	NOTE: If you change these enum values, update SIMDx86asm.inc to reflect that!
*/
typedef enum SIMDx86ISA
{
	SIMDX86ISA_USE_GENERIC,		/* Use native (unaccelerated) ISA (i.e. vanilla C code) */
	SIMDX86ISA_USE_MMX,			/* Use Intel MMX instruction set (Formerly -DUSE_MMX=1) */
	SIMDX86ISA_USE_EMMX,		/* Use Cyrix eMMX instruction set (New in version 0.5) */
	SIMDX86ISA_USE_3DNOW,		/* Use AMD 3DNow! instruction set (Fomerly -DUSE_3DNOW=1) */
	SIMDX86ISA_USE_3DNOWPLUS,	/* Use AMD 3DNow!+/MMX+ instruction set (Fomerly -DUSE_3DNOW=2) */
	SIMDX86ISA_USE_SSE,			/* Use Intel SSE instruction set (Fomerly -DUSE_SSE=1) */
	SIMDX86ISA_USE_SSE2,		/* Use Intel SSE2 instruction set (Fomerly -DUSE_SSE=2) */
	SIMDX86ISA_USE_SSE3,		/* Use Intel SSE3 instruction set (Fomerly -DUSE_SSE=3) */
	SIMDX86ISA_USE_SSSE3,		/* Use Intel SSSE3 instruction set (Fomerly -DUSE_SSE=3.5) */
	SIMDX86ISA_USE_SSE4,		/* Use Intel SSE4 instruction set (Unused currently, for Intel NNI) */
	SIMDX86ISA_USE_ALTIVEC, 	/* Use PowerPC AltiVec/VMX instruction set */
	SIMDX86ISA_USE_BEST,		/* Read CPU info, determine best */
	SIMDX86ISA_MAX				/* Invalid ISA, used for determining enumeration max value */
} SIMDx86ISA;

#define SIMDX86ISA_BIT( isa )			(1 << (isa))
#define SIMDX86ISA_ISSUPPORTED( mask, isa)	( (mask) & (1 << (isa)) )


/* Flags for SIMDx86 initialization. See notes */
#define SIMDX86FLAGS_HIPREC		0x01		/* Use highest precision possible (Formerly -DHIPREC) */
#define SIMDX86FLAGS_NOEMMS		0x02		/* Do not execute (F)EMMS after MMX/3DNow! code block (Formerly -DNO_EMMS) */
#define SIMDX86FLAGS_OPTAMD		0x04		/* Optimize code for AMD processors rather than Intel (See notes) */
#define SIMDx86FLAGS_OPTINTEL	0x08		/* Optimize code for Intel processors rather than AMD (See notes) */

/*
	Note: SIMDx86 automatically picks the optimal code path at runtime, however you may override its decision by OR'ing
	one of these flags in. This can be useful for debugging a program that works fine on an AMD processor yet fails under
	and Intel processor, and you think it might be due to SIMDx86. SIMDx86 refuses to initialize when both SIMDX86FLAGS_OPTAMD
	and SIMDX86FLAGS_OPTINTEL flags are specified, as they are mutally exclusive.
*/

/*
	Initialize SIMDx86 with an ISA. Returns member of SIMDx86ISA enumeration representing the selected ISA if success, or negative value
	representing failure.
*/
int SIMDx86_Initialize(unsigned int WhichISA, unsigned int Flags);

/*
	SIMDx86_GetCPUSupportedISA()
	Returns a bitmask (bitwise OR) of supported ISAs. If the ISA is supported, then the bit is set. The SIMDX86ISA_GENERIC
	ISA is always supported, so this value is never zero. So, if your processor supports MMX, the value of this would be
	
	SIMDX86ISA_BIT(SIMDX86ISA_USE_GENERIC) | SIMDX86ISA_BIT(SIMDX86ISA_USE_MMX)

	To test for MMX, you would do:

	unsigned int ISAs = SIMDx86_GetCPUSupportedISA();

	if(SIMDX86ISA_ISSUPPORTED(ISAs, SIMDX86ISA_USE_MMX))
	{
		MMX Supported
	}
	else
	{
		MMX *Not* Supported
	}

*/
unsigned int SIMDx86_GetCPUSupportedISA();
const char* SIMDx86_GetISAString(unsigned int ISA);

#endif
