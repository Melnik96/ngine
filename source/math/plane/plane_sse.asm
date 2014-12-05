; plane_sse.asm -- SIMDx86 Plane Library (SSE)
; Written by Carl Skeps, 2006 (carl.skeps@gmail.com)
; Under LGPL License
; Part of SIMDx86 Project

%include "SIMDx86asm.inc"
%include "SIMDx86Polygon.inc"

;List of symbols this module provides
EXPORT_SYMBOL(SIMDx86Plane_FromPolygon_SSE)
EXPORT_SYMBOL(SIMDx86Plane_FromPoints_SSE)
EXPORT_SYMBOL(SIMDx86Plane_DistToPoint_SSE)
EXPORT_SYMBOL(SIMDx86Plane_DistToSphere_SSE)

; Vector shuffling constants for SSE_CROSS_PRODUCT
; w | x | z | y  == 1100 1001 = 0xC9
; w | y | x | z  == 1101 0010 = 0xD2
SSE_SHUF_VECTOR_XZY EQU 0C9H
SSE_SHUF_VECTOR_YXZ EQU 0D2H

; Vector shuffling constants for register duplication
; x | x | x | x  == 0000 0000 = 0x00
; y | y | y | y  == 0101 0101 = 0x55
; d | d | d | d  == 1111 1111 = 0xFF
SSE_SHUF_REG_XXXX EQU 000H
SSE_SHUF_REG_YYYY EQU 055H
SSE_SHUF_REG_DDDD EQU 0FFH

; Masks which include the specified components
;				     w   |   z   |   y   |  x
SSE_XYZ_MASK DDQ 00000000FFFFFFFFFFFFFFFFFFFFFFFFH
; Note: YASM chokes on this if it is in proper format
; we will need to fix this before we can compile with MASM
SSE_W_MASK  DDQ 0xFFFFFFFF000000000000000000000000
SSE_W1_MASK DDQ 0x3F800000000000000000000000000000

; Mask for IEEE sign bit
SSE_SIGN_BIT_MASK DDQ 80000000800000008000000080000000H
SSE_NO_SIGN_BIT_MASK DDQ 0x7FFFFFFF7FFFFFFF7FFFFFFF7FFFFFFF

SECTION .text

; Argument Stack Offsets
SOURCE_POLYGON_OFFSET EQU 8H
DEST_PLANE_OFFSET EQU 4H

;Function: SIMDx86Plane_FromPolygon_SSE
;Computes the plane for a given polygon
; where plane a = n.x, b = n.y, c = n.z, d = d
; and d = -(n.x * a.x + n.y * a.y * n.z * a.z)
BEGIN_SYMBOL(SIMDx86Plane_FromPolygon_SSE)

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

	; Multiply with point 'a' on the polygon (saved in xmm7)
	MULPS XMM0, XMM7

	; Sum it all up SSE3 has a horizontal add instruction
	MOVHLPS XMM1, XMM0 ; XMM1 NOW ? | ? | 0 | n.z * a.z
	ADDSS   XMM1, XMM0 ; XMM1 NOW ? | ? | n.y * a.y | n.z * a.z + n.x + a.x
	SHUFPS  XMM0, XMM0, SSE_SHUF_REG_YYYY ; XMM0 NOW n.y * a.y | n.y * a.y | n.y * a.y | n.y * a.y
	ADDSS   XMM1, XMM0 ; XMM1 NOW ? | ? | ? | n.z * a.z + n.x + a.x + n.y * a.y

	; Change sign
	XORPS XMM1, [SSE_SIGN_BIT_MASK] ; XMM1 NOW ? | ? | ? | -(n.z * a.z + n.x + a.x + n.y * a.y)

	; Shuffle to W component location, mask off xyz, and OR with saved portions
	SHUFPS XMM1, XMM1, SSE_SHUF_REG_XXXX
	ANDPS XMM1, [SSE_W_MASK]
	ORPS XMM4, XMM1 ; XMM4 NOW d | z | y | x

	; Get out of here
	MOVAPS [EDX], XMM4

	RET

END_SYMBOL(SIMDx86Plane_FromPolygon_SSE)
SIZE_SYMBOL SIMDx86Plane_FromPolygon_SSE

; Argument Stack Offsets
SOURCE_POINT1_OFFSET EQU 08H
SOURCE_POINT2_OFFSET EQU 0CH
SOURCE_POINT3_OFFSET EQU 10H

;Function: SIMDx86Plane_FromPoints_SSE
;Computes the plane for a given set of points
; where plane a = n.x, b = n.y, c = n.z, d = d
; and d = -(n.x * a.x + n.y * a.y * n.z * a.z)
BEGIN_SYMBOL(SIMDx86Plane_FromPoints_SSE)

	; Get the source and destination pointers off the stack
	MOV EAX, [ESP + SOURCE_POINT1_OFFSET]
	MOV ECX, [ESP + SOURCE_POINT2_OFFSET]
	MOV EDX, [ESP + SOURCE_POINT3_OFFSET]

	; Using aligned moves because we require aligned data only
	MOVAPS XMM0, [EAX]
	MOVAPS XMM1, [ECX]
	MOVAPS XMM2, [EDX]

	; Save off XMM0 for d calculation
	MOVAPS XMM7, XMM0

	; Find the two vectors defined by the three points
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

	; Multiply with point 'a' on the polygon (saved in xmm7)
	MULPS XMM0, XMM7

	; Sum it all up SSE3 has a horizontal add instruction
	MOVHLPS XMM1, XMM0 ; XMM1 NOW ? | ? | 0 | n.z * a.z
	ADDSS   XMM1, XMM0 ; XMM1 NOW ? | ? | n.y * a.y | n.z * a.z + n.x + a.x
	SHUFPS  XMM0, XMM0, SSE_SHUF_REG_YYYY ; XMM0 NOW n.y * a.y | n.y * a.y | n.y * a.y | n.y * a.y
	ADDSS   XMM1, XMM0 ; XMM1 NOW ? | ? | ? | n.z * a.z + n.x + a.x + n.y * a.y

	; Change sign
	XORPS XMM1, [SSE_SIGN_BIT_MASK] ; XMM1 NOW ? | ? | ? | -(n.z * a.z + n.x + a.x + n.y * a.y)

	; Shuffle to W component location, mask off xyz, and OR with saved portions
	SHUFPS XMM1, XMM1, SSE_SHUF_REG_XXXX
	ANDPS XMM1, [SSE_W_MASK]
	ORPS XMM4, XMM1 ; XMM4 NOW d | z | y | x

	; Get out of here
	MOVAPS [EDX], XMM4

	RET

END_SYMBOL(SIMDx86Plane_FromPoints_SSE)
SIZE_SYMBOL SIMDx86Plane_FromPoints_SSE

; Argument Stack Offsets
SOURCE_PLANE_OFFSET EQU 04H
SOURCE_POINT_OFFSET EQU 08H

;Function: SIMDx86Plane_DistToPoint_SSE
;Computes the distance from a point to the given plane
; where dist = |pl.x * pt.x + pl.y * pt.y * pl.z * pt.z + d|
BEGIN_SYMBOL(SIMDx86Plane_DistToPoint_SSE)

	MOV EAX, [ESP + SOURCE_PLANE_OFFSET]
	MOV EDX, [ESP + SOURCE_POINT_OFFSET]

	; Aligned moves because we require aligned data
	MOVAPS XMM0, [EAX]
	MOVAPS XMM1, [EDX]

	ANDPS XMM1, [SSE_XYZ_MASK] ; Put zero's into the high fp value of the point
							   ; this is pad area and doesn't matter to us
							   ; but the FPU loves to multiply by zero
	MOVAPS XMM7, XMM0 ; Keep a copy for later

	MULPS XMM1, XMM0 ; XMM1 NOW pt.z * pl.c | pt.y * pl.b | pt.x * pl.a
	SHUFPS XMM7, XMM7, SSE_SHUF_REG_DDDD ; XMM7 NOW pl.d | pl.d | pl.d | pl.d
										 ; good time to do this we are stalling
										 ; waiting for MULPS to finish

	MOVHLPS XMM2, XMM1 ; XMM2 NOW ? | ? | ? | pt.z * pl.c
	ADDSS XMM2, XMM1 ; XMM2 NOW ? | ? | ? | pt.x * pl.a + pt.z * pl.c
	SHUFPS XMM1, XMM1, SSE_SHUF_REG_YYYY ; XMM1 NOW pt.y * pl.b | pt.y * pl.b | pt.y * pl.b | pt.y * pl.b
	ADDSS XMM1, XMM2 ; XMM1 NOW ? | ? | ? | pt.x * pl.a + pt.y * pl.b + pt.z * pl.c
	ADDSS XMM1, XMM7 ; XMM1 NOW ? | ? | ? | pt.x * pl.a + pt.y * pl.b + pt.z * pl.c + d
	ANDPS XMM1, [SSE_NO_SIGN_BIT_MASK] ; XMM1 NOW |XMM1|

	MOVSS [ESP - 4], XMM1 ; Steal some stack space
	FLD DWORD [ESP - 4] ; Push the return value onto the floating point stack
	RET

END_SYMBOL(SIMDx86Plane_DistToPoint_SSE)
SIZE_SYMBOL SIMDx86Plane_DistToPoint_SSE

; Argument Stack Offsets
SOURCE_SPHERE_OFFSET EQU 08H
SPHERE_RADIUS_OFFSET EQU 10H

;Function: SIMDx86Plane_DistToSphere_SSE
;Computes the distance from a sphere to the given plane
; where dist = |pl.x * pt.x + pl.y * pt.y * pl.z * pt.z + d|
BEGIN_SYMBOL(SIMDx86Plane_DistToSphere_SSE)

	MOV EAX, [ESP + SOURCE_PLANE_OFFSET]
	MOV EDX, [ESP + SOURCE_SPHERE_OFFSET]

	; Aligned moves because we require aligned data
	MOVAPS XMM0, [EAX]
	MOVAPS XMM1, [EDX]

	ANDPS XMM1, [SSE_XYZ_MASK] ; Put zero's into the high fp value of the point
							   ; this is pad area and doesn't matter to us
							   ; but the FPU loves to multiply by zero
	MOVAPS XMM7, XMM0 ; Keep a copy for later

	MULPS XMM1, XMM0 ; XMM1 NOW pt.z * pl.c | pt.y * pl.b | pt.x * pl.a
	SHUFPS XMM7, XMM7, SSE_SHUF_REG_DDDD ; XMM7 NOW pl.d | pl.d | pl.d | pl.d
										 ; good time to do this we are stalling
										 ; waiting for MULPS to finish

	MOVHLPS XMM2, XMM1 ; XMM2 NOW ? | ? | ? | pt.z * pl.c
	ADDSS XMM2, XMM1 ; XMM2 NOW ? | ? | ? | pt.x * pl.a + pt.z * pl.c
	SHUFPS XMM1, XMM1, SSE_SHUF_REG_YYYY ; XMM1 NOW pt.y * pl.b | pt.y * pl.b | pt.y * pl.b | pt.y * pl.b
	ADDSS XMM1, XMM2 ; XMM1 NOW ? | ? | ? | pt.x * pl.a + pt.y * pl.b + pt.z * pl.c
	ADDSS XMM1, XMM7 ; XMM1 NOW ? | ? | ? | pt.x * pl.a + pt.y * pl.b + pt.z * pl.c + d
	ANDPS XMM1, [SSE_NO_SIGN_BIT_MASK] ; XMM1 NOW |XMM1|

	XORPS XMM7, XMM7 ; XMM7 NOW 0 | 0 | 0 | 0
	
	; Subtract radius
	SUBSS XMM1, [EDX + SPHERE_RADIUS_OFFSET] ; XMM1 NOW ? | ? | ? | dist - radius
	MAXSS XMM1, XMM7; XMM1 NOW ? | ? | ? | max(0, dist-radius)

	MOVSS [ESP - 4], XMM1 ; Steal some stack space
	FLD DWORD [ESP - 4] ; Push the return value onto the floating point stack
	RET

END_SYMBOL(SIMDx86Plane_DistToSphere_SSE)
SIZE_SYMBOL SIMDx86Plane_DistToSphere_SSE
