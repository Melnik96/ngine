/*
	overlay.c -- Stub functionality for non-native architectures.
	Written by Patrick Baggett, 2007 (baggett.patrick@gmail.com)
	Under LGPL License
	Part of SIMDx86 Project
*/

#include <SIMDx86/SIMDx86.h>
#include <SIMDx86/codemod.h>
#include <memory.h> /* memcpy() */

#define OVERLAY( funcname, simdname) \
{	\
	extern void simdname(); /* Fake function prototype */ \
	extern unsigned int size_ ## simdname; \
	int res; \
	res = SIMDx86Code_MakeReadWriteExec( funcname, size_ ##simdname); \
	if(res==0) { return 0; } \
	memcpy( funcname, simdname, size_ ## simdname); \
}


int SIMDx86_Initialize(unsigned int WhichISA, unsigned int Flags)
{
	/* Check if AMDOPT and INTELOPT flags were set together (they are mutually exclusive) */
	if((Flags & (SIMDX86FLAGS_OPTAMD | SIMDx86FLAGS_OPTINTEL)) == (SIMDX86FLAGS_OPTAMD | SIMDx86FLAGS_OPTINTEL))
	{
		#ifdef DEBUG /* Debug build displays a reason this function is failing */
		printf("SIMDx86: overlay.c: SIMDx86_Initialize() -- OPTAMD and OPTINTEL flags were both set -- they are mutually exclusive\n");
		#endif
		return -1;
	}

	/* Math */
	OVERLAY(SIMDx86_sqrt, SIMDx86_sqrt_C);	
	OVERLAY(SIMDx86_rsqrt, SIMDx86_rsqrt_C);
	OVERLAY(SIMDx86_sqrtf, SIMDx86_sqrtf_C);	
	OVERLAY(SIMDx86_rsqrtf, SIMDx86_rsqrtf_C);

	return SIMDX86ISA_BIT(SIMDX86ISA_USE_GENERIC);
}
