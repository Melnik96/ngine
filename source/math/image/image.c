/*
	image.c -- SIMDx86 Image Library
	Written by Patrick Baggett, 2006 (baggett.patrick@gmail.com)
	Under LGPL License
	Part of SIMDx86 Project
*/

#include <SIMDx86/image.h>

void SIMDx86Image_SaturatedSum(unsigned char* pDest, unsigned char* pSrc, unsigned int NumBytes)
{

#if defined(USE_SSE) && (USE_SSE >= 2)
	/* SSE2 (aka iSSE) Implementation, process 128 bytes/loop (32x32bpp pixels) */
	int i;
	int remainder = NumBytes % 128;
	int value;

	/* Check if NumBytes is cleanly divisble by 128... */
	if(remainder)
	{
		/* Process extra to make a multiple of 128 */
		for(i=0; i<(remainder); i++)
		{
			value = pDest[i] + pSrc[i];
			
			/* Check saturation and adjust if needed */
			if(value > 255)
				value = 255;
			pDest[i] = value;
		}
		/* Increment pointers and decrease total # of bytes */
		pDest += remainder;
		pSrc += remainder;
		NumBytes -= remainder;

	}

	NumBytes >>= 7; /* NumBytes /= 128 */

	/* Mix SSE2 and MMX to do a bunch of processing -- here goes! */
	asm(
	"ImageAdd%=:\n"
	"prefetchnta 128(%1)\n"		/* fetch cache line 1 */
	"prefetchnta 192(%1)\n"		/* fetch cache line 2 */
	"movups   (%0), %%xmm0\n"	/* xmm0 = pDest[ 0..15] */
	"movups 16(%0), %%xmm1\n"	/* xmm1 = pDest[16..31] */
	"movups 32(%0), %%xmm2\n"	/* xmm2 = pDest[32..47] */
	"movups 48(%0), %%xmm3\n"	/* xmm3 = pDest[48..63] */
	"movq  64(%0), %%mm0\n"		/* mm0 = pDest[64..71] */
	"movq  72(%0), %%mm1\n"		/* mm1 = pDest[72..79] */
	"movq  80(%0), %%mm2\n"		/* mm2 = pDest[80..87] */
	"movq  88(%0), %%mm3\n"		/* mm3 = pDest[88..95] */
	"movq  96(%0), %%mm4\n"		/* mm4 = pDest[96..103] */
	"movq 104(%0), %%mm5\n"		/* mm5 = pDest[104..111] */
	"movq 112(%0), %%mm6\n"		/* mm6 = pDest[112..119]*/
	"movq 120(%0), %%mm7\n"		/* mm7 = pDest[120..127]*/
	"movups   (%1), %%xmm4\n"	/* xmm4 = pSrc[ 0..15] */
	"movups 16(%1), %%xmm5\n"	/* xmm5 = pSrc[16..31] */
	"movups 32(%1), %%xmm6\n"	/* xmm6 = pSrc[32..47] */
	"movups 48(%1), %%xmm7\n"	/* xmm7 = pSrc[48..63] */
	"paddusb  64(%1), %%mm0\n"
	"paddusb  72(%1), %%mm1\n"
	"paddusb  80(%1), %%mm2\n"
	"paddusb  88(%1), %%mm3\n"
	"paddusb  96(%1), %%mm4\n"
	"paddusb 104(%1), %%mm5\n"
	"paddusb 112(%1), %%mm6\n"
	"paddusb 120(%1), %%mm7\n"
	"paddusb %%xmm4, %%xmm0\n"
	"paddusb %%xmm5, %%xmm1\n"
	"paddusb %%xmm6, %%xmm2\n"
	"paddusb %%xmm7, %%xmm3\n"
	"movntps %%xmm0,   (%0)\n"
	"movntps %%xmm1, 16(%0)\n"
	"movntps %%xmm2, 32(%0)\n"
	"movntps %%xmm3, 48(%0)\n"
	"movntq %%mm0,  64(%0)\n"
	"movntq %%mm1,  72(%0)\n"
	"movntq %%mm2,  80(%0)\n"
	"movntq %%mm3,  88(%0)\n"
	"movntq %%mm4,  96(%0)\n"
	"movntq %%mm5, 104(%0)\n"
	"movntq %%mm6, 112(%0)\n"
	"movntq %%mm7, 120(%0)\n"
	"addl $128, %1\n"
	"addl $128, %0\n"
	"decl %2\n"
	"cmpl $0, %2\n"
	"jne ImageAdd%=\n"
	"sfence\n"
	:
	: "r" (pDest), "r" (pSrc), "r" (NumBytes)
	);

	#ifndef NO_EMMS
		asm("emms\n");
	#endif

#elif defined(USE_MMX) || defined(USE_3DNOW) || defined(USE_SSE)

	/* MMX Implementation (also for 3DNow, SSE), process 64 bytes/loop (16x32bpp pixels) */
	int i;
	int remainder = NumBytes % 64;
	int value;

	/* Check if NumBytes is cleanly divisble by 64... */
	if(remainder)
	{
		/* Process extra to make a multiple of 64 */
		for(i=0; i<(remainder); i++)
		{
			value = pDest[i] + pSrc[i];
			
			/* Check saturation and adjust if needed */
			if(value > 255)
				value = 255;
			pDest[i] = value;
		}
		/* Increment pointers and decrease total # of bytes */
		pDest += remainder;
		pSrc += remainder;
		NumBytes -= remainder;

	}

	NumBytes >>= 6; /* NumBytes /= 64 */

	asm(
	"ImageAdd%=:\n"
	"movq   (%0), %%mm0\n"
	"movq  8(%0), %%mm1\n"
	"movq 16(%0), %%mm2\n"
	"movq 24(%0), %%mm3\n"
	"movq 32(%0), %%mm4\n"
	"movq 40(%0), %%mm5\n"
	"movq 48(%0), %%mm6\n"
	"movq 56(%0), %%mm7\n"
	"paddusb   (%1), %%mm0\n"
	"paddusb  8(%1), %%mm1\n"
	"paddusb 16(%1), %%mm2\n"
	"paddusb 24(%1), %%mm3\n"
	"paddusb 32(%1), %%mm4\n"
	"paddusb 40(%1), %%mm5\n"
	"paddusb 48(%1), %%mm6\n"
	"paddusb 56(%1), %%mm7\n"
	"movq %%mm0,   (%0)\n"
	"movq %%mm1,  8(%0)\n"
	"movq %%mm2, 16(%0)\n"
	"movq %%mm3, 24(%0)\n"
	"movq %%mm4, 32(%0)\n"
	"movq %%mm5, 40(%0)\n"
	"movq %%mm6, 48(%0)\n"
	"movq %%mm7, 56(%0)\n"
	"addl $64, %1\n"
	"addl $64, %0\n"
	"decl %2\n"
	"cmpl $0, %2\n"
	"jne ImageAdd%=\n"
	:
	: "r" (pDest), "r" (pSrc), "r" (NumBytes)
	);

	#ifndef NO_EMMS
		asm("emms\n");
	#endif

#else

	/* C Implementation */
	register unsigned int i;
	int value;
	for(i=0; i<NumBytes; i++)
	{
			value = pDest[i] + pSrc[i];
			
			/* Check saturation and adjust if needed */
			if(value > 255)
				value = 255;
			pDest[i] = value;
	}


#endif

}

void SIMDx86Image_SaturatedSumOf(unsigned char* pOut, const unsigned char* pSrc1, const unsigned char* pSrc2, unsigned int NumBytes)
{

#if defined(USE_SSE) && (USE_SSE >= 2)
	/* SSE2 (aka iSSE) Implementation, process 128 bytes/loop (32x32bpp pixels) */
	int i;
	int remainder = NumBytes % 128;
	int value;

	/* Check if NumBytes is cleanly divisble by 128... */
	if(remainder)
	{
		/* Process extra to make a multiple of 128 */
		for(i=0; i<remainder; i++)
		{
			value = pSrc1[i] + pSrc2[i];
			
			/* Check saturation and adjust if needed */
			if(value > 255)
				value = 255;
			pOut[i] = value;
		}
		/* Increment pointers and decrease total # of bytes */
		pSrc1 += remainder;
		pSrc2 += remainder;
		pOut += remainder;
		NumBytes -= remainder;

	}

	NumBytes >>= 7; /* NumBytes /= 128 */

	/* Mix SSE2 and MMX to do a bunch of processing -- here goes! */
	asm(
	"ImageAdd%=:\n"
	"prefetchnta 128(%0)\n"
	"prefetchnta 192(%0)\n"
	"prefetchnta 128(%1)\n"
	"prefetchnta 192(%1)\n"
	"movups   (%0), %%xmm0\n"
	"movups 16(%0), %%xmm1\n"
	"movups 32(%0), %%xmm2\n"
	"movups 48(%0), %%xmm3\n"
	"movq  64(%0), %%mm0\n"
	"movq  72(%0), %%mm1\n"
	"movq  80(%0), %%mm2\n"
	"movq  88(%0), %%mm3\n"
	"movq  96(%0), %%mm4\n"
	"movq 104(%0), %%mm5\n"
	"movq 112(%0), %%mm6\n"
	"movq 120(%0), %%mm7\n"
	"movups   (%1), %%xmm4\n"
	"movups 16(%1), %%xmm5\n"
	"movups 32(%1), %%xmm6\n"
	"movups 48(%1), %%xmm7\n"
	"paddusb  64(%1), %%mm0\n"
	"paddusb  72(%1), %%mm1\n"
	"paddusb  80(%1), %%mm2\n"
	"paddusb  88(%1), %%mm3\n"
	"paddusb  96(%1), %%mm4\n"
	"paddusb 104(%1), %%mm5\n"
	"paddusb 112(%1), %%mm6\n"
	"paddusb 120(%1), %%mm7\n"
	"paddusb %%xmm4, %%xmm0\n"
	"paddusb %%xmm5, %%xmm1\n"
	"paddusb %%xmm6, %%xmm2\n"
	"paddusb %%xmm7, %%xmm3\n"
	"movntps %%xmm0,   (%3)\n"
	"movntps %%xmm1, 16(%3)\n"
	"movntps %%xmm2, 32(%3)\n"
	"movntps %%xmm3, 48(%3)\n"
	"movntq %%mm0,  64(%3)\n"
	"movntq %%mm1,  72(%3)\n"
	"movntq %%mm2,  80(%3)\n"
	"movntq %%mm3,  88(%3)\n"
	"movntq %%mm4,  96(%3)\n"
	"movntq %%mm5, 104(%3)\n"
	"movntq %%mm6, 112(%3)\n"
	"movntq %%mm7, 120(%3)\n"
	"addl $128, %1\n"
	"addl $128, %0\n"
	"addl $128, %3\n"
	"decl %2\n"
	"cmpl $0, %2\n"
	"jne ImageAdd%=\n"
	"sfence\n"
	:
	: "r" (pSrc1), "r" (pSrc2), "r" (NumBytes), "r" (pOut)
	);

	#ifndef NO_EMMS
		asm("emms\n");
	#endif

#elif defined(USE_MMX) || defined(USE_3DNOW) || defined(USE_SSE)

	/* MMX Implementation (also for 3DNow, SSE), process 64 bytes/loop (16x32bpp pixels) */
	int i;
	int remainder = NumBytes % 64;
	int value;

	/* Check if NumBytes is cleanly divisble by 64... */
	if(remainder)
	{
		/* Process extra to make a multiple of 64 */
		for(i=0; i<remainder; i++)
		{
			value = pSrc1[i] + pSrc2[i];
			
			/* Check saturation and adjust if needed */
			if(value > 255)
				value = 255;
			pOut[i] = value;
		}
		/* Increment pointers and decrease total # of bytes */
		pSrc1 += remainder;
		pSrc2 += remainder;
		pOut += remainder;
		NumBytes -= remainder;

	}

	NumBytes >>= 6; /* NumBytes /= 64 */

	asm(
	"ImageAdd%=:\n"
#ifdef USE_SSE
	"prefetchnta 64(%0)\n"
	"prefetchnta 64(%1)\n"
#endif
	"movq   (%0), %%mm0\n"
	"movq  8(%0), %%mm1\n"
	"movq 16(%0), %%mm2\n"
	"movq 24(%0), %%mm3\n"
	"movq 32(%0), %%mm4\n"
	"movq 40(%0), %%mm5\n"
	"movq 48(%0), %%mm6\n"
	"movq 56(%0), %%mm7\n"
	"paddusb   (%1), %%mm0\n"
	"paddusb  8(%1), %%mm1\n"
	"paddusb 16(%1), %%mm2\n"
	"paddusb 24(%1), %%mm3\n"
	"paddusb 32(%1), %%mm4\n"
	"paddusb 40(%1), %%mm5\n"
	"paddusb 48(%1), %%mm6\n"
	"paddusb 56(%1), %%mm7\n"
#ifdef USE_SSE
	"movntq %%mm0,   (%3)\n"
	"movntq %%mm1,  8(%3)\n"
	"movntq %%mm2, 16(%3)\n"
	"movntq %%mm3, 24(%3)\n"
	"movntq %%mm4, 32(%3)\n"
	"movntq %%mm5, 40(%3)\n"
	"movntq %%mm6, 48(%3)\n"
	"movntq %%mm7, 56(%3)\n"
#else
	/* Standard MMX cannot use MOVNTQ for streaming store and thus pollutes the cache */
	"movq %%mm0,   (%3)\n"
	"movq %%mm1,  8(%3)\n"
	"movq %%mm2, 16(%3)\n"
	"movq %%mm3, 24(%3)\n"
	"movq %%mm4, 32(%3)\n"
	"movq %%mm5, 40(%3)\n"
	"movq %%mm6, 48(%3)\n"
	"movq %%mm7, 56(%3)\n"
#endif
	"addl $64, %1\n"
	"addl $64, %0\n"
	"addl $64, %3\n"
	"decl %2\n"
	"cmpl $0, %2\n"
	"jne ImageAdd%=\n"
#ifdef USE_SSE
	"sfence\n" /* memory fence the MOVNTQ's */
#endif
	:
	: "r" (pSrc1), "r" (pSrc2), "r" (NumBytes), "r" (pOut)
	);

	#ifndef NO_EMMS
		asm("emms\n");
	#endif

#else

	/* C Implementation */
	register unsigned int i;
	int value;
	for(i=0; i<NumBytes; i++)
	{
			value = pSrc1[i] + pSrc2[i];
			
			/* Check saturation and adjust if needed */
			if(value > 255)
				value = 255;
			pOut[i] = value;
	}
#endif

}

