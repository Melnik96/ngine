/*
	main/getisa.c -- Generic implementation of GetCPUSupportedISA()
	Written by Patrick Baggett, 2006 (baggett.patrick@gmail.com)
	Under LGPL License
	Part of SIMDx86 Project
*/

#define SIMDX86_LEAN	/* Don't include *all* of SIMDx86 */
#include <SIMDx86/SIMDx86.h>

unsigned int SIMDx86_GetCPUSupportedISA()
{
	/* If this is source file is begin used, then no architecture-specific implementation exists, so just return 'native' */
	return SIMDX86ISA_BIT(SIMDX86ISA_USE_GENERIC);
}
