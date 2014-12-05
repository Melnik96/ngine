; math_sse2.asm -- SSE2 accelerated math functions
; Written by Patrick Baggett, 2005 (baggett.patrick@gmail.com)
; Under LGPL License
; Part of SIMDx86 Project


%include "SIMDx86asm.inc"

;List of symbols this module provides
EXPORT_SYMBOL(SIMDx86_sqrt_SSE2)
EXPORT_SYMBOL(SIMDx86_rsqrt_SSE2)


EXTERN _SIMDx86_double_one	;Required for SIMDx86_rsqrt_SSE2
EXTERN _SIMDx86_float_one	;Required for SIMDx86_rsqrtf_SSE

;Minor optimizations
;movlpd instead of movsd -- Doesn't clear up 64 bits. Apparently this results in 1 less latency

section .text
BEGIN_SYMBOL(SIMDx86_sqrt_SSE2)
	movlpd xmm0, [esp+4]		;xmm0 = value. movlpd is faster than movsd since it doesn't clear upper register half (64 bits)
	sqrtsd xmm0, xmm0			;xmm0 = sqrt(value)
	movlpd [esp-4], xmm0
	fld dword [esp-4]
	ret
END_SYMBOL(SIMDx86_sqrt_SSE2)
SIZE_SYMBOL SIMDx86_sqrt_SSE2

;SIMDx86_rsqrt() -DUSE_SSE>=2
BEGIN_SYMBOL(SIMDx86_rsqrt_SSE2)
	movlpd xmm0, [esp+4]					;xmm0 = value
	movapd xmm1, [_SIMDx86_double_one]		;xmm1 = 1.0
	sqrtsd xmm0, xmm0						;xmm0 = sqrt(value)
	divsd xmm1, xmm0						;xmm1 = 1.0 / sqrt(value)
	movlpd [esp-4], xmm1
	fld dword [esp-4]
	ret
END_SYMBOL(SIMDx86_rsqrt_SSE2)
SIZE_SYMBOL SIMDx86_rsqrt_SSE2