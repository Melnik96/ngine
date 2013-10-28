; math_387.asm -- Standard 387 FPU functions
; Written by Patrick Baggett, 2006 (baggett.patrick@gmail.com)
; Under LGPL License
; Part of SIMDx86 Project


%include "SIMDx86asm.inc"

;List of symbols this module provides
EXPORT_SYMBOL(SIMDx86_sqrtf_387)
EXPORT_SYMBOL(SIMDx86_rsqrtf_387)
EXPORT_SYMBOL(SIMDx86_sqrt_387)
EXPORT_SYMBOL(SIMDx86_rsqrt_387)


; Local variables
singlefp_one:
	dd 1.0
doublefp_one:
	dq 1.0


section .text

;SIMDx86_sqrtf() -- Generic 387
BEGIN_SYMBOL(SIMDx86_sqrtf_387)
	fld dword [esp+4]
	fsqrt
	ret
END_SYMBOL(SIMDx86_sqrtf_387)
SIZE_SYMBOL SIMDx86_sqrtf_387

; SIMDx86_rsqrtf() -- Generic 387
BEGIN_SYMBOL(SIMDx86_rsqrtf_387)
	fld dword [esp+4]
	fsqrt
	fdivr dword [singlefp_one]
	ret
END_SYMBOL(SIMDx86_rsqrtf_387)
SIZE_SYMBOL SIMDx86_rsqrtf_387

; SIMDx86_sqrt() -- Generic 387
BEGIN_SYMBOL(SIMDx86_sqrt_387)
	fld qword [esp+4]		; st0 = value
	fsqrt					; st0 = sqrt(value)
	ret
END_SYMBOL(SIMDx86_sqrt_387)
SIZE_SYMBOL SIMDx86_sqrt_387


; SIMDx86_rsqrt() -- Generic 387
BEGIN_SYMBOL(SIMDx86_rsqrt_387)
	fld qword [esp+4]
	fsqrt
	fdivr qword [doublefp_one]
	ret
END_SYMBOL(SIMDx86_rsqrt_387)
SIZE_SYMBOL SIMDx86_rsqrt_387
