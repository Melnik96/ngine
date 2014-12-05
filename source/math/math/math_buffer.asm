; math_buffer.asm -- NULL buffer space for functions
; Written by Patrick Baggett, 2006 (baggett.patrick@gmail.com)
; Under LGPL License
; Part of SIMDx86 Project


%include "SIMDx86asm.inc"

EXPORT_SYMBOL(SIMDx86_sqrtf)
EXPORT_SYMBOL(SIMDx86_rsqrtf)
EXPORT_SYMBOL(SIMDx86_sqrt)
EXPORT_SYMBOL(SIMDx86_rsqrt)

section .text

BEGIN_SYMBOL(SIMDx86_sqrtf)
	times OVERLAY_SIZE_MEDIUM db 0xc9

BEGIN_SYMBOL(SIMDx86_rsqrtf)
	times OVERLAY_SIZE_MEDIUM db 0xc9

BEGIN_SYMBOL(SIMDx86_sqrt)
	times OVERLAY_SIZE_MEDIUM db 0xc9

BEGIN_SYMBOL(SIMDx86_rsqrt)
	times OVERLAY_SIZE_MEDIUM db 0xc9
