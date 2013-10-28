/*
	codemod_posix -- Code Modification (POSIX)
	Written by Patrick Baggett, 2006 (baggett.patrick@gmail.com)
	Under LGPL License
	Part of SIMDx86 Project
*/

#include <sys/mman.h> /* Memory management, mprotect() */
#include <unistd.h> /* sysconf() */

/* UNIX systems don't quite have it as easy as VirtualProtect() on Win32 based systems. This takes a bit of thought... */

/*
	Note: We are using "unsigned long" type so that C compilers on 64 bit
	architectures can fit an entire 64 bit pointer into an integer type. On
	32 bit architectures, a long is 32 bits, so this is also enough to hold
	a pointer.
*/

/* Determine beginning page given some (possibly unaligned address) */
void* PageOfAddress(unsigned long addr, unsigned long PageSize)
{
	/*
		Justification:
	
		Suppose page size was 64 byes (0x40)
		The mask would be: 0x40 - 0x01 = 0x3f = 0011|1111 binary

		Suppose the function was at address 0xF300C95F. A page must be a multiple of 0x40 bytes (from the example),
		so that means the lower 6 bits must be zero. Thus we have to mask off the bits to find the page. The lower
		6 bits represent the offset from the base of the page.
	*/
	return (void*)(addr & (~(PageSize-1)));
}

/* Determine the offest in bytes from the beginning of a page */
unsigned long PageOffsetOfAddress(unsigned long addr, unsigned long PageSize)
{
	return addr & (PageSize-1);
}

int SIMDx86Code_MakeReadWriteExec(void* pFunctionAddress, unsigned int NumBytes)
{
	unsigned long PageSize; 
	int ActualNumberOfBytes;

	/* Get page size. sysconf() returns a long, but it is safe as unsigned long, since pages cannot be < 0 */
	PageSize = (unsigned long)sysconf(_SC_PAGE_SIZE); /* Try _SC_PAGESIZE if that constant is undefined... */

	/*
		We cannot just mark the page that this function begins at as writable. Worst case:
		
		     | end of page
		     v
		0x66 || 0xb8 0x02 0x00 0x00 0x00 ... || 0x69 ...
	     ^                                       ^
		 | first byte of function                | final byte of function

		 The function can span across pages (2 or more, though I doubt the "or more" part), so we need add
		 the offset of the function and the length to determine the total # of bytes from the beginning
		 page.
	*/
	ActualNumberOfBytes	= ((unsigned long)NumBytes) + PageOffsetOfAddress((unsigned long)pFunctionAddress, PageSize);

	return mprotect(PageOfAddress((unsigned long)pFunctionAddress, PageSize), (size_t) ActualNumberOfBytes, PROT_WRITE | PROT_READ | PROT_EXEC) == 0;
}

int SIMDx86Code_MakeReadExec(void* pFunctionAddress, unsigned int NumBytes)
{
	unsigned long PageSize; 
	int ActualNumberOfBytes;
	

	PageSize = (unsigned long)sysconf(_SC_PAGE_SIZE); /* Try _SC_PAGESIZE if that constant is undefined... */
	ActualNumberOfBytes	= ((unsigned long)NumBytes) + PageOffsetOfAddress((unsigned long)pFunctionAddress, PageSize);

	return mprotect(PageOfAddress((unsigned long)pFunctionAddress, PageSize), (size_t) ActualNumberOfBytes, PROT_READ | PROT_EXEC) == 0;
}

