; matrix_sse.asm -- SSE accelerated matrix code
; Written by Patrick Baggett, 2006 (baggett.patrick@gmail.com)
; Under LGPL License
; Part of SIMDx86 Project

%include "SIMDx86asm.inc"

;List of symbols this module provides
EXPORT_SYMBOL(SIMDx86Matrix_Sum_SSE)
EXPORT_SYMBOL(SIMDx86Matrix_SumOf_SSE)
EXPORT_SYMBOL(SIMDx86Matrix_Diff_SSE)
EXPORT_SYMBOL(SIMDx86Matrix_DiffOf_SSE)
EXPORT_SYMBOL(SIMDx86Matrix_Scale_SSE);



;TODO:
; * Check if interleaving movaps/subps or addps/movaps improves performance -> code was converted from movups,
; which has different performance implications.

BEGIN_SYMBOL(SIMDx86Matrix_Sum_SSE) ;void SIMDx86Matrix_Sum(SIMDx86Matrix* Out, const SIMDx86Matrix* In)
	mov eax, [esp+4]	;eax = Out
	mov edx, [esp+8]	;edx = In
	movaps xmm0, [eax]		;xmm0 = Out[0..3]
	movaps xmm1, [eax+16]	;xmm1 = Out[4..7]
	movaps xmm2, [eax+32]	;xmm2 = Out[8..11]
	movaps xmm3, [eax+48]	;xmm3 = Out[12..15]
	addps xmm0, [edx]		;xmm0 = In[0..3] + Out[0..3]
	addps xmm1, [edx+16]	;xmm1 = In[4..7] + Out[4..7]
	addps xmm2, [edx+32]	;xmm2 = In[8..11] + Out[8..11]
	addps xmm3, [edx+48]	;xmm3 = In[12..15] + Out[12..15]
	movaps [eax], xmm0		;Store sum...
	movaps [eax+16], xmm1
	movaps [eax+32], xmm2
	movaps [eax+48], xmm3
	ret
END_SYMBOL(SIMDx86Matrix_Sum_SSE)
SIZE_SYMBOL SIMDx86Matrix_Sum_SSE

BEGIN_SYMBOL(SIMDx86Matrix_SumOf_SSE) ;void SIMDx86Matrix_SumOf(SIMDx86Matrix* Out, const SIMDx86Matrix* In1, const SIMDx86Matrix* In2)
	mov ecx, [esp+4]	;ecx = Out
	mov eax, [esp+8]	;eax = In1
	mov edx, [esp+12]	;edx = In2
	movaps xmm0, [eax]		;xmm0 = In1[0..3]
	movaps xmm1, [eax+16]	;xmm1 = In1[4..7]
	movaps xmm2, [eax+32]	;xmm2 = In1[8..11]
	movaps xmm3, [eax+48]	;xmm3 = In1[12..15]
	addps xmm0, [edx]		;xmm0 = In1[0..3] + In2[0..3]
	addps xmm1, [edx+16]	;xmm1 = In1[4..7] + In2[4..7]
	addps xmm2, [edx+32]	;xmm2 = In1[8..11] + In2[8..11]
	addps xmm3, [edx+48]	;xmm3 = In1[12..15] + In2[12..15]
	movaps [ecx], xmm0		;Store sum into Out
	movaps [ecx+16], xmm1
	movaps [ecx+32], xmm2
	movaps [ecx+48], xmm3
	ret
END_SYMBOL(SIMDx86Matrix_SumOf_SSE)
SIZE_SYMBOL SIMDx86Matrix_SumOf_SSE

BEGIN_SYMBOL(SIMDx86Matrix_Diff_SSE) ;void SIMDx86Matrix_Diff(SIMDx86Matrix* Out, const SIMDx86Matrix* In)
	mov eax, [esp+4]	;eax = Out
	mov edx, [esp+8]	;edx = In
	movaps xmm0, [eax]		;xmm0 = Out[0..3]
	movaps xmm1, [eax+16]	;xmm1 = Out[4..7]
	movaps xmm2, [eax+32]	;xmm2 = Out[8..11]
	movaps xmm3, [eax+48]	;xmm3 = Out[12..15]
	subps xmm0, [edx]		;xmm0 = Out[0..3] - In[0..3]
	subps xmm1, [edx+16]	;xmm1 = Out[4..7] - In[4..7]
	subps xmm2, [edx+32]	;xmm2 = Out[8..11] - In[8..11] 
	subps xmm3, [edx+48]	;xmm3 = Out[12..15] - In[12..15]
	movaps [eax], xmm0		;Store difference...
	movaps [eax+16], xmm1
	movaps [eax+32], xmm2
	movaps [eax+48], xmm3
	ret
END_SYMBOL(SIMDx86Matrix_Diff_SSE)
SIZE_SYMBOL SIMDx86Matrix_Diff_SSE


BEGIN_SYMBOL(SIMDx86Matrix_DiffOf_SSE) ;void SIMDx86Matrix_DiffOf(SIMDx86Matrix* Out, const SIMDx86Matrix* In1, const SIMDx86Matrix* In2)
	mov ecx, [esp+4]	;ecx = Out
	mov eax, [esp+8]	;eax = In1
	mov edx, [esp+12]	;edx = In2
	movaps xmm0, [eax]		;xmm0 = In1[0..3]
	movaps xmm1, [eax+16]	;xmm1 = In1[4..7]
	movaps xmm2, [eax+32]	;xmm2 = In1[8..11]
	movaps xmm3, [eax+48]	;xmm3 = In1[12..15]
	subps xmm0, [edx]		;xmm0 = In1[0..3] - In2[0..3]
	subps xmm1, [edx+16]	;xmm1 = In1[4..7] - In2[4..7]
	subps xmm2, [edx+32]	;xmm2 = In1[8..11] - In2[8..11]
	subps xmm3, [edx+48]	;xmm3 = In1[12..15] - In2[12..15]
	movaps [ecx], xmm0		;Store difference into Out
	movaps [ecx+16], xmm1
	movaps [ecx+32], xmm2
	movaps [ecx+48], xmm3
	ret
END_SYMBOL(SIMDx86Matrix_DiffOf_SSE)
SIZE_SYMBOL SIMDx86Matrix_DiffOf_SSE

;TODO: The matrix scaling might be faster if we do shufps first then movaps/mulps/movaps triplets and let out
; of order execution execute what can be executed in parallel. MULPS as a repeat latency that is worth trying to hide
; if possible.

BEGIN_SYMBOL(SIMDx86Matrix_Scale_SSE) ;void SIMDx86Matrix_Scale(SIMDx86Matrix* mtx, float scalar)
	mov eax, [esp+4]
	movss xmm4, [esp+8]

	/* Get the matrix into registers */
	movaps xmm0, [eax]		;xmm0 = m[0..3]
	movaps xmm1, [eax+16]		;xmm1 = m[4..7]
	shufps xmm4, xmm4, 0x00		;xmm4 = s | s | s | s
	movaps xmm2, [eax+32]		;xmm2 = m[8..11]
	movaps xmm3, [eax+48]		;xmm3 = m[12..15]
	
	/* Scale the matrix in parallel */
	mulps xmm0, xmm4
	mulps xmm1, xmm4
	mulps xmm2, xmm4
	mulps xmm3, xmm4

	/* Store results */
	movaps [eax], xmm0
	movaps [eax+16], xmm1
	movaps [eax+32], xmm2
	movaps [eax+48], xmm3
END_SYMBOL(SIMDx86Matrix_Scale_SSE)
SIZE_SYMBOL SIMDx86Matrix_Scale_SSE
