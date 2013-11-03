; polygon_x64.asm -- SIMDx86 Polygon Library (x86-64)
; Written by Carl Skeps, 2006 (carl.skeps@gmail.com)
; Under LGPL License
; Part of SIMDx86 Project

%include "SIMDx86asm.inc"
%include "SIMDx86Polygon.inc"

;List of symbols this module provides
EXPORT_SYMBOL(SIMDx86Polygon_PlaneNormal_x64)

; Vector shuffling constants for X64_CROSS_PRODUCT
; w | x | z | y  == 1100 1001 = 0xC9
; w | y | x | z  == 1101 0010 = 0xD2
X64_SHUF_VECTOR_XZY EQU 0C9H
X64_SHUF_VECTOR_YXZ EQU 0D2H

SECTION .text

;Function: SIMDx86Polygon_PlaneNormal_x64
;Computes the normal vector for a given polygon
BEGIN_SYMBOL(SIMDx86Polygon_PlaneNormal_x64)

	; Using aligned moves because the structure should be aligned
	; because it is declared with the ALIGNED attribute
	MOVAPS XMM0, [RDX + POLYGON_VERTEX_A_OFFSET]
	MOVAPS XMM1, [RDX + POLYGON_VERTEX_B_OFFSET]
	MOVAPS XMM2, [RDX + POLYGON_VERTEX_C_OFFSET]

	; Find the two vectors defined by the three vertices of the polygon
	SUBPS XMM0, XMM1
	SUBPS XMM2, XMM1

	; Duplicate the registers so we can shuffle
	; and complete the cross product of XMM0 and XMM2
	MOVAPS XMM1, XMM0
	MOVAPS XMM3, XMM2

	; Shuffles to set up the cross product multiply
	SHUFPS XMM0, XMM0, X64_SHUF_VECTOR_XZY
	SHUFPS XMM1, XMM1, X64_SHUF_VECTOR_YXZ
	SHUFPS XMM2, XMM2, X64_SHUF_VECTOR_YXZ
	SHUFPS XMM3, XMM3, X64_SHUF_VECTOR_XZY

	; Complete the cross product by multiplying
	; and then subtracting
	MULPS XMM0, XMM2
	MULPS XMM1, XMM3
	SUBPS XMM0, XMM1

	; Store the result
	MOVAPS [RCX], XMM0

	RET

END_SYMBOL(SIMDx86Polygon_PlaneNormal_x64)
SIZE_SYMBOL SIMDx86Polygon_PlaneNormal_x64
