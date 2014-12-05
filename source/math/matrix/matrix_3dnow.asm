; matrix_3dnow.asm -- 3DNow! accelerated matrix code
; Written by Patrick Baggett, 2006 (baggett.patrick@gmail.com)
; Under LGPL License
; Part of SIMDx86 Project

%include "SIMDx86asm.inc"

;List of symbols this module provides
EXPORT_SYMBOL(SIMDx86Matrix_Sum_3DNow)
EXPORT_SYMBOL(SIMDx86Matrix_SumOf_3DNow)
EXPORT_SYMBOL(SIMDx86Matrix_Diff_3DNow)
EXPORT_SYMBOL(SIMDx86Matrix_DiffOf_3DNow)
EXPORT_SYMBOL(SIMDx86Matrix_Scale_3DNow)

BEGIN_SYMBOL(SIMDx86Matrix_Sum_3DNow) ;void SIMDx86Matrix_Sum(SIMDx86Matrix* Out, const SIMDx86Matrix* In)
	mov eax, [esp+4]
	mov edx, [esp+8]
	movq mm0, [eax]
	movq mm1, [eax+8]
	movq mm2, [eax+16]
	movq mm3, [eax+24]
	movq mm4, [eax+32]
	movq mm5, [eax+40]
	movq mm6, [eax+48]
	movq mm7, [eax+56]
	pfadd mm0, [edx]
	pfadd mm1, [edx+8]
	pfadd mm2, [edx+16]
	pfadd mm3, [edx+24]
	pfadd mm4, [edx+32]
	pfadd mm5, [edx+40]
	pfadd mm6, [edx+48]
	pfadd mm7, [edx+56]
	movq [eax], mm0
	movq [eax+8], mm1
	movq [eax+16], mm2
	movq [eax+24], mm3
	movq [eax+32], mm4
	movq [eax+40], mm5
	movq [eax+48], mm6
	movq [eax+56], mm7
	femms
	ret
END_SYMBOL(SIMDx86Matrix_Sum_3DNow)
SIZE_SYMBOL SIMDx86Matrix_Sum_3DNow

BEGIN_SYMBOL(SIMDx86Matrix_SumOf_3DNow) ;void SIMDx86Matrix_SumOf(SIMDx86Matrix* Out, const SIMDx86Matrix* In1, const SIMDx86Matrix* In2)
	mov ecx, [esp+4]
	mov eax, [esp+8]
	mov edx, [esp+12]
	movq mm0, [eax]
	movq mm1, [eax+8]
	movq mm2, [eax+16]
	movq mm3, [eax+24]
	movq mm4, [eax+32]
	movq mm5, [eax+40]
	movq mm6, [eax+48]
	movq mm7, [eax+56]
	pfadd mm0, [edx]
	pfadd mm1, [edx+8]
	pfadd mm2, [edx+16]
	pfadd mm3, [edx+24]
	pfadd mm4, [edx+32]
	pfadd mm5, [edx+40]
	pfadd mm6, [edx+48]
	pfadd mm7, [edx+56]
	movq [ecx], mm0
	movq [ecx+8], mm1
	movq [ecx+16], mm2
	movq [ecx+24], mm3
	movq [ecx+32], mm4
	movq [ecx+40], mm5
	movq [ecx+48], mm6
	movq [ecx+56], mm7
	femms
	ret
END_SYMBOL(SIMDx86Matrix_SumOf_3DNow)
SIZE_SYMBOL SIMDx86Matrix_SumOf_3DNow

BEGIN_SYMBOL(SIMDx86Matrix_Diff_3DNow) ;void SIMDx86Matrix_Diff(SIMDx86Matrix* Out, const SIMDx86Matrix* In)
	mov eax, [esp+4]
	mov edx, [esp+8]
	movq mm0, [eax]
	movq mm1, [eax+8]
	movq mm2, [eax+16]
	movq mm3, [eax+24]
	movq mm4, [eax+32]
	movq mm5, [eax+40]
	movq mm6, [eax+48]
	movq mm7, [eax+56]
	pfsub mm0, [edx]
	pfsub mm1, [edx+8]
	pfsub mm2, [edx+16]
	pfsub mm3, [edx+24]
	pfsub mm4, [edx+32]
	pfsub mm5, [edx+40]
	pfsub mm6, [edx+48]
	pfsub mm7, [edx+56]
	movq [eax], mm0
	movq [eax+8], mm1
	movq [eax+16], mm2
	movq [eax+24], mm3
	movq [eax+32], mm4
	movq [eax+40], mm5
	movq [eax+48], mm6
	movq [eax+56], mm7
	femms
	ret
END_SYMBOL(SIMDx86Matrix_Diff_3DNow)
SIZE_SYMBOL SIMDx86Matrix_Diff_3DNow

BEGIN_SYMBOL(SIMDx86Matrix_DiffOf_3DNow) ;void SIMDx86Matrix_DiffOf(SIMDx86Matrix* Out, const SIMDx86Matrix* In1, const SIMDx86Matrix* In2)
	mov ecx, [esp+4]
	mov eax, [esp+8]
	mov edx, [esp+12]
	movq mm0, [eax]
	movq mm1, [eax+8]
	movq mm2, [eax+16]
	movq mm3, [eax+24]
	movq mm4, [eax+32]
	movq mm5, [eax+40]
	movq mm6, [eax+48]
	movq mm7, [eax+56]
	pfsub mm0, [edx]
	pfsub mm1, [edx+8]
	pfsub mm2, [edx+16]
	pfsub mm3, [edx+24]
	pfsub mm4, [edx+32]
	pfsub mm5, [edx+40]
	pfsub mm6, [edx+48]
	pfsub mm7, [edx+56]
	movq [ecx], mm0
	movq [ecx+8], mm1
	movq [ecx+16], mm2
	movq [ecx+24], mm3
	movq [ecx+32], mm4
	movq [ecx+40], mm5
	movq [ecx+48], mm6
	movq [ecx+56], mm7
	femms
	ret
END_SYMBOL(SIMDx86Matrix_DiffOf_3DNow)
SIZE_SYMBOL SIMDx86Matrix_DiffOf_3DNow

BEGIN_SYMBOL(SIMDx86Matrix_Scale_3DNow) ;void SIMDx86Matrix_Scale(SIMDx86Matrix* mtx, float scalar)
	mov eax, [esp+4]
	
	movd mm0, [esp+8]
	punpckldq mm0, mm0

	;Attempt to make use of pipelined operations...
	;Duplicate, begin multiply, and duplicate again, write result of first multiply
	movq mm1, mm0
	pfmul mm1, [eax+8]
	movq mm2, mm0
	movq [eax+8], mm1
	pfmul mm2, [eax+16]
	movq mm3, mm0
	movq [eax+16], mm2
	pfmul mm3, [eax+24]
	movq mm4, mm0
	movq [eax+24], mm3
	pfmul mm4, [eax+32]
	movq mm5, mm0
	movq [eax+32], mm4
	pfmul mm5, [eax+40]
	movq mm6, mm0
	movq [eax+40], mm5
	pfmul mm6, [eax+48]
	movq mm7, mm0
	pfmul mm0, [eax]
	movq [eax+48], mm6	
	pfmul mm7, [eax+56]
	movq [eax], mm0
	movq [eax+56], mm7


	femms
	ret
END_SYMBOL(SIMDx86Matrix_Scale_3DNow)
SIZE_SYMBOL SIMDx86Matrix_Scale_3DNow
