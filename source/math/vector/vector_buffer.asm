; vector_buffer.asm -- Buffer space for code overlays
; Written by Patrick Baggett, 2006 (baggett.patrick@gmail.com)
; Under LGPL License
; Part of SIMDx86 Project

section .text 

%include "SIMDx86asm.inc"

;List of symbols this module provides
EXPORT_SYMBOL(SIMDx86Vector_Sum)
EXPORT_SYMBOL(SIMDx86Vector_SumOf)
EXPORT_SYMBOL(SIMDx86Vector_Diff)
EXPORT_SYMBOL(SIMDx86Vector_DiffOf)
EXPORT_SYMBOL(SIMDx86Vector_Scale)
EXPORT_SYMBOL(SIMDx86Vector_ScaleOf)
EXPORT_SYMBOL(SIMDx86Vector_Dot)
EXPORT_SYMBOL(SIMDx86Vector_Dot4)
EXPORT_SYMBOL(SIMDx86Vector_LengthSq)
EXPORT_SYMBOL(SIMDx86Vector_Length)
EXPORT_SYMBOL(SIMDx86Vector_Cross)
EXPORT_SYMBOL(SIMDx86Vector_CrossOf)
EXPORT_SYMBOL(SIMDx86Vector_Normalize)
EXPORT_SYMBOL(SIMDx86Vector_NormalizeOf)
EXPORT_SYMBOL(SIMDx86Vector_Distance)

; The "times OVERLAY_SIZE_MEDIUM db 0xC9" reserves a buffer space of code bytes to be overlayed, filling it with ret's


BEGIN_SYMBOL(SIMDx86Vector_Sum)
	times OVERLAY_SIZE_MEDIUM db 0xc9
	
BEGIN_SYMBOL(SIMDx86Vector_SumOf)
	times OVERLAY_SIZE_MEDIUM db 0xC9
	
BEGIN_SYMBOL(SIMDx86Vector_Diff)
	times OVERLAY_SIZE_MEDIUM db 0xC9
	
BEGIN_SYMBOL(SIMDx86Vector_DiffOf)
	times OVERLAY_SIZE_MEDIUM db 0xC9
	
BEGIN_SYMBOL(SIMDx86Vector_Scale)
	times OVERLAY_SIZE_MEDIUM db 0xC9
	
BEGIN_SYMBOL(SIMDx86Vector_ScaleOf)
	times OVERLAY_SIZE_MEDIUM db 0xC9
	
BEGIN_SYMBOL(SIMDx86Vector_Dot)
	times OVERLAY_SIZE_MEDIUM db 0xC9
	
BEGIN_SYMBOL(SIMDx86Vector_Dot4)
	times OVERLAY_SIZE_MEDIUM db 0xC9
	
BEGIN_SYMBOL(SIMDx86Vector_LengthSq)
	times OVERLAY_SIZE_MEDIUM db 0xC9
	
BEGIN_SYMBOL(SIMDx86Vector_Length)
	times OVERLAY_SIZE_MEDIUM db 0xC9
	
BEGIN_SYMBOL(SIMDx86Vector_Cross)
	times OVERLAY_SIZE_MEDIUM db 0xC9
	
BEGIN_SYMBOL(SIMDx86Vector_CrossOf)
	times OVERLAY_SIZE_MEDIUM db 0xC9
	
BEGIN_SYMBOL(SIMDx86Vector_Normalize)
	times OVERLAY_SIZE_MEDIUM db 0xC9
	
BEGIN_SYMBOL(SIMDx86Vector_NormalizeOf)
	times OVERLAY_SIZE_MEDIUM db 0xC9
	
BEGIN_SYMBOL(SIMDx86Vector_Distance)
	times OVERLAY_SIZE_MEDIUM db 0xC9
