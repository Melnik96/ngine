/*
	matrix.c -- SIMDx86 Matrix Library for 4x4 matricies (used in 3D transforms)
	Written by Patrick Baggett, 2005 (baggett.patrick@gmail.com)
	Under LGPL License
	Part of SIMDx86 Project
*/

#include <SIMDx86/matrix.h>

#include <memory.h> /* memcpy() */

void SIMDx86Matrix_Sum(SIMDx86Matrix* Out, const SIMDx86Matrix* In)
{
	Out->m[ 0] += In->m[ 0];
	Out->m[ 1] += In->m[ 1];
	Out->m[ 2] += In->m[ 2];
	Out->m[ 3] += In->m[ 3];
	Out->m[ 4] += In->m[ 4];
	Out->m[ 5] += In->m[ 5];
	Out->m[ 6] += In->m[ 6];
	Out->m[ 7] += In->m[ 7];
	Out->m[ 8] += In->m[ 8];
	Out->m[ 9] += In->m[ 9];
	Out->m[10] += In->m[10];
	Out->m[11] += In->m[11];
	Out->m[12] += In->m[12];
	Out->m[13] += In->m[13];
	Out->m[14] += In->m[14];
	Out->m[15] += In->m[15];
}

void SIMDx86Matrix_SumOf(SIMDx86Matrix* Out, const SIMDx86Matrix* In1, const SIMDx86Matrix* In2)
{
	Out->m[ 0] = In1->m[ 0] + In2->m[ 0];
	Out->m[ 1] = In1->m[ 1] + In2->m[ 1];
	Out->m[ 2] = In1->m[ 2] + In2->m[ 2];
	Out->m[ 3] = In1->m[ 3] + In2->m[ 3];
	Out->m[ 4] = In1->m[ 4] + In2->m[ 4];
	Out->m[ 5] = In1->m[ 5] + In2->m[ 5];
	Out->m[ 6] = In1->m[ 6] + In2->m[ 6];
	Out->m[ 7] = In1->m[ 7] + In2->m[ 7];
	Out->m[ 8] = In1->m[ 8] + In2->m[ 8];
	Out->m[ 9] = In1->m[ 9] + In2->m[ 9];
	Out->m[10] = In1->m[10] + In2->m[10];
	Out->m[11] = In1->m[11] + In2->m[11];
	Out->m[12] = In1->m[12] + In2->m[12];
	Out->m[13] = In1->m[13] + In2->m[13];
	Out->m[14] = In1->m[14] + In2->m[14];
	Out->m[15] = In1->m[15] + In2->m[15];
}

void SIMDx86Matrix_Diff(SIMDx86Matrix* Out, const SIMDx86Matrix* In)
{
	Out->m[ 0] -= In->m[0];
	Out->m[ 1] -= In->m[1];
	Out->m[ 2] -= In->m[2];
	Out->m[ 3] -= In->m[3];
	Out->m[ 4] -= In->m[4];
	Out->m[ 5] -= In->m[5];
	Out->m[ 6] -= In->m[6];
	Out->m[ 7] -= In->m[7];
	Out->m[ 8] -= In->m[8];
	Out->m[ 9] -= In->m[9];
	Out->m[10] -= In->m[10];
	Out->m[11] -= In->m[11];
	Out->m[12] -= In->m[12];
	Out->m[13] -= In->m[13];
	Out->m[14] -= In->m[14];
	Out->m[15] -= In->m[15];
}

void SIMDx86Matrix_DiffOf(SIMDx86Matrix* Out, const SIMDx86Matrix* In1, const SIMDx86Matrix* In2)
{
	Out->m[ 0] = In1->m[0] - In2->m[0];
	Out->m[ 1] = In1->m[1] - In2->m[1];
	Out->m[ 2] = In1->m[2] - In2->m[2];
	Out->m[ 3] = In1->m[3] - In2->m[3];
	Out->m[ 4] = In1->m[4] - In2->m[4];
	Out->m[ 5] = In1->m[5] - In2->m[5];
	Out->m[ 6] = In1->m[6] - In2->m[6];
	Out->m[ 7] = In1->m[7] - In2->m[7];
	Out->m[ 8] = In1->m[8] - In2->m[8];
	Out->m[ 9] = In1->m[9] - In2->m[9];
	Out->m[10] = In1->m[10] - In2->m[10];
	Out->m[11] = In1->m[11] - In2->m[11];
	Out->m[12] = In1->m[12] - In2->m[12];
	Out->m[13] = In1->m[13] - In2->m[13];
	Out->m[14] = In1->m[14] - In2->m[14];
	Out->m[15] = In1->m[15] - In2->m[15];
}

void SIMDx86Matrix_Scale(SIMDx86Matrix* mtx, float scalar)
{
	/* Don't waste CPU time on this */
	if(scalar == 1.0f)
		return;

	mtx->m[0] *= scalar;
	mtx->m[1] *= scalar;
	mtx->m[2] *= scalar;
	mtx->m[3] *= scalar;
	mtx->m[4] *= scalar;
	mtx->m[5] *= scalar;
	mtx->m[6] *= scalar;
	mtx->m[7] *= scalar;
	mtx->m[8] *= scalar;
	mtx->m[9] *= scalar;
	mtx->m[10] *= scalar;
	mtx->m[11] *= scalar;
	mtx->m[12] *= scalar;
	mtx->m[13] *= scalar;
	mtx->m[14] *= scalar;
	mtx->m[15] *= scalar;

}

void SIMDx86Matrix_AlignedScaleOf(SIMDx86Matrix* pOut, const SIMDx86Matrix* pIn, float scalar)
{
	#if defined(USE_SSE)

	asm(
	"movss %1, %%xmm4\n"
	"movaps   (%0), %%xmm0\n"
	"movaps 16(%0), %%xmm1\n"
	"movaps 32(%0), %%xmm2\n"
	"movaps 48(%0), %%xmm3\n"
	"shufps $0x00, %%xmm4, %%xmm4\n"
	"mulps %%xmm4, %%xmm0\n"
	"mulps %%xmm4, %%xmm1\n"
	"mulps %%xmm4, %%xmm2\n"
	"mulps %%xmm4, %%xmm3\n"
	"movaps %%xmm0,   (%2)\n"
	"movaps %%xmm1, 16(%2)\n"
	"movaps %%xmm2, 32(%2)\n"
	"movaps %%xmm3, 48(%2)\n"
	:
	: "r" (pIn), "m" (scalar), "r" (pOut)
	);

	#elif defined(USE_3DNOW)
	asm(
	"movd %0, %%mm0\n"
	"punpckldq %%mm0, %%mm0\n"
	"movq %%mm0, %%mm1\n"
	"movq %%mm0, %%mm2\n"
	"movq %%mm0, %%mm3\n"
	"movq %%mm0, %%mm4\n"
	"movq %%mm0, %%mm5\n"
	"movq %%mm0, %%mm6\n"
	"movq %%mm0, %%mm7\n"
	"pfmul   (%1), %%mm0\n"
	"pfmul  8(%1), %%mm1\n"
	"pfmul 16(%1), %%mm2\n"
	"pfmul 24(%1), %%mm3\n"
	"pfmul 32(%1), %%mm4\n"
	"pfmul 40(%1), %%mm5\n"
	"pfmul 48(%1), %%mm6\n"
	"pfmul 56(%1), %%mm7\n"
	"movq %%mm0,   (%2)\n"
	"movq %%mm1,  8(%2)\n"
	"movq %%mm2, 16(%2)\n"
	"movq %%mm3, 24(%2)\n"
	"movq %%mm4, 32(%2)\n"
	"movq %%mm5, 40(%2)\n"
	"movq %%mm6, 48(%2)\n"
	"movq %%mm7, 56(%2)\n"
	:
	: "m" (scalar), "r" (pIn), "r" (pOut)
	);

	/* Execute 'femms' if desired */
	#ifndef NO_EMMS
	asm("femms\n");
	#endif


	#else

	/* Don't waste CPU time */
	if(scalar == 1.0f)
	{
		memcpy((void*)pOut, (const void*)pIn, sizeof(SIMDx86Matrix));
		return;
	}

	pOut->m[0] = pIn->m[0] * scalar;
	pOut->m[1] = pIn->m[1] * scalar;
	pOut->m[2] = pIn->m[2] * scalar;
	pOut->m[3] = pIn->m[3] * scalar;
	pOut->m[4] = pIn->m[4] * scalar;
	pOut->m[5] = pIn->m[5] * scalar;
	pOut->m[6] = pIn->m[6] * scalar;
	pOut->m[7] = pIn->m[7] * scalar;
	pOut->m[8] = pIn->m[8] * scalar;
	pOut->m[9] = pIn->m[9] * scalar;
	pOut->m[10] = pIn->m[10] * scalar;
	pOut->m[11] = pIn->m[11] * scalar;
	pOut->m[12] = pIn->m[12] * scalar;
	pOut->m[13] = pIn->m[13] * scalar;
	pOut->m[14] = pIn->m[14] * scalar;
	pOut->m[15] = pIn->m[15] * scalar;
	#endif
}

void SIMDx86Matrix_AlignedMultiply(SIMDx86Matrix* pLeft, const SIMDx86Matrix* pRight)
{
	#if defined(USE_SSE)
	asm(
	"movaps   (%0), %%xmm0\n"	/* xmm0 = pRight[0..3] */
	"movaps 16(%0), %%xmm1\n"	/* xmm1 = pRight[5..7] */
	"movaps 32(%0), %%xmm2\n"	/* xmm2 = pRight[8..11] */
	"movaps 48(%0), %%xmm3\n"	/* xmm3 = pRight[12..15] */

	/* Processes 1/2 of the matrix at a time (2x4), unrolled loop */
	"movss    (%1), %%xmm4\n"
	"movss   4(%1), %%xmm6\n"
	"movss  16(%1), %%xmm5\n"
	"movss  20(%1), %%xmm7\n"
	"shufps $0x00, %%xmm4, %%xmm4\n"
	"shufps $0x00, %%xmm5, %%xmm5\n"
	"shufps $0x00, %%xmm6, %%xmm6\n"
	"shufps $0x00, %%xmm7, %%xmm7\n"
	"mulps %%xmm0, %%xmm4\n"
	"mulps %%xmm0, %%xmm5\n"
	"mulps %%xmm1, %%xmm6\n"
	"mulps %%xmm1, %%xmm7\n"
	"addps %%xmm7, %%xmm5\n"
	"addps %%xmm6, %%xmm4\n"


	"movss  8(%1), %%xmm6\n"
	"movss 24(%1), %%xmm7\n"
	"shufps $0x00, %%xmm6, %%xmm6\n"
	"shufps $0x00, %%xmm7, %%xmm7\n"
	"mulps %%xmm2, %%xmm6\n"
	"mulps %%xmm2, %%xmm7\n"
	"addps %%xmm6, %%xmm4\n"
	"addps %%xmm7, %%xmm5\n"

	"movss  12(%1), %%xmm6\n"
	"movss  28(%1), %%xmm7\n"
	"shufps $0x00, %%xmm6, %%xmm6\n"
	"shufps $0x00, %%xmm7, %%xmm7\n"
	"mulps %%xmm3, %%xmm6\n"
	"mulps %%xmm3, %%xmm7\n"
	"addps %%xmm6, %%xmm4\n"
	"addps %%xmm7, %%xmm5\n"

	"movaps %%xmm4, (%1)\n"
	"movaps %%xmm5, 16(%1)\n"

	/* second half of the matrix */
	"movss  32(%1), %%xmm4\n"
	"movss  36(%1), %%xmm6\n"
	"movss  48(%1), %%xmm5\n"
	"movss  52(%1), %%xmm7\n"
	"shufps $0x00, %%xmm4, %%xmm4\n"
	"shufps $0x00, %%xmm5, %%xmm5\n"
	"mulps %%xmm0, %%xmm4\n"
	"mulps %%xmm0, %%xmm5\n"

	"shufps $0x00, %%xmm6, %%xmm6\n"
	"shufps $0x00, %%xmm7, %%xmm7\n"
	"mulps %%xmm1, %%xmm6\n"
	"mulps %%xmm1, %%xmm7\n"
	"addps %%xmm6, %%xmm4\n"
	"addps %%xmm7, %%xmm5\n"


	"movss 40(%1), %%xmm6\n"
	"movss 56(%1), %%xmm7\n"
	"shufps $0x00, %%xmm6, %%xmm6\n"
	"shufps $0x00, %%xmm7, %%xmm7\n"
	"mulps %%xmm2, %%xmm6\n"
	"mulps %%xmm2, %%xmm7\n"
	"addps %%xmm6, %%xmm4\n"
	"addps %%xmm7, %%xmm5\n"

	"movss  44(%1), %%xmm6\n"
	"movss  60(%1), %%xmm7\n"
	"shufps $0x00, %%xmm6, %%xmm6\n"
	"shufps $0x00, %%xmm7, %%xmm7\n"
	"mulps %%xmm3, %%xmm6\n"
	"mulps %%xmm3, %%xmm7\n"
	"addps %%xmm6, %%xmm4\n"
	"addps %%xmm7, %%xmm5\n"

	"movaps %%xmm4, 32(%1)\n"
	"movaps %%xmm5, 48(%1)\n"

	:
	: "r" (pRight), "r" (pLeft)
	);


	#elif defined(USE_3DNOW)

	asm(
	"movl $4, %%ecx\n"
	"MatrixMultiply_3DNow_Loop%=:\n"
	"movd   (%0), %%mm0\n"			/* mm0 = ? | x */
	"movd  4(%0), %%mm2\n"			/* mm2 = ? | y */
	"movd  8(%0), %%mm4\n"			/* mm4 = ? | z */
	"movd 12(%0), %%mm6\n"			/* mm6 = ? | w */
	"prefetchw 16(%0)\n"			/* prefetch_for_writing(m[4]...m[7]);  */
	"punpckldq %%mm0, %%mm0\n"		/* mm0 = x | x */
	"punpckldq %%mm2, %%mm2\n"		/* mm2 = y | y */
	"punpckldq %%mm4, %%mm4\n"		/* mm4 = z | z */
	"punpckldq %%mm6, %%mm6\n"		/* mm6 = w | w */
	"movq %%mm0, %%mm1\n"			/* mm1 = x | x */
	"movq %%mm2, %%mm3\n"			/* mm3 = y | y */
	"movq %%mm4, %%mm5\n"			/* mm5 = z | z */
	"movq %%mm6, %%mm7\n"			/* mm7 = w | w */
	"pfmul   (%1), %%mm0\n"			/* mm0 = x*m[1]  | x*m[0] */
	"pfmul  8(%1), %%mm1\n"			/* mm1 = x*m[3]  | x*m[2] */
	"pfmul 16(%1), %%mm2\n" 		/* mm2 = y*m[5]  | y*m[4] */
	"pfmul 24(%1), %%mm3\n" 		/* mm3 = y*m[7]  | y*m[6] */
	"pfmul 32(%1), %%mm4\n" 		/* mm4 = z*m[9]  | z*m[8] */
	"pfmul 40(%1), %%mm5\n" 		/* mm5 = z*m[11] | z*m[10] */
	"pfmul 48(%1), %%mm6\n" 		/* mm6 = w*m[13] | w*m[12] */
	"pfmul 56(%1), %%mm7\n" 		/* mm7 = w*m[15] | w*m[14] */
	"pfadd %%mm0, %%mm2\n"
	"pfadd %%mm1, %%mm3\n"
	"pfadd %%mm4, %%mm6\n"
	"pfadd %%mm5, %%mm7\n"
	"pfadd %%mm2, %%mm6\n"
	"pfadd %%mm3, %%mm7\n"
	"movq %%mm6,  (%0)\n"
	"movq %%mm7, 8(%0)\n"
	"addl $16, %0\n"
	"loop MatrixMultiply_3DNow_Loop%=\n"
	:
	: "r" (pLeft), "r" (pRight)
	: "%ecx"
	);

	/* Execute 'femms' if desired */
	#ifndef NO_EMMS
	asm("femms\n");
	#endif


	#else

	/*
		This is ugly: Since the matrix cannot be stored in registers, it must have a stack copy or else the matrix
		is being overwritten as it is being multiplied.
		This results in some bad performance when benched against an SIMD implementation
	*/
	SIMDx86Matrix temp;


	memcpy(&temp, pLeft, sizeof(SIMDx86Matrix));

	SIMDx86Matrix_AlignedMultiplyOf(pLeft, &temp, pRight);


	#endif

}

void SIMDx86Matrix_AlignedMultiplyOf(SIMDx86Matrix* pOut, const SIMDx86Matrix* pLeft, const SIMDx86Matrix* pRight)
{
	#if defined(USE_SSE)

	asm(
	"movaps   (%0), %%xmm0\n"	/* xmm0 = pRight[0..3] */
	"movaps 16(%0), %%xmm1\n"	/* xmm1 = pRight[5..7] */
	"movaps 32(%0), %%xmm2\n"	/* xmm2 = pRight[8..11] */
	"movaps 48(%0), %%xmm3\n"	/* xmm3 = pRight[12..15] */

	/* Processes 1/2 of the matrix at a time (2x4), unrolled loop */
	"movss    (%1), %%xmm4\n"
	"movss   4(%1), %%xmm6\n"
	"movss  16(%1), %%xmm5\n"
	"movss  20(%1), %%xmm7\n"
	"shufps $0x00, %%xmm4, %%xmm4\n"
	"shufps $0x00, %%xmm5, %%xmm5\n"
	"shufps $0x00, %%xmm6, %%xmm6\n"
	"shufps $0x00, %%xmm7, %%xmm7\n"
	"mulps %%xmm0, %%xmm4\n"
	"mulps %%xmm0, %%xmm5\n"
	"mulps %%xmm1, %%xmm6\n"
	"mulps %%xmm1, %%xmm7\n"
	"addps %%xmm7, %%xmm5\n"
	"addps %%xmm6, %%xmm4\n"


	"movss  8(%1), %%xmm6\n"
	"movss 24(%1), %%xmm7\n"
	"shufps $0x00, %%xmm6, %%xmm6\n"
	"shufps $0x00, %%xmm7, %%xmm7\n"
	"mulps %%xmm2, %%xmm6\n"
	"mulps %%xmm2, %%xmm7\n"
	"addps %%xmm6, %%xmm4\n"
	"addps %%xmm7, %%xmm5\n"

	"movss  12(%1), %%xmm6\n"
	"movss  28(%1), %%xmm7\n"
	"shufps $0x00, %%xmm6, %%xmm6\n"
	"shufps $0x00, %%xmm7, %%xmm7\n"
	"mulps %%xmm3, %%xmm6\n"
	"mulps %%xmm3, %%xmm7\n"
	"addps %%xmm6, %%xmm4\n"
	"addps %%xmm7, %%xmm5\n"

	"movaps %%xmm4, (%2)\n"
	"movaps %%xmm5, 16(%2)\n"

	/* second half of the matrix */
	"movss  32(%1), %%xmm4\n"
	"movss  36(%1), %%xmm6\n"
	"movss  48(%1), %%xmm5\n"
	"movss  52(%1), %%xmm7\n"
	"shufps $0x00, %%xmm4, %%xmm4\n"
	"shufps $0x00, %%xmm5, %%xmm5\n"
	"mulps %%xmm0, %%xmm4\n"
	"mulps %%xmm0, %%xmm5\n"

	"shufps $0x00, %%xmm6, %%xmm6\n"
	"shufps $0x00, %%xmm7, %%xmm7\n"
	"mulps %%xmm1, %%xmm6\n"
	"mulps %%xmm1, %%xmm7\n"
	"addps %%xmm6, %%xmm4\n"
	"addps %%xmm7, %%xmm5\n"


	"movss 40(%1), %%xmm6\n"
	"movss 56(%1), %%xmm7\n"
	"shufps $0x00, %%xmm6, %%xmm6\n"
	"shufps $0x00, %%xmm7, %%xmm7\n"
	"mulps %%xmm2, %%xmm6\n"
	"mulps %%xmm2, %%xmm7\n"
	"addps %%xmm6, %%xmm4\n"
	"addps %%xmm7, %%xmm5\n"

	"movss  44(%1), %%xmm6\n"
	"movss  60(%1), %%xmm7\n"
	"shufps $0x00, %%xmm6, %%xmm6\n"
	"shufps $0x00, %%xmm7, %%xmm7\n"
	"mulps %%xmm3, %%xmm6\n"
	"mulps %%xmm3, %%xmm7\n"
	"addps %%xmm6, %%xmm4\n"
	"addps %%xmm7, %%xmm5\n"

	"movaps %%xmm4, 32(%2)\n"
	"movaps %%xmm5, 48(%2)\n"

	:
	: "r" (pRight), "r" (pLeft), "r" (pOut)
	);

	#elif defined(USE_3DNOW)
	asm(
	"movl $4, %%ecx\n"
	"MatrixMultiplyOf_3DNow_Loop%=:\n"
	"movd   (%0), %%mm0\n"			/* mm0 = ? | x */
	"movd  4(%0), %%mm2\n"			/* mm2 = ? | y */
	"movd  8(%0), %%mm4\n"			/* mm4 = ? | z */
	"movd 12(%0), %%mm6\n"			/* mm6 = ? | w */
	"prefetch 16(%0)\n"				/* prefetch_for_reading(in+4);  */
	"prefetchw 16(%2)\n"			/* prefetch_for_writing(out+4); */
	"punpckldq %%mm0, %%mm0\n"		/* mm0 = x | x */
	"punpckldq %%mm2, %%mm2\n"		/* mm2 = y | y */
	"punpckldq %%mm4, %%mm4\n"		/* mm4 = z | z */
	"punpckldq %%mm6, %%mm6\n"		/* mm6 = w | w */
	"movq %%mm0, %%mm1\n"			/* mm1 = x | x */
	"movq %%mm2, %%mm3\n"			/* mm3 = y | y */
	"movq %%mm4, %%mm5\n"			/* mm5 = z | z */
	"movq %%mm6, %%mm7\n"			/* mm7 = w | w */
	"pfmul   (%1), %%mm0\n"			/* mm0 = x*m[1]  | x*m[0] */
	"pfmul  8(%1), %%mm1\n"			/* mm1 = x*m[3]  | x*m[2] */
	"pfmul 16(%1), %%mm2\n" 		/* mm2 = y*m[5]  | y*m[4] */
	"pfmul 24(%1), %%mm3\n" 		/* mm3 = y*m[7]  | y*m[6] */
	"pfmul 32(%1), %%mm4\n" 		/* mm4 = z*m[9]  | z*m[8] */
	"pfmul 40(%1), %%mm5\n" 		/* mm5 = z*m[11] | z*m[10] */
	"pfmul 48(%1), %%mm6\n" 		/* mm6 = w*m[13] | w*m[12] */
	"pfmul 56(%1), %%mm7\n" 		/* mm7 = w*m[15] | w*m[14] */
	"pfadd %%mm0, %%mm2\n"
	"pfadd %%mm1, %%mm3\n"
	"pfadd %%mm4, %%mm6\n"
	"pfadd %%mm5, %%mm7\n"
	"pfadd %%mm2, %%mm6\n"
	"pfadd %%mm3, %%mm7\n"
	"movq %%mm6,  (%2)\n"
	"movq %%mm7, 8(%2)\n"
	"addl $16, %0\n"
	"addl $16, %2\n"
	"loop MatrixMultiplyOf_3DNow_Loop%=\n"
	:
	: "r" (pLeft), "r" (pRight), "r" (pOut)
	: "%ecx"
	);

	/* Execute 'femms' if desired */
	#ifndef NO_EMMS
	asm("femms\n");
	#endif

	#else

	pOut->m[0] = pRight->m[0]*pLeft->m[0] + pRight->m[4]*pLeft->m[1] + pRight->m[8]*pLeft->m[2] + pRight->m[12]*pLeft->m[3];
	pOut->m[1] = pRight->m[1]*pLeft->m[0] + pRight->m[5]*pLeft->m[1] + pRight->m[9]*pLeft->m[2] + pRight->m[13]*pLeft->m[3];
	pOut->m[2] = pRight->m[2]*pLeft->m[0] + pRight->m[6]*pLeft->m[1] + pRight->m[10]*pLeft->m[2] + pRight->m[14]*pLeft->m[3];
	pOut->m[3] = pRight->m[3]*pLeft->m[0] + pRight->m[7]*pLeft->m[1] + pRight->m[11]*pLeft->m[2] + pRight->m[15]*pLeft->m[3];

	pOut->m[4] = pRight->m[0]*pLeft->m[4] + pRight->m[4]*pLeft->m[5] + pRight->m[8]*pLeft->m[6] + pRight->m[12]*pLeft->m[7];
	pOut->m[5] = pRight->m[1]*pLeft->m[4] + pRight->m[5]*pLeft->m[5] + pRight->m[9]*pLeft->m[6] + pRight->m[13]*pLeft->m[7];
	pOut->m[6] = pRight->m[2]*pLeft->m[4] + pRight->m[6]*pLeft->m[5] + pRight->m[10]*pLeft->m[6] + pRight->m[14]*pLeft->m[7];
	pOut->m[7] = pRight->m[3]*pLeft->m[4] + pRight->m[7]*pLeft->m[5] + pRight->m[11]*pLeft->m[6] + pRight->m[15]*pLeft->m[7];

	pOut->m[8] = pRight->m[0]*pLeft->m[8] + pRight->m[4]*pLeft->m[9] + pRight->m[8]*pLeft->m[10] + pRight->m[12]*pLeft->m[11];
	pOut->m[9] = pRight->m[1]*pLeft->m[8] + pRight->m[5]*pLeft->m[9] + pRight->m[9]*pLeft->m[10] + pRight->m[13]*pLeft->m[11];
	pOut->m[10] = pRight->m[2]*pLeft->m[8] + pRight->m[6]*pLeft->m[9] + pRight->m[10]*pLeft->m[10] + pRight->m[14]*pLeft->m[11];
	pOut->m[11] = pRight->m[3]*pLeft->m[8] + pRight->m[7]*pLeft->m[9] + pRight->m[11]*pLeft->m[10] + pRight->m[15]*pLeft->m[11];

	pOut->m[12] = pRight->m[0]*pLeft->m[12] + pRight->m[4]*pLeft->m[13] + pRight->m[8]*pLeft->m[14] + pRight->m[12]*pLeft->m[15];
	pOut->m[13] = pRight->m[1]*pLeft->m[12] + pRight->m[5]*pLeft->m[13] + pRight->m[9]*pLeft->m[14] + pRight->m[13]*pLeft->m[15];
	pOut->m[14] = pRight->m[2]*pLeft->m[12] + pRight->m[6]*pLeft->m[13] + pRight->m[10]*pLeft->m[14] + pRight->m[14]*pLeft->m[15];
	pOut->m[15] = pRight->m[3]*pLeft->m[12] + pRight->m[7]*pLeft->m[13] + pRight->m[11]*pLeft->m[14] + pRight->m[15]*pLeft->m[15];
	#endif

}

void SIMDx86Matrix_AlignedTranspose(SIMDx86Matrix* pIn)
{
	#if defined(USE_SSE)
	asm(
		"movlps	  (%0), %%xmm1\n"
		"movlps	 8(%0), %%xmm3\n"
		"movhps	16(%0), %%xmm1\n"
		"movhps	24(%0), %%xmm3\n"
		"movlps	32(%0), %%xmm5\n"
		"movlps	40(%0), %%xmm4\n"
		"movhps	48(%0), %%xmm5\n"
		"movhps	56(%0), %%xmm4\n"
		"movaps	%%xmm1, %%xmm0\n"
		"movaps	%%xmm3, %%xmm2\n"
		"shufps	$0xDD, %%xmm5,%%xmm1\n"
		"shufps	$0xDD, %%xmm4,%%xmm3\n"
		"shufps	$0x88, %%xmm5,%%xmm0\n"
		"shufps	$0x88, %%xmm4,%%xmm2\n"
		"movaps %%xmm0,   (%0)\n"
		"movaps %%xmm1, 16(%0)\n"
		"movaps %%xmm2, 32(%0)\n"
		"movaps %%xmm3, 48(%0)\n"
		:
		: "r" (pIn)
		);

	#else
	SIMDx86Matrix temp;

	memcpy(&temp, pIn, sizeof(SIMDx86Matrix));
/*  pIn->m[0] = temp.m[0]; */
	pIn->m[1] = temp.m[4];
	pIn->m[2] = temp.m[8];
	pIn->m[3] = temp.m[12];

	pIn->m[4] = temp.m[1];
/*  pIn->m[5] = temp.m[5]; */
	pIn->m[6] = temp.m[9];
	pIn->m[7] = temp.m[13];

	pIn->m[8] = temp.m[2];
	pIn->m[9] = temp.m[6];
/*  pIn->m[10] = temp.m[10]; */
	pIn->m[11] = temp.m[14];

	pIn->m[12] = temp.m[3];
	pIn->m[13] = temp.m[7];
	pIn->m[14] = temp.m[11];
/*  pIn->m[15] = temp.m[15]; */
	#endif
	
}

void SIMDx86Matrix_AlignedTransposeOf(SIMDx86Matrix* pOut, const SIMDx86Matrix* pIn)
{
	#if defined(USE_SSE)
	asm(
		"movlps	  (%0), %%xmm1\n"
		"movlps	 8(%0), %%xmm3\n"
		"movhps	16(%0), %%xmm1\n"
		"movhps	24(%0), %%xmm3\n"
		"movlps	32(%0), %%xmm5\n"
		"movlps	40(%0), %%xmm4\n"
		"movhps	48(%0), %%xmm5\n"
		"movhps	56(%0), %%xmm4\n"
		"movaps	%%xmm1, %%xmm0\n"
		"movaps	%%xmm3, %%xmm2\n"
		"shufps	$0xDD, %%xmm5,%%xmm1\n"
		"shufps	$0xDD, %%xmm4,%%xmm3\n"
		"shufps	$0x88, %%xmm5,%%xmm0\n"
		"shufps	$0x88, %%xmm4,%%xmm2\n"
		"movaps %%xmm0,   (%1)\n"
		"movaps %%xmm1, 16(%1)\n"
		"movaps %%xmm2, 32(%1)\n"
		"movaps %%xmm3, 48(%1)\n"
		:
		: "r" (pIn), "r" (pOut)
		);

	#else

	pOut->m[0] = pIn->m[0];
	pOut->m[1] = pIn->m[4];
	pOut->m[2] = pIn->m[8];
	pOut->m[3] = pIn->m[12];

	pOut->m[4] = pIn->m[1];
	pOut->m[5] = pIn->m[5];
	pOut->m[6] = pIn->m[9];
	pOut->m[7] = pIn->m[13];

	pOut->m[8] = pIn->m[2];
	pOut->m[9] = pIn->m[6];
	pOut->m[10] = pIn->m[10];
	pOut->m[11] = pIn->m[14];

	pOut->m[12] = pIn->m[3];
	pOut->m[13] = pIn->m[7];
	pOut->m[14] = pIn->m[11];
	pOut->m[15] = pIn->m[15];
	#endif
}

void SIMDx86Matrix_AlignedVectorMultiply(SIMDx86Vector* pVec, const SIMDx86Matrix* pMat)
{
	/*
		Does a normal vector x matrix, but since w = 1.0f, the final column of the matrix is
		merely added.
	*/

	#if defined(USE_SSE)

	asm(
	"movaps   (%1), %%xmm4\n"
	"movaps %%xmm4, %%xmm5\n"
	"movaps %%xmm4, %%xmm6\n"
	"shufps $0x00, %%xmm4, %%xmm4\n"    /* xmm4 = x | x | x | x */
	"shufps $0x55, %%xmm5, %%xmm5\n"    /* xmm5 = y | y | y | y */
	"shufps $0xAA, %%xmm6, %%xmm6\n"    /* xmm6 = z | z | z | z */

	/* Multiply with each row */
	"mulps   (%0), %%xmm4\n"
	"mulps 16(%0), %%xmm5\n"
	"mulps 32(%0), %%xmm6\n"

	/* Sum results, xmm0-2 = transformed x,y,z colums, xmm3 = w column */
	"addps %%xmm4, %%xmm5\n"    /* xmm1 = tx + ty */
	"addps 48(%0), %%xmm6\n"    /* xmm3 = tz + w */
	"addps %%xmm5, %%xmm6\n"    /* xmm1 = tx + ty + tz + w*/

	/* Store translated vector */
	"movaps %%xmm6, (%1)\n"
	:
	: "r" (pMat), "r" (pVec)
	);
	#elif defined(USE_3DNOW)

	asm(
	"movd   (%0), %%mm0\n"			/* mm0 = ? | x */
	"movd  4(%0), %%mm2\n"			/* mm2 = ? | y */
	"movd  8(%0), %%mm4\n"			/* mm4 = ? | z */
	"punpckldq %%mm0, %%mm0\n"		/* mm0 = x | x */
	"punpckldq %%mm2, %%mm2\n"		/* mm2 = y | y */
	"punpckldq %%mm4, %%mm4\n"		/* mm4 = z | z */
	"movq %%mm0, %%mm1\n"			/* mm1 = x | x */
	"movq %%mm2, %%mm3\n"			/* mm3 = y | y */
	"movq %%mm4, %%mm5\n"			/* mm5 = z | z */
	"pfmul   (%1), %%mm0\n"			/* mm0 = x*m[1]  | x*m[0] */
	"pfmul  8(%1), %%mm1\n"			/* mm1 = x*m[3]  | x*m[2] */
	"pfmul 16(%1), %%mm2\n" 		/* mm2 = y*m[5]  | y*m[4] */
	"pfmul 24(%1), %%mm3\n" 		/* mm3 = y*m[7]  | y*m[6] */
	"pfmul 32(%1), %%mm4\n" 		/* mm4 = z*m[9]  | z*m[8] */
	"pfmul 40(%1), %%mm5\n" 		/* mm5 = z*m[11] | z*m[10] */
	"pfadd 48(%1), %%mm4\n"         /* mm4 = z*m[9] + m[13]  | z*m[8] + m[12] */
	"pfadd 56(%1), %%mm5\n"			/* mm5 = z*m[11] + m[15] | z*m[10] + m[14] */

	/* Sum it... (not displaying register contents.... */

	/* Combine X and Y column into mm2-3 */
	"pfadd %%mm0, %%mm2\n"
	"pfadd %%mm1, %%mm3\n"

	/* Combine with ZW column into mm2-3 */
	"pfadd %%mm4, %%mm2\n"
	"pfadd %%mm5, %%mm3\n"
	
	"movq %%mm2,  (%0)\n"
	"movq %%mm3, 8(%0)\n"
	:
	: "r" (pVec), "r" (pMat)
	);

	/* Execute 'femms' if desired */
	#ifndef NO_EMMS
	asm("femms\n");
	#endif

	#else
	float In[3] = { pVec->x, pVec->y, pVec->z };

	pVec->x = (In[0]*pMat->m[0]) + (In[1]*pMat->m[4]) + (In[2]*pMat->m[8]) + pMat->m[12];
	pVec->y = (In[0]*pMat->m[1]) + (In[1]*pMat->m[5]) + (In[2]*pMat->m[9]) + pMat->m[13];
	pVec->z = (In[0]*pMat->m[2]) + (In[1]*pMat->m[6]) + (In[2]*pMat->m[10]) + pMat->m[14];
	#endif

}

void SIMDx86Matrix_AlignedVectorMultiplyOf(SIMDx86Vector* pOut, const SIMDx86Vector* pIn, const SIMDx86Matrix* pMat)
{
	/*
		Does a normal vector x matrix, but since w = 1.0f, the final column of the matrix is
		merely added.
	*/

	#if defined(USE_SSE)
	asm(
	"movaps   (%1), %%xmm4\n"
	"movaps %%xmm4, %%xmm5\n"
	"movaps %%xmm4, %%xmm6\n"
	"shufps $0x00, %%xmm4, %%xmm4\n"    /* xmm4 = x | x | x | x */
	"shufps $0x55, %%xmm5, %%xmm5\n"    /* xmm5 = y | y | y | y */
	"shufps $0xAA, %%xmm6, %%xmm6\n"    /* xmm6 = z | z | z | z */

	/* Multiply with each row */
	"mulps   (%0), %%xmm4\n"
	"mulps 16(%0), %%xmm5\n"
	"mulps 32(%0), %%xmm6\n"

	/* Sum results, xmm0-2 = transformed x,y,z colums, xmm3 = w column */
	"addps %%xmm4, %%xmm5\n"    /* xmm1 = tx + ty */
	"addps 48(%0), %%xmm6\n"    /* xmm3 = tz + w */
	"addps %%xmm5, %%xmm6\n"    /* xmm1 = tx + ty + tz + w*/

	/* Store translated vector */
	"movaps %%xmm6, (%2)\n"
	:
	: "r" (pMat), "r" (pIn), "r" (pOut)
	);
	#elif defined(USE_3DNOW)

	asm(
	"movd   (%0), %%mm0\n"			/* mm0 = ? | x */
	"movd  4(%0), %%mm2\n"			/* mm2 = ? | y */
	"movd  8(%0), %%mm4\n"			/* mm4 = ? | z */
	"punpckldq %%mm0, %%mm0\n"		/* mm0 = x | x */
	"punpckldq %%mm2, %%mm2\n"		/* mm2 = y | y */
	"punpckldq %%mm4, %%mm4\n"		/* mm4 = z | z */
	"movq %%mm0, %%mm1\n"			/* mm1 = x | x */
	"movq %%mm2, %%mm3\n"			/* mm3 = y | y */
	"movq %%mm4, %%mm5\n"			/* mm5 = z | z */
	"pfmul   (%1), %%mm0\n"			/* mm0 = x*m[1]  | x*m[0] */
	"pfmul  8(%1), %%mm1\n"			/* mm1 = x*m[3]  | x*m[2] */
	"pfmul 16(%1), %%mm2\n" 		/* mm2 = y*m[5]  | y*m[4] */
	"pfmul 24(%1), %%mm3\n" 		/* mm3 = y*m[7]  | y*m[6] */
	"pfmul 32(%1), %%mm4\n" 		/* mm4 = z*m[9]  | z*m[8] */
	"pfmul 40(%1), %%mm5\n" 		/* mm5 = z*m[11] | z*m[10] */
	"pfadd 48(%1), %%mm4\n"         /* mm4 = z*m[9] + m[13]  | z*m[8] + m[12] */
	"pfadd 56(%1), %%mm5\n"			/* mm5 = z*m[11] + m[15] | z*m[10] + m[14] */

	/* Sum it... (not displaying register contents.... */

	/* Combine X and Y column into mm2-3 */
	"pfadd %%mm0, %%mm2\n"
	"pfadd %%mm1, %%mm3\n"

	/* Combine with ZW column into mm2-3 */
	"pfadd %%mm4, %%mm2\n"
	"pfadd %%mm5, %%mm3\n"

	"movq %%mm2,  (%2)\n"
	"movq %%mm3, 8(%2)\n"
	:
	: "r" (pIn), "r" (pMat), "r" (pOut)
	);

	/* Execute 'femms' if desired */
	#ifndef NO_EMMS
	asm("femms\n");
	#endif

	#else

	pOut->x = (pIn->x*pMat->m[0]) + (pIn->y*pMat->m[4]) + (pIn->z*pMat->m[8]) + pMat->m[12];
	pOut->y = (pIn->x*pMat->m[1]) + (pIn->y*pMat->m[5]) + (pIn->z*pMat->m[9]) + pMat->m[13];
	pOut->z = (pIn->x*pMat->m[2]) + (pIn->y*pMat->m[6]) + (pIn->z*pMat->m[10]) + pMat->m[14];
	#endif
}

void SIMDx86Matrix_AlignedVector4Multiply(float* pOut4D, const SIMDx86Matrix* pMat)
{
	#if defined(USE_SSE)

	asm(
	"movaps (%1), %%xmm4\n"
	"movaps %%xmm4, %%xmm5\n"
	"movaps %%xmm4, %%xmm6\n"
	"movaps  %%xmm4, %%xmm7\n"
	"shufps $0x00, %%xmm4, %%xmm4\n"
	"shufps $0x55, %%xmm5, %%xmm5\n"
	"shufps $0xAA, %%xmm6, %%xmm6\n"
	"shufps $0xFF, %%xmm7, %%xmm7\n"

	/* Multiply with each row */
	"mulps   (%0), %%xmm4\n"
	"mulps 16(%0), %%xmm5\n"
	"mulps 32(%0), %%xmm6\n"
	"mulps 48(%0), %%xmm7\n"

	/* Sum results */
	"addps %%xmm4, %%xmm5\n"
	"addps %%xmm6, %%xmm7\n"
	"addps %%xmm5, %%xmm7\n"

	/* Store translated vector */
	"movaps %%xmm7, (%1)\n"
	:
	: "r" (pMat), "r" (pOut4D)
	);
	#elif defined(USE_3DNOW)

	asm(
	"movd   (%0), %%mm0\n"			/* mm0 = ? | x */
	"movd  4(%0), %%mm2\n"			/* mm2 = ? | y */
	"movd  8(%0), %%mm4\n"			/* mm4 = ? | z */
	"movd 12(%0), %%mm6\n"			/* mm6 = ? | w */
	"punpckldq %%mm0, %%mm0\n"		/* mm0 = x | x */
	"punpckldq %%mm2, %%mm2\n"		/* mm2 = y | y */
	"punpckldq %%mm4, %%mm4\n"		/* mm4 = z | z */
	"punpckldq %%mm6, %%mm6\n"		/* mm6 = w | w */
	"movq %%mm0, %%mm1\n"			/* mm1 = x | x */
	"movq %%mm2, %%mm3\n"			/* mm3 = y | y */
	"movq %%mm4, %%mm5\n"			/* mm5 = z | z */
	"movq %%mm6, %%mm7\n"			/* mm7 = w | w */
	"pfmul   (%1), %%mm0\n"			/* mm0 = x*m[1]  | x*m[0] */
	"pfmul  8(%1), %%mm1\n"			/* mm1 = x*m[3]  | x*m[2] */
	"pfmul 16(%1), %%mm2\n" 		/* mm2 = y*m[5]  | y*m[4] */
	"pfmul 24(%1), %%mm3\n" 		/* mm3 = y*m[7]  | y*m[6] */
	"pfmul 32(%1), %%mm4\n" 		/* mm4 = z*m[9]  | z*m[8] */
	"pfmul 40(%1), %%mm5\n" 		/* mm5 = z*m[11] | z*m[10] */
	"pfmul 48(%1), %%mm6\n" 		/* mm6 = w*m[13] | w*m[12] */
	"pfmul 56(%1), %%mm7\n" 		/* mm7 = w*m[15] | w*m[14] */

	/* Sum it... (not displaying register contents.... */
	"pfadd %%mm0, %%mm2\n"
	"pfadd %%mm1, %%mm3\n"
	"pfadd %%mm4, %%mm6\n"
	"pfadd %%mm5, %%mm7\n"
	"pfadd %%mm2, %%mm6\n"
	"pfadd %%mm3, %%mm7\n"
	"movq %%mm6,  (%0)\n"
	"movq %%mm7, 8(%0)\n"
	:
	: "r" (pOut4D), "r" (pMat)
	);

	/* Execute 'femms' if desired */
	#ifndef NO_EMMS
	asm("femms\n");
	#endif

	#else
	float In[4] = { pOut4D[0], pOut4D[1], pOut4D[2], pOut4D[3] };

	pOut4D[0] = (In[0]*pMat->m[0]) + (In[1]*pMat->m[4]) + (In[2]*pMat->m[8]) + (In[3]*pMat->m[12]);
	pOut4D[1] = (In[0]*pMat->m[1]) + (In[1]*pMat->m[5]) + (In[2]*pMat->m[9]) + (In[3]*pMat->m[13]);
	pOut4D[2] = (In[0]*pMat->m[2]) + (In[1]*pMat->m[6]) + (In[2]*pMat->m[10]) + (In[3]*pMat->m[14]);
	pOut4D[3] = (In[0]*pMat->m[3]) + (In[1]*pMat->m[7]) + (In[2]*pMat->m[11]) + (In[3]*pMat->m[15]);
	#endif

}


void SIMDx86Matrix_AlignedVector4MultiplyOf(float* pOut4D, const float* pIn4D, const SIMDx86Matrix* pMat)
{
	#if defined(USE_SSE)
	asm(
	"movaps (%1), %%xmm4\n"
	"movaps %%xmm4, %%xmm5\n"
	"movaps %%xmm4, %%xmm6\n"
	"movaps  %%xmm4, %%xmm7\n"
	"shufps $0x00, %%xmm4, %%xmm4\n"
	"shufps $0x55, %%xmm5, %%xmm5\n"
	"shufps $0xAA, %%xmm6, %%xmm6\n"
	"shufps $0xFF, %%xmm7, %%xmm7\n"

	/* Multiply with each row */
	"mulps   (%0), %%xmm4\n"
	"mulps 16(%0), %%xmm5\n"
	"mulps 32(%0), %%xmm6\n"
	"mulps 48(%0), %%xmm7\n"

	/* Sum results */
	"addps %%xmm4, %%xmm5\n"
	"addps %%xmm6, %%xmm7\n"
	"addps %%xmm5, %%xmm7\n"

	/* Store translated vector */
	"movaps %%xmm7, (%2)\n"
	:
	: "r" (pMat), "r" (pIn4D), "r" (pOut4D)
	);
	#elif defined(USE_3DNOW)

	asm(
	"movd   (%0), %%mm0\n"			/* mm0 = ? | x */
	"movd  4(%0), %%mm2\n"			/* mm2 = ? | y */
	"movd  8(%0), %%mm4\n"			/* mm4 = ? | z */
	"movd 12(%0), %%mm6\n"			/* mm6 = ? | w */
	"punpckldq %%mm0, %%mm0\n"		/* mm0 = x | x */
	"punpckldq %%mm2, %%mm2\n"		/* mm2 = y | y */
	"punpckldq %%mm4, %%mm4\n"		/* mm4 = z | z */
	"punpckldq %%mm6, %%mm6\n"		/* mm6 = w | w */
	"movq %%mm0, %%mm1\n"			/* mm1 = x | x */
	"movq %%mm2, %%mm3\n"			/* mm3 = y | y */
	"movq %%mm4, %%mm5\n"			/* mm5 = z | z */
	"movq %%mm6, %%mm7\n"			/* mm7 = w | w */
	"pfmul   (%1), %%mm0\n"			/* mm0 = x*m[1]  | x*m[0] */
	"pfmul  8(%1), %%mm1\n"			/* mm1 = x*m[3]  | x*m[2] */
	"pfmul 16(%1), %%mm2\n" 		/* mm2 = y*m[5]  | y*m[4] */
	"pfmul 24(%1), %%mm3\n" 		/* mm3 = y*m[7]  | y*m[6] */
	"pfmul 32(%1), %%mm4\n" 		/* mm4 = z*m[9]  | z*m[8] */
	"pfmul 40(%1), %%mm5\n" 		/* mm5 = z*m[11] | z*m[10] */
	"pfmul 48(%1), %%mm6\n" 		/* mm6 = w*m[13] | w*m[12] */
	"pfmul 56(%1), %%mm7\n" 		/* mm7 = w*m[15] | w*m[14] */
	"pfadd %%mm0, %%mm2\n"
	"pfadd %%mm1, %%mm3\n"
	"pfadd %%mm4, %%mm6\n"
	"pfadd %%mm5, %%mm7\n"
	"pfadd %%mm2, %%mm6\n"
	"pfadd %%mm3, %%mm7\n"
	"movq %%mm6,  (%2)\n"
	"movq %%mm7, 8(%2)\n"
	:
	: "r" (pIn4D), "r" (pMat), "r" (pOut4D)
	);

	/* Execute 'femms' if desired */
	#ifndef NO_EMMS
	asm("femms\n");
	#endif

	#else
	pOut4D[0] = (pIn4D[0]*pMat->m[0]) + (pIn4D[1]*pMat->m[4]) + (pIn4D[2]*pMat->m[8]) + (pIn4D[3]*pMat->m[12]);
	pOut4D[1] = (pIn4D[0]*pMat->m[1]) + (pIn4D[1]*pMat->m[5]) + (pIn4D[2]*pMat->m[9]) + (pIn4D[3]*pMat->m[13]);
	pOut4D[2] = (pIn4D[0]*pMat->m[2]) + (pIn4D[1]*pMat->m[6]) + (pIn4D[2]*pMat->m[10]) + (pIn4D[3]*pMat->m[14]);
	pOut4D[3] = (pIn4D[0]*pMat->m[3]) + (pIn4D[1]*pMat->m[7]) + (pIn4D[2]*pMat->m[11]) + (pIn4D[3]*pMat->m[15]);
	#endif
}


void SIMDx86Matrix_AlignedToIdentity(SIMDx86Matrix* pMat)
{
	memset(pMat, 0, sizeof(SIMDx86Matrix));
	pMat->m[0] = pMat->m[5] = pMat->m[10] = pMat->m[15] = 1.0f;
}

void SIMDx86Matrix_AlignedToScale(SIMDx86Matrix* pMat, float x, float y, float z)
{
	memset(pMat, 0, sizeof(SIMDx86Matrix));

	pMat->m[0] = x;
	pMat->m[5] = y;
	pMat->m[10] = z;
	pMat->m[15] = 1.0f;
}

void SIMDx86Matrix_AlignedToScaleOf(SIMDx86Matrix* pMat, const SIMDx86Vector* pVec)
{
	memset(pMat, 0, sizeof(SIMDx86Matrix));

	pMat->m[0] = pVec->x;
	pMat->m[5] = pVec->y;
	pMat->m[10] = pVec->z;
	pMat->m[15] = 1.0f;
}

void SIMDx86Matrix_AlignedToTranslate(SIMDx86Matrix* pMat, float x, float y, float z)
{
	/* Zero out [0]...[11] components */
	memset(pMat->m, 0, sizeof(float) * 12);
	pMat->m[12] = x;
	pMat->m[13] = y;
	pMat->m[14] = z;
	pMat->m[15] = 1.0f;
}

void SIMDx86Matrix_AlignedToTranslateOf(SIMDx86Matrix* pMat, const SIMDx86Vector* pVec)
{
	/* Zero out [0]...[11] components */
	memset(pMat->m, 0, sizeof(float) * 12);
	pMat->m[12] = pVec->x;
	pMat->m[13] = pVec->y;
	pMat->m[14] = pVec->z;
	pMat->m[15] = 1.0f;
}

void SIMDx86Matrix_AlignedToRotate(SIMDx86Matrix* pMat, float yaw, float pitch, float roll)
{
	/* TODO: fsincos 387 instruction?? */
	float cos_yaw = cosf(yaw);
	float sin_yaw = sinf(yaw);
	float cos_pitch = cosf(pitch);
	float sin_pitch = sinf(pitch);
	float cos_roll = cosf(roll);
	float sin_roll = sinf(roll);

	pMat->m[0] = (cos_yaw * cos_pitch);
	pMat->m[1] = (cos_yaw * sin_pitch * sin_roll) - (sin_yaw * cos_roll);
	pMat->m[2] = (cos_yaw * sin_pitch * cos_roll) + (sin_yaw * sin_roll);
	pMat->m[3] = 0.0;

	pMat->m[4] = (sin_yaw * cos_pitch);
	pMat->m[5] = (cos_yaw * cos_roll) + (sin_yaw * sin_pitch * sin_roll);
	pMat->m[6] = (sin_yaw * sin_pitch * cos_roll) - (cos_yaw * sin_roll);
	pMat->m[7] = 0.0;

	pMat->m[8] = -sin_pitch;
	pMat->m[9] = (cos_pitch * sin_roll);
	pMat->m[10] = (cos_pitch * cos_roll);
	pMat->m[11] = 0.0;

	pMat->m[12] = 0.0;
	pMat->m[13] = 0.0;
	pMat->m[14] = 0.0;
	pMat->m[15] = 1.0;
}

void SIMDx86Matrix_AlignedToRotateOf(SIMDx86Matrix* pMat, const SIMDx86Vector* pYawPitchRoll)
{
	/* TODO: fsincos 387 instruction?? */
	float cos_yaw = cosf(pYawPitchRoll->x);
	float sin_yaw = sinf(pYawPitchRoll->x);
	float cos_pitch = cosf(pYawPitchRoll->y);
	float sin_pitch = sinf(pYawPitchRoll->y);
	float cos_roll = cosf(pYawPitchRoll->z);
	float sin_roll = sinf(pYawPitchRoll->z);

	pMat->m[0] = (cos_yaw * cos_pitch);
	pMat->m[1] = (cos_yaw * sin_pitch * sin_roll) - (sin_yaw * cos_roll);
	pMat->m[2] = (cos_yaw * sin_pitch * cos_roll) + (sin_yaw * sin_roll);
	pMat->m[3] = 0.0;

	pMat->m[4] = (sin_yaw * cos_pitch);
	pMat->m[5] = (cos_yaw * cos_roll) + (sin_yaw * sin_pitch * sin_roll);
	pMat->m[6] = (sin_yaw * sin_pitch * cos_roll) - (cos_yaw * sin_roll);
	pMat->m[7] = 0.0;

	pMat->m[8] = -sin_pitch;
	pMat->m[9] = (cos_pitch * sin_roll);
	pMat->m[10] = (cos_pitch * cos_roll);
	pMat->m[11] = 0.0;

	pMat->m[12] = 0.0;
	pMat->m[13] = 0.0;
	pMat->m[14] = 0.0;
	pMat->m[15] = 1.0;
}

SIMDx86Matrix* SIMDx86Matrix_AlignedInverse(SIMDx86Matrix* pMat)
{
	SIMDx86Matrix temp;

	/* Calculate the 2x2 submatrix determinates */
	float det01 = pMat->m[6] * pMat->m[11] - pMat->m[7] * pMat->m[10];
	float det02 = pMat->m[5] * pMat->m[11] - pMat->m[7] * pMat->m[9];
	float det03 = pMat->m[5] * pMat->m[10] - pMat->m[6] * pMat->m[9];
	float det04 = pMat->m[4] * pMat->m[11] - pMat->m[7] * pMat->m[8];
	float det05 = pMat->m[4] * pMat->m[10] - pMat->m[6] * pMat->m[8];
	float det06 = pMat->m[4] * pMat->m[9] - pMat->m[5] * pMat->m[8];
	float det07;
	float det08;
	float det09;
	float det10;
	float det11;
	float det12;
	float det13;
	float det14;
	float det15;
	float det16;
	float det17;
	float det18;
	float det19;
	float det20;
	float det21;
	float det22;
	float det23;
	float det24;
	float det;

	det = -pMat->m[12] * (pMat->m[1] * det01 - pMat->m[2] * det02 + pMat->m[3] * det03) + pMat->m[13] * (pMat->m[0] * det01 - pMat->m[2] * det04 + pMat->m[3] * det05) - pMat->m[14] * (pMat->m[0] * det02 - pMat->m[1] * det04 + pMat->m[3] * det06) + pMat->m[15] * (pMat->m[0] * det03 - pMat->m[1] * det05 + pMat->m[2] * det06);

	/* If determinate is zero, then the matrix is singular (non-inversable) */
	if(det == 0.0f)
	    return NULL;

	/* Calculate the rest of the cofactors */
	det07 = pMat->m[10] * pMat->m[15] - pMat->m[11] * pMat->m[14];
	det08 = pMat->m[11] * pMat->m[13] - pMat->m[9] * pMat->m[15];
	det09 = pMat->m[9] * pMat->m[14] - pMat->m[10] * pMat->m[13];
	det10 = pMat->m[2] * pMat->m[15] - pMat->m[3] * pMat->m[14];
	det11 = pMat->m[3] * pMat->m[13] - pMat->m[1] * pMat->m[15];
	det12 = pMat->m[1] * pMat->m[14] - pMat->m[2] * pMat->m[13];
	det13 = pMat->m[2] * pMat->m[7] - pMat->m[3] * pMat->m[6];
	det14 = pMat->m[3] * pMat->m[5] - pMat->m[1] * pMat->m[7];
	det15 = pMat->m[1] * pMat->m[6] - pMat->m[2] * pMat->m[5];
	det16 = pMat->m[8] * pMat->m[15] - pMat->m[11] * pMat->m[12];
	det17 = pMat->m[10] * pMat->m[12] - pMat->m[8] * pMat->m[14];
	det18 = pMat->m[0] * pMat->m[15] - pMat->m[3] * pMat->m[12];
	det19 = pMat->m[2] * pMat->m[12] - pMat->m[0] * pMat->m[14];
	det20 = pMat->m[0] * pMat->m[7] - pMat->m[3] * pMat->m[4];
	det21 = pMat->m[2] * pMat->m[4] - pMat->m[0] * pMat->m[6];
	det22 = pMat->m[8] * pMat->m[13] - pMat->m[9] * pMat->m[12];
	det23 = pMat->m[0] * pMat->m[13] - pMat->m[1] * pMat->m[12];
	det24 = pMat->m[0] * pMat->m[5] - pMat->m[1] * pMat->m[4];


	memcpy(&temp, pMat, sizeof(SIMDx86Matrix));

	pMat->m[0] = det * (temp.m[5] * det07 + temp.m[6] * det08 + temp.m[7] * det09);
	pMat->m[1] = det * (temp.m[9] * det10 + temp.m[10] * det11 + temp.m[11] * det12);
	pMat->m[2] = det * (temp.m[13] * det13 + temp.m[14] * det14 + temp.m[15] * det15);
	pMat->m[3] = det * (temp.m[1] * -det01 + temp.m[2] * det02 + temp.m[3] * -det03);

	pMat->m[4] = det * (temp.m[6] * det16 + temp.m[7] * det17 - temp.m[4] * det07);
	pMat->m[5] = det * (temp.m[10] * det18 + temp.m[11] * det19 - temp.m[8] * det10);
	pMat->m[6] = det * (temp.m[14] * det20 + temp.m[15] * det21 - temp.m[12] * det13);
	pMat->m[7] = det * (temp.m[2] * -det04 + temp.m[3] * det05 + temp.m[0] * det01);

	pMat->m[8] = det * (temp.m[7] * det22 - temp.m[4] * det08 - temp.m[5] * det16);
	pMat->m[9] = det * (temp.m[11] * det23 - temp.m[8] * det11 - temp.m[9] * det18);
	pMat->m[10] = det * (temp.m[15] * det24 - temp.m[12] * det14 - temp.m[13] * det20);
	pMat->m[11] = det * (temp.m[3] * -det06 + temp.m[0] * -det02 + temp.m[1] * det04);

	pMat->m[12] = det * (temp.m[4] * -det09 - temp.m[5] * det17 - temp.m[6] * det22);
	pMat->m[13] = det * (temp.m[8] * -det12 - temp.m[9] * det19 - temp.m[10] * det23);
	pMat->m[14] = det * (temp.m[12] * -det15 - temp.m[13] * det21 - temp.m[14] * det24);
	pMat->m[15] = det * (temp.m[0] * det03 + temp.m[1] * -det05 + temp.m[2] * det06);


	return pMat;
}

SIMDx86Matrix* SIMDx86Matrix_AlignedInverseOf(SIMDx86Matrix* pOut, const SIMDx86Matrix* pIn)
{
	/* Calculate the 2x2 submatrix determinates */
	float det01 = pIn->m[6] * pIn->m[11] - pIn->m[7] * pIn->m[10];
	float det02 = pIn->m[5] * pIn->m[11] - pIn->m[7] * pIn->m[9];
	float det03 = pIn->m[5] * pIn->m[10] - pIn->m[6] * pIn->m[9];
	float det04 = pIn->m[4] * pIn->m[11] - pIn->m[7] * pIn->m[8];
	float det05 = pIn->m[4] * pIn->m[10] - pIn->m[6] * pIn->m[8];
	float det06 = pIn->m[4] * pIn->m[9] - pIn->m[5] * pIn->m[8];
	float det07;
	float det08;
	float det09;
	float det10;
	float det11;
	float det12;
	float det13;
	float det14;
	float det15;
	float det16;
	float det17;
	float det18;
	float det19;
	float det20;
	float det21;
	float det22;
	float det23;
	float det24;
	float det;

	det = -pIn->m[12] * (pIn->m[1] * det01 - pIn->m[2] * det02 + pIn->m[3] * det03) + pIn->m[13] * (pIn->m[0] * det01 - pIn->m[2] * det04 + pIn->m[3] * det05) - pIn->m[14] * (pIn->m[0] * det02 - pIn->m[1] * det04 + pIn->m[3] * det06) + pIn->m[15] * (pIn->m[0] * det03 - pIn->m[1] * det05 + pIn->m[2] * det06);

	/* If determinate is zero, then the matrix is singular (non-inversable) */
	if(det == 0.0f)
	    return NULL;

	/* Calculate the rest of the cofactors */
	det07 = pIn->m[10] * pIn->m[15] - pIn->m[11] * pIn->m[14];
	det08 = pIn->m[11] * pIn->m[13] - pIn->m[9] * pIn->m[15];
	det09 = pIn->m[9] * pIn->m[14] - pIn->m[10] * pIn->m[13];
	det10 = pIn->m[2] * pIn->m[15] - pIn->m[3] * pIn->m[14];
	det11 = pIn->m[3] * pIn->m[13] - pIn->m[1] * pIn->m[15];
	det12 = pIn->m[1] * pIn->m[14] - pIn->m[2] * pIn->m[13];
	det13 = pIn->m[2] * pIn->m[7] - pIn->m[3] * pIn->m[6];
	det14 = pIn->m[3] * pIn->m[5] - pIn->m[1] * pIn->m[7];
	det15 = pIn->m[1] * pIn->m[6] - pIn->m[2] * pIn->m[5];
	det16 = pIn->m[8] * pIn->m[15] - pIn->m[11] * pIn->m[12];
	det17 = pIn->m[10] * pIn->m[12] - pIn->m[8] * pIn->m[14];
	det18 = pIn->m[0] * pIn->m[15] - pIn->m[3] * pIn->m[12];
	det19 = pIn->m[2] * pIn->m[12] - pIn->m[0] * pIn->m[14];
	det20 = pIn->m[0] * pIn->m[7] - pIn->m[3] * pIn->m[4];
	det21 = pIn->m[2] * pIn->m[4] - pIn->m[0] * pIn->m[6];
	det22 = pIn->m[8] * pIn->m[13] - pIn->m[9] * pIn->m[12];
	det23 = pIn->m[0] * pIn->m[13] - pIn->m[1] * pIn->m[12];
	det24 = pIn->m[0] * pIn->m[5] - pIn->m[1] * pIn->m[4];

	pOut->m[0] = det * (pIn->m[5] * det07 + pIn->m[6] * det08 + pIn->m[7] * det09);
	pOut->m[1] = det * (pIn->m[9] * det10 + pIn->m[10] * det11 + pIn->m[11] * det12);
	pOut->m[2] = det * (pIn->m[13] * det13 + pIn->m[14] * det14 + pIn->m[15] * det15);
	pOut->m[3] = det * (pIn->m[1] * -det01 + pIn->m[2] * det02 + pIn->m[3] * -det03);

	pOut->m[4] = det * (pIn->m[6] * det16 + pIn->m[7] * det17 - pIn->m[4] * det07);
	pOut->m[5] = det * (pIn->m[10] * det18 + pIn->m[11] * det19 - pIn->m[8] * det10);
	pOut->m[6] = det * (pIn->m[14] * det20 + pIn->m[15] * det21 - pIn->m[12] * det13);
	pOut->m[7] = det * (pIn->m[2] * -det04 + pIn->m[3] * det05 + pIn->m[0] * det01);

	pOut->m[8] = det * (pIn->m[7] * det22 - pIn->m[4] * det08 - pIn->m[5] * det16);
	pOut->m[9] = det * (pIn->m[11] * det23 - pIn->m[8] * det11 - pIn->m[9] * det18);
	pOut->m[10] = det * (pIn->m[15] * det24 - pIn->m[12] * det14 - pIn->m[13] * det20);
	pOut->m[11] = det * (pIn->m[3] * -det06 + pIn->m[0] * -det02 + pIn->m[1] * det04);

	pOut->m[12] = det * (pIn->m[4] * -det09 - pIn->m[5] * det17 - pIn->m[6] * det22);
	pOut->m[13] = det * (pIn->m[8] * -det12 - pIn->m[9] * det19 - pIn->m[10] * det23);
	pOut->m[14] = det * (pIn->m[12] * -det15 - pIn->m[13] * det21 - pIn->m[14] * det24);
	pOut->m[15] = det * (pIn->m[0] * det03 + pIn->m[1] * -det05 + pIn->m[2] * det06);
	return pOut;
}
