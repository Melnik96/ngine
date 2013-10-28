; vector_sse.asm -- SSE accelerated vector functions
; Written by Patrick Baggett, 2006 (baggett.patrick@gmail.com)
; Under LGPL License
; Part of SIMDx86 Project

%include "SIMDx86asm.inc"



;List of symbols this module provides
EXPORT_SYMBOL(SIMDx86Vector_Sum_SSE)
EXPORT_SYMBOL(SIMDx86Vector_SumOf_SSE)
EXPORT_SYMBOL(SIMDx86Vector_Diff_SSE)
EXPORT_SYMBOL(SIMDx86Vector_DiffOf_SSE)
EXPORT_SYMBOL(SIMDx86Vector_Scale_SSE)
EXPORT_SYMBOL(SIMDx86Vector_ScaleOf_SSE)
EXPORT_SYMBOL(SIMDx86Vector_Dot_SSE)
EXPORT_SYMBOL(SIMDx86Vector_Dot4_SSE)
EXPORT_SYMBOL(SIMDx86Vector_LengthSq_SSE)
EXPORT_SYMBOL(SIMDx86Vector_Length_SSE)
EXPORT_SYMBOL(SIMDx86Vector_Length_HIPREC_SSE)
EXPORT_SYMBOL(SIMDx86Vector_Cross_SSE)
EXPORT_SYMBOL(SIMDx86Vector_CrossOf_SSE)
EXPORT_SYMBOL(SIMDx86Vector_Normalize_SSE)
EXPORT_SYMBOL(SIMDx86Vector_Normalize_HIPREC_SSE)
EXPORT_SYMBOL(SIMDx86Vector_NormalizeOf_SSE)
EXPORT_SYMBOL(SIMDx86Vector_NormalizeOf_HIPREC_SSE)
EXPORT_SYMBOL(SIMDx86Vector_Distance_SSE)
EXPORT_SYMBOL(SIMDx86Vector_Distance_HIPREC_SSE)

section .text

BEGIN_SYMBOL(SIMDx86Vector_Sum_SSE) ;void SIMDx86Vector_Sum(SIMDx86Vector* pOut, const SIMDx86Vector* pIn)
	mov eax, [esp+4]			;eax = &V1
	mov edx, [esp+8]			;edx = &V2
	movaps xmm0, [eax]			;xmm0 = ? | Z1 | Y1 | X1
	addps xmm0, [edx]			;xmm0 = ? | Z1+Z2 | Y1+Y2 | X1+X2
	movaps [eax], xmm0			;V1 = ? | Z1+Z2 | Y1+Y2 | X1+X2
	ret
END_SYMBOL(SIMDx86Vector_Sum_SSE)
SIZE_SYMBOL SIMDx86Vector_Sum_SSE

BEGIN_SYMBOL(SIMDx86Vector_SumOf_SSE) ;void SIMDx86Vector_SumOf(SIMDx86Vector* pOut, const SIMDx86Vector* pIn1, const SIMDx86Vector* pIn2)
	mov eax, [esp+8]		;eax = &In1
	mov edx, [esp+12]		;edx = &In2
	movaps xmm0, [eax]		;xmm0 = ? | Z1 | Y1 | X1
	mov ecx, [esp+4]		;ecx = &Output -- Hide a bit of latency in movaps (Latency=1, Throughput=2 if I recall)
	addps xmm0, [edx]		;xmm0 = ? | Z1+Z2 | Y1+Y2 | X1+X2
	movaps [ecx], xmm0		;Output = ? | Z1+Z2 | Y1+Y2 | X1+X2
	ret
END_SYMBOL(SIMDx86Vector_SumOf_SSE)
SIZE_SYMBOL SIMDx86Vector_SumOf_SSE

BEGIN_SYMBOL(SIMDx86Vector_Diff_SSE) ;void SIMDx86Vector_Diff(SIMDx86Vector* pLeft, SIMDx86Vector* pRight)
	mov eax, [esp+4]		;eax = &Left
	mov edx, [esp+8]		;edx = &Right
	movaps xmm0, [eax]		;xmm0 = ? | Lz | Ly | Lx
	subps xmm0, [edx]		;xmm0 = ? | Lz-Rz | Ly-Ry | Lx-Rx
	movaps [eax], xmm0		;Left = ? | Lz-Rz | Ly-Ry | Lx-Rx
	ret
END_SYMBOL(SIMDx86Vector_Diff_SSE)
SIZE_SYMBOL SIMDx86Vector_Diff_SSE

BEGIN_SYMBOL(SIMDx86Vector_DiffOf_SSE) ;void SIMDx86Vector_DiffOf(SIMDx86Vector* pOut, const SIMDx86Vector* pLeft, const SIMDx86Vector* pRight)
	mov eax, [esp+8]		;eax = &Left
	mov edx, [esp+12]		;edx = &Right
	movaps xmm0, [eax]		;xmm0 = ? | Lz | Ly | Lx
	mov ecx, [esp+4]		;ecx = &Output -- Hide a bit of latency in movaps
	subps xmm0, [edx]		;xmm0 = ? | Lz-Rz | Ly-Ry | Lx-Rx
	movaps [ecx], xmm0		;Output = ? | Lz-Rz | Ly-Ry | Lx-Rx
	ret
END_SYMBOL(SIMDx86Vector_DiffOf_SSE)
SIZE_SYMBOL SIMDx86Vector_DiffOf_SSE

BEGIN_SYMBOL(SIMDx86Vector_Scale_SSE) ;void SIMDx86Vector_Scale(SIMDx86Vector* pOut, float scalar)
	movlps xmm0, [esp+4]		;xmm0 = ? | ? | scalar | ? (movlps is faster than movss. See http://www.amd.com/us-en/assets/content_type/white_papers_and_tech_docs/25112.PDF)
	mov eax, [esp+4]			;eax = &Output
	shufps xmm0, xmm0, 0x55		;xmm0 = scalar | scalar | scalar | scalar
	mulps xmm0, [eax]			;xmm0 = ? | Z*scalar | Y*scalar | X*scalar
	movaps [eax], xmm0			;Output = ? | Z*scalar | Y*scalar | X*scalar
	ret
END_SYMBOL(SIMDx86Vector_Scale_SSE) ;Would it be faster to not do mulps/movaps on the same location?
SIZE_SYMBOL SIMDx86Vector_Scale_SSE

BEGIN_SYMBOL(SIMDx86Vector_ScaleOf_SSE) ;void SIMDx86Vector_ScaleOf(SIMDx86Vector* pOut, const SIMDx86Vector* pIn, float scalar)
	movlps xmm0, [esp+12]			;xmm0 = ? | ? | ? | scalar
	mov eax, [esp+8]				;eax = &Input
	shufps xmm0, xmm0, 0x00			;xmm0 = scalar | scalar | scalar | scalar
	mov edx, [esp+4]				;edx = &Output (hide shufps latency with another instruction)
	mulps xmm0, [eax]				;xmm0 = ? | Z*scalar | Y*scalar | X*scalar
	movaps [edx], xmm0				;Output = ? | Z*scalar | Y*scalar | X*scalar
	ret
END_SYMBOL(SIMDx86Vector_ScaleOf_SSE)
SIZE_SYMBOL SIMDx86Vector_ScaleOf_SSE

BEGIN_SYMBOL(SIMDx86Vector_Dot_SSE) ;float SIMDx86Vector_Dot(const SIMDx86Vector* pSrc1, const SIMDx86Vector* pSrc2)
	mov eax, [esp+4]
	mov edx, [esp+8]
	
	;Load and multiply vectors
	movaps xmm0, [eax]		;xmm0 = ? | Z1 | Y1 | X1
	mulps xmm0, [edx]		;xmm1 = ? | Z1*Z2 | Y1*Y2 | X1*X2
	
	;Perform horizontal sum
	movhlps xmm1, xmm0		;xmm1 = ? | ? | ? | Z1*Z2
	addss xmm1, xmm0		;xmm0 = ? | ? | ? | Z1*Z2 + X1*X2
	shufps xmm0, xmm0, 0x55 ;xmm0 = ? | ? | ? | Y1*Y2
	addss xmm1, xmm0		;xmm1 = ? | ? | ? | Z1*Z2 + Y1*Y2 + X1*X2
	
	;Save in st0 where C looks for result
	movss [esp-4], xmm1
	fld dword [esp-4]
	
	;Return
	ret
END_SYMBOL(SIMDx86Vector_Dot_SSE)
SIZE_SYMBOL SIMDx86Vector_Dot_SSE

BEGIN_SYMBOL(SIMDx86Vector_Dot4_SSE) ;float SIMDx86Vector_Dot4(const float* pSrc4D1, const float* pSrc4D2)
	mov eax, [esp+4]
	mov edx, [esp+8]
	
	;Load and multiply vectors
	movaps xmm0, [eax]		;xmm0 = W1 | Z1 | Y1 | X1
	xorps xmm1, xmm1		;Make sure the contents of xmm1 are not undefined so that fp exception does not occur (SLOW!!) when addps comes
	mulps xmm0, [edx]		;xmm1 = W1*W2 | Z1*Z2 | Y1*Y2 | X1*X2
	
	;Perform horizontal sum (Isn't there a better way to do this?)
	movhlps xmm1, xmm0		;xmm1 = 0 | 0 | W1*W2 | Z1*Z2
	addps xmm1, xmm0		;xmm1 = ? | ? | W1*W2 +Y1*Y2 | Z1*Z2 + X1*X2
	movaps xmm0, xmm1		;xmm0 = ? | ? | W1*W2 +Y1*Y2 | Z1*Z2 + X1*X2
	shufps xmm0, xmm0, 0x55 ;xmm0 = ? | ? | ? | W1*W2 + Y1*Y2
	addss xmm1, xmm0		;xmm1 = ? | ? | ? | W1*W2 + Z1*Z2 + Y1*Y2 + X1*X2
	
	;Save in st0 where C looks for result
	movss [esp-4], xmm1
	fld dword [esp-4]
	
	;Return
	ret
END_SYMBOL(SIMDx86Vector_Dot4_SSE)
SIZE_SYMBOL SIMDx86Vector_Dot4_SSE

BEGIN_SYMBOL(SIMDx86Vector_LengthSq_SSE) ;float SIMDx86Vector_LengthSq(const SIMDx86Vector* pVec)
	mov eax, [esp+4]			;eax = &Src1
	movaps xmm0, [eax]			;xmm0 = ? | Z1 | Y1 | X1
	mulps xmm0,xmm0				;xmm0 = ? | Z1*Z1 | Y1*Y1 | X1*X1
	movhlps xmm1, xmm0			;xmm1 = ? | ? | ? | Z1*Z1
	addss xmm1, xmm0			;xmm1 = ? | ? | ? | X1*X1+Z1*Z1
	shufps xmm0, xmm0, 0x00		;xmm0 = Y1*Y1 | Y1*Y1 | Y1*Y1 | Y1*Y1
	addss xmm1, xmm0			;xmm1 = ? | ? | ? | X1*X1+Y1*Y1+Z1*Z1 == magsq(Src1)
	movss [esp-4], xmm1			;temp = magsq(Src1, Src1)
	fld dword [esp-4]			;st0 = magsq(Src1, Src1)
	ret
END_SYMBOL(SIMDx86Vector_LengthSq_SSE)
SIZE_SYMBOL SIMDx86Vector_LengthSq_SSE

BEGIN_SYMBOL(SIMDx86Vector_Length_SSE)
	mov eax, [esp+4]			;eax = &Src1
	movaps xmm0, [eax]			;xmm0 = ? | Z1 | Y1 | X1
	mulps xmm0,xmm0				;xmm0 = ? | Z1*Z1 | Y1*Y1 | X1*X1
	movhlps xmm1, xmm0			;xmm1 = ? | ? | ? | Z1*Z1
	addss xmm1, xmm0			;xmm1 = ? | ? | ? | X1*X1+Z1*Z1
	shufps xmm0, xmm0, 0x00		;xmm0 = Y1*Y1 | Y1*Y1 | Y1*Y1 | Y1*Y1
	addss xmm1, xmm0			;xmm1 = ? | ? | ? | X1*X1+Y1*Y1+Z1*Z1 == magsq(Src1)

	;Ok, we have the magnitude (length) squared, now we need the square root.
	;Since this is the low precision version, we do the reciprocal of the reciprocal-square-root approximation.
	;This is blazingly fast, much faster than a square root, but not so great precision (~3-4 decimal places at best)
	;Compare to high-precision version below.
	rsqrtss xmm1, xmm1			;xmm1 = ? | ? | ? | 1/mag(Src1) (approx)
	rcpss xmm1, xmm1			;xmm1 = ? | ? | ? | mag(Src1) (approx)
	movss [esp-4], xmm1			;temp = magsq(Src1, Src1)
	fld dword [esp-4]			;st0 = magsq(Src1, Src1)
	ret
END_SYMBOL(SIMDx86Vector_Length_SSE)
SIZE_SYMBOL SIMDx86Vector_Length_SSE

BEGIN_SYMBOL(SIMDx86Vector_Length_HIPREC_SSE)
	mov eax, [esp+4]			;eax = &Src1
	movaps xmm0, [eax]			;xmm0 = ? | Z1 | Y1 | X1
	mulps xmm0,xmm0				;xmm0 = ? | Z1*Z1 | Y1*Y1 | X1*X1
	movhlps xmm1, xmm0			;xmm1 = ? | ? | ? | Z1*Z1
	addss xmm1, xmm0			;xmm1 = ? | ? | ? | X1*X1+Z1*Z1
	shufps xmm0, xmm0, 0x00		;xmm0 = Y1*Y1 | Y1*Y1 | Y1*Y1 | Y1*Y1
	addss xmm1, xmm0			;xmm1 = ? | ? | ? | X1*X1+Y1*Y1+Z1*Z1 == magsq(Src1)
	
	;Ok, we have the magnitude (length) squared, now we need the square root.
	;Compare to low precision version above.
	sqrtss xmm1, xmm2			;xmm1 = ? | ? | ? | sqrtf(X1*X1+Y1*Y1+Z1*Z1) == mag(Src1)
	movss [esp-4], xmm1			;temp = magsq(Src1, Src1)
	fld dword [esp-4]			;st0 = magsq(Src1, Src1)
	ret
END_SYMBOL(SIMDx86Vector_Length_HIPREC_SSE)
SIZE_SYMBOL SIMDx86Vector_Length_HIPREC_SSE

;The cross product can be computed as a determinate of a 3x3 matrix with i,j,k and the two vectors
;  [i  j  k]
;  [Lx Ly Lz]
;  [Rx Ry Rz]
;x' = i(Ly*Rz - Lz*Ry)		where i = 1 (unit vector)
;y' = j(Lz*Rx - Lx*Rz)		where j = 1 (unit vector)
;z' = k(Lx*Ry - Ly*Rx)		where k = 1 (unit vector)
; Once properly shuffled, the parallelism is perfect for SSE

BEGIN_SYMBOL(SIMDx86Vector_Cross_SSE) ;void SIMDx86Vector_Cross(SIMDx86Vector* pLeft, const SIMDx86Vector* pRight)
	mov eax, [esp+4]
	mov edx, [esp+8]

	;Fetch data and make duplicates	
	movaps xmm0, [eax]		;xmm0 = ? | Lz | Ly | Lx
	movaps xmm1, [edx]		;xmm1 = ? | Rz | Ry | Rx
	movaps xmm2, xmm0		;xmm2 = ? | Lz | Ly | Lx
	movaps xmm3, xmm1		;xmm3 = ? | Rz | Ry | Rx

	;Shuffle constants for calculation of cross product
	;0xC9 == 1100|1001 == w | x | z | y
	;0xD2 == 1101|0010 == w | y | x | z
	;If you are having a hard time following these shuffles, look at the definition of a crossproduct, or check vector.c
	;for the generic C implementation

	shufps xmm0, xmm0, 0xC9		;xmm0 = ? | Lx | Lz | Ly 
	shufps xmm1, xmm1, 0xD2		;xmm1 = ? | Rz | Ry | Rx
	shufps xmm2, xmm2, 0xD2		;xmm2 = ? | Lz | Ly | Lx
	shufps xmm3, xmm3, 0xC9		;xmm3 = ? | Rx | Rz | Ry

	;Multiply the two columns
	mulps xmm1, xmm0			;xmm1 = ? | Lx*Rz | Lz*Ry | Ly*Rx 
	mulps xmm3, xmm2			;xmm3 = ? | Lz*Rx | Ly*Rz | Lx*Ry

	;Now just subtract
	subps xmm0, xmm2			;xmm0 = cross(Left, Right)
	
	movaps [eax], xmm0			;Left = cross(Left, Right)
	ret	
END_SYMBOL(SIMDx86Vector_Cross_SSE)
SIZE_SYMBOL SIMDx86Vector_Cross_SSE

BEGIN_SYMBOL(SIMDx86Vector_CrossOf_SSE) ;void SIMDx86Vector_CrossOf(SIMDx86Vector* pOut, const SIMDx86Vector* pLeft, const SIMDx86Vector* pRight)
	mov eax, [esp+8]
	mov edx, [esp+12]

	;Fetch data and make duplicates	
	movaps xmm0, [eax]		;xmm0 = ? | Lz | Ly | Lx
	movaps xmm1, [edx]		;xmm1 = ? | Rz | Ry | Rx
	movaps xmm2, xmm0		;xmm2 = ? | Lz | Ly | Lx
	movaps xmm3, xmm1		;xmm3 = ? | Rz | Ry | Rx

	;Shuffle constants for calculation of cross product
	;0xC9 == 1100|1001 == w | x | z | y
	;0xD2 == 1101|0010 == w | y | x | z
	;If you are having a hard time following these shuffles, look at the definition of a crossproduct, or check vector.c
	;for the generic C implementation

	shufps xmm0, xmm0, 0xC9		;xmm0 = ? | Lx | Lz | Ly 
	shufps xmm1, xmm1, 0xD2		;xmm1 = ? | Rz | Ry | Rx
	shufps xmm2, xmm2, 0xD2		;xmm2 = ? | Lz | Ly | Lx
	shufps xmm3, xmm3, 0xC9		;xmm3 = ? | Rx | Rz | Ry

	;Multiply the two columns
	mulps xmm1, xmm0			;xmm1 = ? | Lx*Rz | Lz*Ry | Ly*Rx 
	mulps xmm3, xmm2			;xmm3 = ? | Lz*Rx | Ly*Rz | Lx*Ry

	;Hide latency and load edx with output pointer
	mov edx, [esp+4]			;edx = &Output

	;Now just subtract
	subps xmm0, xmm2			;xmm0 = cross(Left, Right)
	
	movaps [edx], xmm0			;Left = cross(Left, Right)
	ret	
END_SYMBOL(SIMDx86Vector_CrossOf_SSE)
SIZE_SYMBOL SIMDx86Vector_CrossOf_SSE

BEGIN_SYMBOL(SIMDx86Vector_Normalize_SSE) ;void SIMDx86Vector_Normalize(SIMDx86Vector* pVec)
	mov eax, [esp+4]
	movaps xmm0, [eax]	;xmm0 = ? | z | y | x
	movaps xmm2, xmm0		;Save original vector in xmm2
	mulps xmm0, xmm0		;Square terms

	;Sum components
	movhlps xmm1, xmm0	;xmm1 = ? | ? | ? | z*z
	addss xmm1, xmm0		;xmm0 = ? | ? | ? | z*z + x*x
	shufps xmm0, xmm0, 0x55 ;xmm0 = ? | ? | ? | y*y
	addss xmm1, xmm0		;xmm1 = ? | ? | ? | z*z + y*y + x*x

	;Get reciprocal square root and multiply to perform cheap square root
	rsqrtss xmm1, xmm1	;xmm1 = ? | ? | ? | 1.0f / sqrtf(z*z + y*y + x*x) == mag(input)
	shufps xmm1, xmm1, 0x00 ;xmm1 = mag(input) | mag(input) | mag(input) | mag(input)
	mulps xmm1, xmm2		;xmm0 = ? | z / mag() | y / mag() | x / mag()

	;Write out result
	movaps [eax], xmm1
	ret
END_SYMBOL(SIMDx86Vector_Normalize_SSE)
SIZE_SYMBOL SIMDx86Vector_Normalize_SSE

BEGIN_SYMBOL(SIMDx86Vector_Normalize_HIPREC_SSE) ;void SIMDx86Vector_Normalize(SIMDx86Vector* pVec)
	mov eax, [esp+4]
	movaps xmm0, [eax]	;xmm0 = ? | z | y | x
	movaps xmm2, xmm0		;Save original vector in xmm2
	mulps xmm0, xmm0		;Square terms

	;Sum components
	movhlps xmm1, xmm0	;xmm1 = ? | ? | ? | z*z
	addss xmm1, xmm0		;xmm0 = ? | ? | ? | z*z + x*x
	shufps xmm0, xmm0, 0x55 ;xmm0 = ? | ? | ? | y*y
	addss xmm1, xmm0		;xmm1 = ? | ? | ? | z*z + y*y + x*x

	;Do a full square root and a full divide
	sqrtss xmm1, xmm1			;xmm1 = ? | ? | ? | 1.0f / sqrtf(z*z + y*y + x*x) == mag(input)
	shufps xmm1, xmm1, 0x00 	;xmm0 = mag(input) | mag(input) | mag(input) | mag(input)
	divps xmm2, xmm1			;xmm2 = ? | z / mag() | y / mag() | x / mag()

	;Write out result
	movaps [eax], xmm2
	ret
END_SYMBOL(SIMDx86Vector_Normalize_HIPREC_SSE)
SIZE_SYMBOL SIMDx86Vector_Normalize_HIPREC_SSE

BEGIN_SYMBOL(SIMDx86Vector_NormalizeOf_SSE) ;void SIMDx86Vector_NormalizeOf(SIMDx86Vector* pOut, const SIMDx86Vector* pVec)
	mov eax, [esp+8]
	mov edx, [esp+4]
	movaps xmm0, [eax]		;xmm0 = ? | z | y | x
	movaps xmm2, xmm0		;Save original vector in xmm2
	mulps xmm0, xmm0		;Square terms

	;Sum components
	movhlps xmm1, xmm0	;xmm1 = ? | ? | ? | z*z
	addss xmm1, xmm0		;xmm0 = ? | ? | ? | z*z + x*x
	shufps xmm0, xmm0, 0x55 ;xmm0 = ? | ? | ? | y*y
	addss xmm1, xmm0		;xmm1 = ? | ? | ? | z*z + y*y + x*x

	;Get reciprocal square root and multiply to perform cheap square root
	rsqrtss xmm1, xmm1	;xmm1 = ? | ? | ? | 1.0f / sqrtf(z*z + y*y + x*x) == mag(input)
	shufps xmm1, xmm1, 0x00 ;xmm1 = mag(input) | mag(input) | mag(input) | mag(input)
	mulps xmm1, xmm2		;xmm0 = ? | z / mag() | y / mag() | x / mag()

	;Write out result
	movaps [edx], xmm1
	ret
END_SYMBOL(SIMDx86Vector_NormalizeOf_SSE)
SIZE_SYMBOL SIMDx86Vector_NormalizeOf_SSE

BEGIN_SYMBOL(SIMDx86Vector_NormalizeOf_HIPREC_SSE) ;void SIMDx86Vector_NormalizeOf(SIMDx86Vector* pOut, const SIMDx86Vector* pVec)
	mov eax, [esp+8]
	mov edx, [esp+4]
	movaps xmm0, [eax]		;xmm0 = ? | z | y | x
	movaps xmm2, xmm0		;Save original vector in xmm2
	mulps xmm0, xmm0		;Square terms

	;Sum components
	movhlps xmm1, xmm0		;xmm1 = ? | ? | ? | z*z
	addss xmm1, xmm0		;xmm0 = ? | ? | ? | z*z + x*x
	shufps xmm0, xmm0, 0x55 ;xmm0 = ? | ? | ? | y*y
	addss xmm1, xmm0		;xmm1 = ? | ? | ? | z*z + y*y + x*x

	;Do a full square root and a full divide
	sqrtss xmm1, xmm1			;xmm1 = ? | ? | ? | 1.0f / sqrtf(z*z + y*y + x*x) == mag(input)
	shufps xmm1, xmm1, 0x00 	;xmm0 = mag(input) | mag(input) | mag(input) | mag(input)
	divps xmm2, xmm1			;xmm2 = ? | z / mag() | y / mag() | x / mag()

	;Write out result
	movaps [edx], xmm2
	ret
END_SYMBOL(SIMDx86Vector_NormalizeOf_HIPREC_SSE)
SIZE_SYMBOL SIMDx86Vector_NormalizeOf_HIPREC_SSE

BEGIN_SYMBOL(SIMDx86Vector_Distance_SSE) ;float SIMDx86Vector_Distance(const SIMDx86Vector* pVec1, const SIMDx86Vector* pVec2)
	mov eax, [esp+4]
	mov edx, [esp+8]

	;Load vector 1 and subtract vector 2 from it
	movaps xmm0, [eax]
	subps xmm0, [edx]

	;Square the resultant
	mulps xmm0,xmm0				;xmm0 = ? | Z1*Z1 | Y1*Y1 | X1*X1
	
	;Horizontally add the components
	movhlps xmm1, xmm0			;xmm1 = ? | ? | ? | Z1*Z1
	addss xmm1, xmm0			;xmm1 = ? | ? | ? | X1*X1+Z1*Z1
	shufps xmm0, xmm0, 0x00		;xmm0 = Y1*Y1 | Y1*Y1 | Y1*Y1 | Y1*Y1
	addss xmm1, xmm0			;xmm1 = ? | ? | ? | X1*X1+Y1*Y1+Z1*Z1 == magsq(Src1)

	;Ok, we have the magnitude (length) squared, now we need the square root.
	;Since this is the low precision version, we do the reciprocal of the reciprocal-square-root approximation.
	;This is blazingly fast, much faster than a square root, but not so great precision (~3-4 decimal places at best)
	rsqrtss xmm1, xmm1			;xmm1 = ? | ? | ? | 1/mag(Src1) (approx)
	rcpss xmm1, xmm1			;xmm1 = ? | ? | ? | mag(Src1) (approx)
	movss [esp-4], xmm1			;temp = magsq(Src1, Src1)
	fld dword [esp-4]			;st0 = magsq(Src1, Src1)
	ret
END_SYMBOL(SIMDx86Vector_Distance_SSE)
SIZE_SYMBOL SIMDx86Vector_Distance_SSE

BEGIN_SYMBOL(SIMDx86Vector_Distance_HIPREC_SSE) ;float SIMDx86Vector_Distance(const SIMDx86Vector* pVec1, const SIMDx86Vector* pVec2)
	mov eax, [esp+4]
	mov edx, [esp+8]

	;Load vector 1 and subtract vector 2 from it
	movaps xmm0, [eax]
	subps xmm0, [edx]

	;Square the resultant
	mulps xmm0,xmm0				;xmm0 = ? | Z1*Z1 | Y1*Y1 | X1*X1

	;Horizontally add the components
	movhlps xmm1, xmm0			;xmm1 = ? | ? | ? | Z1*Z1
	addss xmm1, xmm0			;xmm1 = ? | ? | ? | X1*X1+Z1*Z1
	shufps xmm0, xmm0, 0x00		;xmm0 = Y1*Y1 | Y1*Y1 | Y1*Y1 | Y1*Y1
	addss xmm1, xmm0			;xmm1 = ? | ? | ? | X1*X1+Y1*Y1+Z1*Z1 == magsq(Src1)

	;Ok, we have the magnitude (length) squared, now we need the square root.
	;Perform a full square root
	sqrtss xmm1, xmm1
	movss [esp-4], xmm1			;temp = magsq(Src1, Src1)
	fld dword [esp-4]			;st0 = magsq(Src1, Src1)
	ret
END_SYMBOL(SIMDx86Vector_Distance_HIPREC_SSE)
SIZE_SYMBOL SIMDx86Vector_Distance_HIPREC_SSE
