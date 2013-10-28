; math_3dnow.asm -- 3DNow! accelerated math functions
; Written by Patrick Baggett, 2006 (baggett.patrick@gmail.com)
; Under LGPL License
; Part of SIMDx86 Project


%include "SIMDx86asm.inc"

;List of symbols this module provides
EXPORT_SYMBOL(SIMDx86_sqrtf_HIPREC_3DNow)
EXPORT_SYMBOL(SIMDx86_sqrtf_3DNow)
EXPORT_SYMBOL(SIMDx86_rsqrtf_HIPREC_3DNow)
EXPORT_SYMBOL(SIMDx86_rsqrtf_3DNow)

section .text

;SIMDx86_sqrtf() -- HIPREC USE_3DNOW>=1
BEGIN_SYMBOL(SIMDx86_sqrtf_HIPREC_3DNow)
	movd mm0, [esp+4]	;mm0 = 0 | value
	pfrsqrt mm1, mm0	;mm1 = 1/sqrtf(value) (approx) | 1/sqrtf(value) (approx)
	movq mm1, mm2		;mm2 = mm1 = 1/sqrtf(value) | 1/sqrtf(value)
	pfmul mm1, mm1		;mm1 = x0*x0 | x0*x0
	punpckldq mm0, mm0	;mm0 = value | value
	pfrsqit1 mm1, mm0	;mm1 = intermediate
	pfrcpit2 mm2, mm1	;mm2 = 1/sqrtf(value) (exact) | 1/sqrtf(value) (exact)
	pfmul mm0, mm2		;mm0 = sqrtf(value)
	movd [esp-4], mm0	;tmp = sqrtf(value)
	femms
	fld dword [esp-4]
	ret
END_SYMBOL(SIMDx86_sqrtf_HIPREC_3DNow)
SIZE_SYMBOL SIMDx86_sqrtf_HIPREC_3DNow

;SIMDx86_sqrtf() -- USE_3DNOW>=1
BEGIN_SYMBOL(SIMDx86_sqrtf_3DNow)
	movd mm0, [esp+4]
	pfrsqrt mm1, mm0
	pfmul mm1, mm0
	movd [esp-4], mm0
	femms
	fld dword [esp-4]
	ret
END_SYMBOL(SIMDx86_sqrtf_3DNow)
SIZE_SYMBOL SIMDx86_sqrtf_3DNow

; SIMDx86_rsqrtf()-- HIPREC USE_3DNOW>=1
BEGIN_SYMBOL(SIMDx86_rsqrtf_HIPREC_3DNow)
	movd mm0, [esp+4]
	pfrsqrt mm1, mm0
	movq mm2, mm1
	pfmul mm1, mm1
	punpckldq mm0, mm0
	pfrsqit1 mm1, mm0
	pfrcpit2 mm2, mm2
	movd [esp-4], mm2
	femms
	fld dword [esp-4]
	ret
END_SYMBOL(SIMDx86_rsqrtf_HIPREC_3DNow)
SIZE_SYMBOL SIMDx86_rsqrtf_HIPREC_3DNow

;SIMDx86_rsqrtf() -- USE_3DNOW>=1
BEGIN_SYMBOL(SIMDx86_rsqrtf_3DNow)
	movd mm0, [esp+4]
	pfrsqrt mm0, mm0
	movd [esp-4], mm0
	femms
	fld dword [esp-4]
	ret
END_SYMBOL(SIMDx86_rsqrtf_3DNow)
SIZE_SYMBOL SIMDx86_rsqrtf_3DNow