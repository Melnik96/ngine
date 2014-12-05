; math_sse.asm -- SSE accelerated math functions
; Written by Patrick Baggett, 2005 (baggett.patrick@gmail.com)
; Under LGPL License
; Part of SIMDx86 Project


%include "SIMDx86asm.inc"


;List of symbols this module provides
EXPORT_SYMBOL(SIMDx86_sqrtf_HIPREC_SSE)
EXPORT_SYMBOL(SIMDx86_sqrtf_SSE)
EXPORT_SYMBOL(SIMDx86_rsqrtf_HIPREC_SSE)
EXPORT_SYMBOL(SIMDx86_rsqrtf_SSE)

EXTERN _SIMDx86_double_one	;Required for SIMDx86_rsqrt_SSE2
EXTERN _SIMDx86_float_one	;Required for SIMDx86_rsqrtf_SSE

;Minor optimizations
;movlps instead of movss -- Has 2 latency compared to 3 on movss. Does not interferec with addss/mulss pipes. When reading stack, I know it will not GPF

section .text

BEGIN_SYMBOL(SIMDx86_sqrtf_HIPREC_SSE)
	movlps xmm0, [esp+4]	;xmm0 = value
	sqrtss xmm0, xmm0		;xmm0 = sqrtf(value)
	movss [esp-4],xmm0
	fld dword [esp-4]
	ret						;return sqrt(value)
END_SYMBOL(SIMDx86_sqrtf_HIPREC_SSE)
SIZE_SYMBOL SIMDx86_sqrtf_HIPREC_SSE

BEGIN_SYMBOL(SIMDx86_sqrtf_SSE)
	movlps xmm0, [esp+4]	;xmm0 = value
	rsqrtss xmm0, xmm0		;xmm0 = rsqrtf(value) (approx)
	rcpss xmm0, xmm0		;xmm0 = 1.0 / rsqrtf(value)	(approx)
	movss [esp-4], xmm0
	fld dword [esp-4]
	ret						;return 1.0 / rsqrtf(value) (approx)
END_SYMBOL(SIMDx86_sqrtf_SSE)
SIZE_SYMBOL SIMDx86_sqrtf_SSE

BEGIN_SYMBOL(SIMDx86_rsqrtf_HIPREC_SSE)
	movlps xmm0, [esp+4]
	movaps xmm1, [_SIMDx86_float_one]
	sqrtss xmm0, xmm0
	divss xmm1, xmm0
	movss [esp-4], xmm1
	fld dword [esp-4]
	ret
END_SYMBOL(SIMDx86_rsqrtf_HIPREC_SSE)
SIZE_SYMBOL SIMDx86_rsqrtf_HIPREC_SSE

BEGIN_SYMBOL(SIMDx86_rsqrtf_SSE)
	movlps xmm0, [esp+4]
	rsqrtss xmm0, xmm0
	movss [esp-4], xmm0
	fld dword [esp-4]
	ret
END_SYMBOL(SIMDx86_rsqrtf_SSE)
SIZE_SYMBOL SIMDx86_rsqrtf_SSE
