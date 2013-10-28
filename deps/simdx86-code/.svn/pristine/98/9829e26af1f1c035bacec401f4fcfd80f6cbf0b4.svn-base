; polygon_sse.asm -- SIMDx86 Polygon Library (SSE)
; Written by Carl Skeps, 2006 (carl.skeps@gmail.com)
; Under LGPL License
; Part of SIMDx86 Project

%include "SIMDx86asm.inc"
%include "SIMDx86Polygon.inc"

;List of symbols this module provides
EXPORT_SYMBOL(SIMDx86Polygon_PlaneNormal_SSE)

; Vector shuffling constants for SSE_CROSS_PRODUCT
; w | x | z | y  == 1100 1001 = 0xC9
; w | y | x | z  == 1101 0010 = 0xD2
SSE_SHUF_VECTOR_XZY EQU 0C9H
SSE_SHUF_VECTOR_YXZ EQU 0D2H

; Argument Stack Offsets
SOURCE_POLYGON_OFFSET EQU 8H
DEST_VECTOR_OFFSET EQU 4H

SECTION .text

;Function: SIMDx86Polygon_PlaneNormal_SSE
;Computes the normal vector for a given polygon
BEGIN_SYMBOL(SIMDx86Polygon_PlaneNormal_SSE)

	; Get the source and destination pointers off the stack
	MOV EAX, [ESP + SOURCE_POLYGON_OFFSET]
	MOV EDX, [ESP + DEST_VECTOR_OFFSET]

	; Using aligned moves because we require aligned data only
	MOVAPS XMM0, [EAX + POLYGON_VERTEX_A_OFFSET]
	MOVAPS XMM1, [EAX + POLYGON_VERTEX_B_OFFSET]
	MOVAPS XMM2, [EAX + POLYGON_VERTEX_C_OFFSET]

	; Find the two vectors defined by the three vertices of the polygon
	SUBPS XMM0, XMM1
	SUBPS XMM2, XMM1

	; Duplicate the registers so we can shuffle
	; and complete the cross product of XMM0 and XMM2
	MOVAPS XMM1, XMM0
	MOVAPS XMM3, XMM2

	; Shuffles to set up the cross product multiply
	SHUFPS XMM0, XMM0, SSE_SHUF_VECTOR_XZY
	SHUFPS XMM1, XMM1, SSE_SHUF_VECTOR_YXZ
	SHUFPS XMM2, XMM2, SSE_SHUF_VECTOR_YXZ
	SHUFPS XMM3, XMM3, SSE_SHUF_VECTOR_XZY

	; Complete the cross product by multiplying
	; and then subtracting
	MULPS XMM0, XMM2
	MULPS XMM1, XMM3
	SUBPS XMM0, XMM1

	; Store the result
	MOVAPS [EDX], XMM0

	RET

END_SYMBOL(SIMDx86Polygon_PlaneNormal_SSE)
SIZE_SYMBOL SIMDx86Polygon_PlaneNormal_SSE
