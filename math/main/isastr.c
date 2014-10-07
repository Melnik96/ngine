/*
	main/isastr.c -- ISA String names
	Written by Patrick Baggett, 2006 (baggett.patrick@gmail.com)
	Under LGPL License
	Part of SIMDx86 Project
*/

#define SIMDX86_LEAN /* Improve compile time by not including *all* of SIMDx86 into this file */

#include <SIMDx86/SIMDx86.h>

static const char* ISAs[SIMDX86ISA_MAX] =
{
	"Generic Native Instruction Set",	/* SIMDX86ISA_USE_GENERIC */
	"Intel MMX",						/* SIMDX86ISA_USE_MMX */
	"Cyrix EMMX",						/* SIMDX86ISA_USE_EMMX */
	"AMD 3DNow!",                       /* SIMDX86ISA_USE_3DNOW */
	"AMD 3DNow! Plus",					/* SIMDX86ISA_USE_3DNOWPLUS */
	"Intel SSE",						/* SIMDX86ISA_USE_SSE */
	"Intel SSE2",						/* SIMDX86ISA_USE_SSE2 */
	"Intel SSE3",						/* SIMDX86ISA_USE_SSE3 */
	"Intel SSSE3",						/* SIMDX86ISA_USE_SSSE3*/
	"Intel SSE4",						/* SIMDX86ISA_USE_SSE4 */
	"PowerPC AltiVec/VMX",					/* SIMDX86ISA_USE_ALTIVEC */
	"Optimal Instruction Set"			/* SIMDX86ISA_USE_BEST */
};

const char* SIMDx86_GetISAString(unsigned int ISA)
{

#ifdef DEBUG
	if(ISA >= SIMDX86ISA_MAX)
		return "(null ISA -> check function input value)"
#endif

	return ISAs[ISA];
}
