; emms.asm -- (Fast) Entry/Exit MultiMedia State
; Written by Patrick Baggett, 2006 (baggett.patrick@gmail.com)
; Under LGPL License
; Part of SIMDx86 Project


%include "SIMDx86asm.inc"

; There is no good reason we couldn't just have a #define in the header for f/emms (as we did at one time),
; but again, this inline assembly code keeps tripping up different compilers. Thus, these are out-of-line for portability.

section .text

EXPORT_SYMBOL(SIMDx86_emms)
EXPORT_SYMBOL(SIMDx86_femms)

BEGIN_SYMBOL(SIMDx86_emms)
	emms
	ret
END_SYMBOL(SIMDx86_emms)

BEGIN_SYMBOL(SIMDx86_femms)
	femms
	ret
END_SYMBOL(SIMDx86_femms)
