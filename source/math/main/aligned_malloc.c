/*
	aligned_malloc.c -- Allocation of aligned memory blocks.
	Written by Patrick Baggett, 2007 (baggett.patrick@gmail.com)
	Under LGPL License
	Part of SIMDx86 Project
*/
#include <malloc.h>

/* malloc()/free() hooks, defaulting to... malloc() and free() */
static void* (*MyMalloc)(size_t) = malloc;
static void (*MyFree)(void*) = free;

void SIMDx86_SetMallocHook(void* (*MallocFuncPtr)(size_t), void (*FreeFuncPtr)(void*))
{
	MyMalloc = MallocFuncPtr;
	MyFree = FreeFuncPtr;
}

void* SIMDx86_AlignedMalloc(size_t BlockSize, unsigned char Alignment)
{
	/*
		Using unsigned longs here such that 64-bit pointers will be held in LP64 model as well as ILP32 model.
		We have a lot of bit manipulations to do, so it gets really annoying to do a lot of casting. Keep these
		as integers until we really need C to think we have a pointer.
		C compilers still complain about that kind of typecast as "pointer truncation"... whatever.
	*/
	unsigned long MallocAddress;
	unsigned long AlignmentMask; 
	unsigned long AlignedAddress;
	unsigned char Delta;
	unsigned char* pData;

	/* Cannot align to zeroth byte */
	if(Alignment == 0)
		return (void*)0;

	/*
		Cannot align to a non-power of two.
		-> We check this by taking the value and subtracting 1 to create a bitmask, then
		AND'ing with the original value. Since the original value should not have but
		a single bit set (it is a power of two right?), and that bit is at a higher
		order than all of the others, the AND should give zero.
	*/
	if((Alignment - 0x01) & Alignment)
		return (void*)0;

	/* Create a bitmask that when AND'ed with an address strips the lower bits to make it aligned */
	AlignmentMask = ~(Alignment-1);

	/* Actually allocate the block */
	MallocAddress = (unsigned long)MyMalloc(BlockSize + (size_t)Alignment);
	
	/* Well, can't do a thing unless we actually can get memory */
	if(MallocAddress == 0)
		return (void*)0;

	/* Align the address somewhere within the extra buffer space that we asked for with malloc() */
	AlignedAddress = (MallocAddress+Alignment-1) & AlignmentMask;

	/* Check if it was already aligned */
	if(AlignedAddress == MallocAddress)
	{
		/*
			OK, this a small problem because now aligned_free() expects these addresses to have data behind them
			saying how far back the original pointer is. We can't move back a single byte, so the answer is to 
			use that extra slack space from malloc() to move the pointer up. This won't unalign it either because
			we will move up "Alignment" bytes.
		*/
		
		AlignedAddress += Alignment;
	}
	
	/* Compute how many bytes we moved from the original block */
	Delta = (unsigned char)(AlignedAddress - MallocAddress);

	/* Get pointer that is one byte before the displayed block */
	pData = (unsigned char*)(AlignedAddress-1);

	/* Store # of bytes moved so that we can move back when we need to free() the data */
	*pData = Delta;

	return (void*)AlignedAddress;
}

void SIMDx86_AlignedFree(void* pAlignedAddress)
{
	unsigned char* pData;

	if(pAlignedAddress == (void*)0)
		return;
	
	pData = (unsigned char*)pAlignedAddress;

	MyFree(pData - pData[-1]);
}
