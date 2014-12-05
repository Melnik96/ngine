; matrix_buffer.asm -- Buffer space for code overlays
; Written by Patrick Baggett, 2006 (baggett.patrick@gmail.com)
; Under LGPL License
; Part of SIMDx86 Project

section .text 

%include "SIMDx86asm.inc"

;List of symbols this module provides
EXPORT_SYMBOL(SIMDx86Matrix_Sum)
EXPORT_SYMBOL(SIMDx86Matrix_SumOf)
EXPORT_SYMBOL(SIMDx86Matrix_Diff)
EXPORT_SYMBOL(SIMDx86Matrix_DiffOf)
EXPORT_SYMBOL(SIMDx86Matrix_Scale)

BEGIN_SYMBOL(SIMDx86Vector_Sum)
	times OVERLAY_SIZE_LARGE db 0xc9
	
BEGIN_SYMBOL(SIMDx86Vector_SumOf)
	times OVERLAY_SIZE_LARGE db 0xC9
	
BEGIN_SYMBOL(SIMDx86Vector_Diff)
	times OVERLAY_SIZE_LARGE db 0xC9
	
BEGIN_SYMBOL(SIMDx86Vector_DiffOf)
	times OVERLAY_SIZE_LARGE db 0xC9

BEGIN_SYMBOL(SIMDx86Vector_Scale)
	times OVERLAY_SIZE_LARGE db 0xC9
	
