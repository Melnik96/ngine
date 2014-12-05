; polygon_buffer.asm -- NULL buffer space for functions
; Written by Patrick Baggett, 2006 (baggett.patrick@gmail.com)
; Under LGPL License
; Part of SIMDx86 Project

%include "SIMDx86asm.inc"

section .text

EXPORT_SYMBOL(SIMDx86Polygon_PlaneNormal)

BEGIN_SYMBOL(SIMDx86Polygon_PlaneNormal)
	times OVERLAY_SIZE_MEDIUM db 0xc9

