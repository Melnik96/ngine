/*
	align.h -- Defines ALIGNED for SIMDx86 structures to be aligned.
	Written by Patrick Baggett, 2006 (baggett.patrick@gmail.com) and Carl Skeps, 2006 (carl.skeps@gmail.com)
	Under LGPL License
	Part of SIMDx86 Project
*/

#ifndef _SIMDX86_ALIGNED_H
#define _SIMDX86_ALGINED_H

/* Have these already been defined via command line? */
#if !defined(ALIGNMENT_PREFIX) || !defined(ALIGNMENT_SUFFIX)

	
	#if defined( _MSC_VER ) /* Microsoft Visual C++ */
	
		#define ALIGNMENT_PREFIX __declspec(  align(16)  )
		#define ALIGNMENT_SUFFIX
	
	
	#elif defined( __GNUC__ ) || defined(__SUNPRO_C) /* GNU C Compiler, Sun C compiler (12 and later) */
	
		#define ALIGNMENT_PREFIX
		#define ALIGNMENT_SUFFIX __attribute__((aligned(16)))
		
	#else
	
		#error Unrecognized compiler, please identify your compiler in include/SIMDx86/align.h and send the changes, or define at compile time via command line.

	#endif

#endif

/* Need definition of size_t */
#include <malloc.h>

#ifdef __cplusplus
extern "C" {
#endif

void SIMDx86_SetMallocHook(void* (*MallocFuncPtr)(size_t), void (*FreeFuncPtr)(void*));
void* SIMDx86_AlignedMalloc(size_t BlockSize, unsigned char Alignment);
void SIMDx86_AlignedFree(void* Address);

#ifdef __cplusplus
}
#endif

	
#endif

