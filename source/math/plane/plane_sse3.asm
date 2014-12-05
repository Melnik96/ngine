; plane_sse3.asm -- SIMDx86 Plane Library (SSE3)
; Written by Carl Skeps, 2006 (carl.skeps@gmail.com)
; Under LGPL License
; Part of SIMDx86 Project

%include "SIMDx86asm.inc"
%include "SIMDx86Polygon.inc"
%include "SIMDx86Plane.inc"

;List of symbols this module provides
EXPORT_SYMBOL(SIMDx86Plane_FromPolygon_SSE3)
EXPORT_SYMBOL(SIMDx86Plane_FromPoints_SSE3)

; Vector shuffling constants for SSE_CROSS_PRODUCT
; w | x | z | y  == 1100 1001 = 0xC9
; w | y | x | z  == 1101 0010 = 0xD2
SSE_SHUF_VECTOR_XZY EQU 0C9H
SSE_SHUF_VECTOR_YXZ EQU 0D2H

; Vector shuffling constants for register duplication
; x | x | x | x  == 0000 0000 = 0x00
; y | y | y | y  == 0101 0101 = 0x55
SSE_SHUF_REG_XXXX EQU 0H
SSE_SHUF_REG_YYYY EQU 055H

; Masks which include the specified components
;				     w   |   z   |   y   |  x
SSE_XYZ_MASK DDQ 00000000FFFFFFFFFFFFFFFFFFFFFFFFH
; Note: YASM chokes on this if it is in proper format
; we will need to fix this before we can compile with MASM
SSE_W_MASK  DDQ 0xFFFFFFFF000000000000000000000000

; Mask for IEEE sign bit
SSE_SIGN_BIT_MASK DDQ 80000000800000008000000080000000H

SECTION .text

; Argument Stack Offsets
SOURCE_POLYGON_OFFSET EQU 8H
DEST_PLANE_OFFSET EQU 4H

;Function: SIMDx86Plane_FromPolygon_SSE
;Computes the plane for a given polygon
; where plane a = n.x, b = n.y, c = n.z, d = d
; and d = -(n.x * a.x + n.y * a.y + n.z * a.z)
BEGIN_SYMBOL(SIMDx86Plane_FromPolygon_SSE3)

	; Get the source and destination pointers off the stack
	MOV EAX, [ESP + SOURCE_POLYGON_OFFSET]
	MOV EDX, [ESP + DEST_PLANE_OFFSET]

	; Using aligned moves because we require aligned data only
	MOVAPS XMM0, [EAX + POLYGON_VERTEX_A_OFFSET]
	MOVAPS XMM1, [EAX + POLYGON_VERTEX_B_OFFSET]
	MOVAPS XMM2, [EAX + POLYGON_VERTEX_C_OFFSET]
	MOVAPS XMM7, XMM0 ; Save off XMM0 for d calculation

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

	; Dump W component
	ANDPS XMM0, [SSE_XYZ_MASK]

	; Save XMM4 = 0 | z | y | x
	MOVAPS XMM4, XMM0

	; Multiply with point 'a' on the polygon (saved in XMM7)
	MULPS XMM0, XMM7

	; Horizontally add XMM0
	HADDPS XMM0, XMM0 ; XMM0 NOW F3 + F4 | F1 + F2 | F3 + F4 | F1 + F2
	HADDPS XMM0, XMM0 ; XMM0 NOW F1+F2+F3+F4 | F1+F2+F3+F4 | F1+F2+F3+F4 | F1+F2+F3+F4 

	; Change the sign and mask off xyz
	XORPS XMM0, [SSE_SIGN_BIT_MASK]
	ANDPS XMM0, [SSE_W_MASK]
	ORPS  XMM4, XMM0

	; Get out of here
	MOVAPS [EDX], XMM4

	RET

END_SYMBOL(SIMDx86Plane_FromPolygon_SSE3)
SIZE_SYMBOL SIMDx86Plane_FromPolygon_SSE3

; Argument Stack Offsets
SOURCE_POINT1_OFFSET EQU 08H
SOURCE_POINT2_OFFSET EQU 0CH
SOURCE_POINT3_OFFSET EQU 10H

;Function: SIMDx86Plane_FromPoints_SSE
;Computes the plane for a given set of points
; where plane a = n.x, b = n.y, c = n.z, d = d
; and d = -(n.x * a.x + n.y * a.y * n.z * a.z)
BEGIN_SYMBOL(SIMDx86Plane_FromPoints_SSE3)

	; Get the source and destination pointers off the stack
	MOV EAX, [ESP + SOURCE_POINT1_OFFSET]
	MOV ECX, [ESP + SOURCE_POINT2_OFFSET]
	MOV EDX, [ESP + SOURCE_POINT3_OFFSET]

	; Using aligned moves because we require aligned data only
	MOVAPS XMM0, [EAX]
	MOVAPS XMM1, [ECX]
	MOVAPS XMM2, [EDX]

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

	; Replace EDX with the destination value
	; Ok to do it here as we are far enough
	; away from last read as to not stall
	MOV EDX, [ESP + DEST_PLANE_OFFSET]

	; Dump W component
	ANDPS XMM0, [SSE_XYZ_MASK]

	; Save XMM4 = 0 | z | y | x
	MOVAPS XMM4, XMM0

	; Multiply with point 'a' on the polygon (saved in XMM7)
	MULPS XMM0, XMM7

	; Horizontally add XMM0
	HADDPS XMM0, XMM0 ; XMM0 NOW F3 + F4 | F1 + F2 | F3 + F4 | F1 + F2
	HADDPS XMM0, XMM0 ; XMM0 NOW F1+F2+F3+F4 | F1+F2+F3+F4 | F1+F2+F3+F4 | F1+F2+F3+F4 

	; Change the sign and mask off xyz
	XORPS XMM0, [SSE_SIGN_BIT_MASK]
	ANDPS XMM0, [SSE_W_MASK]
	ORPS  XMM4, XMM0

	; Get out of here
	MOVAPS [EDX], XMM4

	RET

END_SYMBOL(SIMDx86Plane_FromPoints_SSE3)
SIZE_SYMBOL SIMDx86Plane_FromPoints_SSE3
