; vector_sse3.asm -- SSE3 accelerated vector functions (makes use of new haddps instruction)
; Written by Patrick Baggett, 2006 (baggett.patrick@gmail.com)
; Under LGPL License
; Part of SIMDx86 Project

%include "SIMDx86asm.inc"

section .text

EXTERN _SIMDx86_float_SSE_NO_W_MASK			;unsigned int SIMDx86_float_SSE_NO_W_MASK[4] = { 0xFFFFFFFF,  0xFFFFFFFF, 0xFFFFFFFF, 0x00000000 };

;List of symbols this module provides
EXPORT_SYMBOL(SIMDx86Vector_Dot_SSE3)
EXPORT_SYMBOL(SIMDx86Vector_Dot4_SSE3)
EXPORT_SYMBOL(SIMDx86Vector_LengthSq_SSE3)
EXPORT_SYMBOL(SIMDx86Vector_Length_SSE3)
EXPORT_SYMBOL(SIMDx86Vector_Length_HIPREC_SSE3)
EXPORT_SYMBOL(SIMDx86Vector_Normalize_SSE3)
EXPORT_SYMBOL(SIMDx86Vector_Normalize_HIPREC_SSE3)
EXPORT_SYMBOL(SIMDx86Vector_NormalizeOf_SSE3)
EXPORT_SYMBOL(SIMDx86Vector_NormalizeOf_HIPREC_SSE3)
EXPORT_SYMBOL(SIMDx86Vector_Distance_SSE3)
EXPORT_SYMBOL(SIMDx86Vector_Distance_HIPREC_SSE3)

;TODO: Could this be done more efficiently with movaps to load 2nd vector rather than stall on andps?
;TODO: is movlps faster than movss for final value? AMD's docs say mem->reg it is faster, what about reg->mem?
BEGIN_SYMBOL(SIMDx86Vector_Dot_SSE3) ;float SIMDx86Vector_Dot(const SIMDx86Vector* pSrc1, const SIMDx86Vector* pSrc2)
	mov eax, [esp+4]
	mov edx, [esp+8]
	
	;Load vector 1 and mask off the 'w' component
	movaps xmm0, [eax]								;xmm0 = ? | z1 | y1 | x1
	andps xmm0, [_SIMDx86_float_SSE_NO_W_MASK]		;xmm0 = ? & 0x0 | z1 & 0xFFFFFFFF | y1 & 0xFFFFFFFF | x1 & 0xFFFFFFFF
	
	;Multiply components then horizontally add
	mulps xmm0, [edx]								;xmm0 = 0 | z1*z2 | y1*y2 | x1*x2
	haddps xmm0, xmm0								;xmm0 = ? | ?  | 0 + z1*z2 | y1*y2 + x1*x2
	haddps xmm0, xmm0								;xmm0 = ? | ?  | ? | 0 + z1*z2 + y1*y2 + x1*x2
	
	movss [esp-4], xmm0
	fld dword [esp-4]
	ret
END_SYMBOL(SIMDx86Vector_Dot_SSE3)
SIZE_SYMBOL SIMDx86Vector_Dot_SSE3

BEGIN_SYMBOL(SIMDx86Vector_Dot4_SSE3) ;float SIMDx86Vector_Dot4(const float* pSrc4D1, const float* pSrc4D2)
	mov eax, [esp+4]
	mov edx, [esp+8]
	
	;Load vector 1 and multiply by vector 2
	movaps xmm0, [eax]								;xmm0 = w1 | z1 | y1 | x1
	mulps xmm0, [edx]								;xmm0 = w1*w2 | z1*z2 | y1*y2 | x1*x2
	
	;Horizontally add components
	haddps xmm0, xmm0								;xmm0 = ? | ?  | w1*w2 + z1*z2 | y1*y2 + x1*x2
	haddps xmm0, xmm0								;xmm0 = ? | ?  | ? | w1*w2 + z1*z2 + y1*y2 + x1*x2
	
	movss [esp-4], xmm0
	fld dword [esp-4]
	ret
END_SYMBOL(SIMDx86Vector_Dot4_SSE3)
SIZE_SYMBOL SIMDx86Vector_Dot4_SSE3

BEGIN_SYMBOL(SIMDx86Vector_LengthSq_SSE3) ;float SIMDx86Vector_LengthSq(const SIMDx86Vector* pVec)
	mov eax, [esp+4]
	
	;Load vector and mask off the 'w' component
	movaps xmm0, [eax]								;xmm0 = ? | z | y | x
	andps xmm0, [_SIMDx86_float_SSE_NO_W_MASK]		;xmm0 = ? & 0x0 | z & 0xFFFFFFFF | y & 0xFFFFFFFF | x & 0xFFFFFFFF
	
	;Square components and horizontally add
	mulps xmm0, xmm0								;xmm0 = 0 | z*z | y*y | x*x
	haddps xmm0, xmm0								;xmm0 = ? | ?  | 0 + z*z | y*y + x*x
	haddps xmm0, xmm0								;xmm0 = ? | ?  | ? | 0 + z*z + y*y + x*x
	
	movss [esp-4], xmm0
	fld dword [esp-4]
	ret
END_SYMBOL(SIMDx86Vector_LengthSq_SSE3)
SIZE_SYMBOL SIMDx86Vector_LengthSq_SSE3


BEGIN_SYMBOL(SIMDx86Vector_Length_SSE3)
	mov eax, [esp+4]
	
	;Load vector and mask off the 'w' component
	movaps xmm0, [eax]								;xmm0 = ? | z | y | x
	andps xmm0, [_SIMDx86_float_SSE_NO_W_MASK]		;xmm0 = ? & 0x0 | z & 0xFFFFFFFF | y & 0xFFFFFFFF | x & 0xFFFFFFFF
	
	;Square components and horizontally add
	mulps xmm0, xmm0								;xmm0 = 0 | z*z | y*y | x*x
	haddps xmm0, xmm0								;xmm0 = ? | ?  | 0 + z*z | y*y + x*x
	haddps xmm0, xmm0								;xmm0 = ? | ?  | ? | 0 + z*z + y*y + x*x

	;Cheap square root
	rsqrtss xmm0, xmm0
	rcpss xmm0, xmm0
	
	movss [esp-4], xmm0
	fld dword [esp-4]
	ret
END_SYMBOL(SIMDx86Vector_Length_SSE3)
SIZE_SYMBOL SIMDx86Vector_Length_SSE3

BEGIN_SYMBOL(SIMDx86Vector_Length_HIPREC_SSE3)
	mov eax, [esp+4]
	
	;Load vector and mask off the 'w' component
	movaps xmm0, [eax]								;xmm0 = ? | z | y | x
	andps xmm0, [_SIMDx86_float_SSE_NO_W_MASK]		;xmm0 = ? & 0x0 | z & 0xFFFFFFFF | y & 0xFFFFFFFF | x & 0xFFFFFFFF
	
	;Square components and horizontally add
	mulps xmm0, xmm0								;xmm0 = 0 | z*z | y*y | x*x
	haddps xmm0, xmm0								;xmm0 = ? | ?  | 0 + z*z | y*y + x*x
	haddps xmm0, xmm0								;xmm0 = ? | ?  | ? | 0 + z*z + y*y + x*x

	;Full square root
	sqrtss xmm0, xmm0
	
	movss [esp-4], xmm0
	fld dword [esp-4]
	ret
END_SYMBOL(SIMDx86Vector_Length_HIPREC_SSE3)
SIZE_SYMBOL SIMDx86Vector_Length_HIPREC_SSE3


; Vnormalized = V / ||V||, where ||V|| = sqrt(Vx*Vx + Vy*Vy + Vz*Vz)
BEGIN_SYMBOL(SIMDx86Vector_Normalize_SSE3)
	mov eax, [esp+4]
	movaps xmm0, [eax]	;xmm0 = ? | z | y | x
	andps xmm0, [_SIMDx86_float_SSE_NO_W_MASK]		;xmm0 = ? & 0x0 | z & 0xFFFFFFFF | y & 0xFFFFFFFF | x & 0xFFFFFFFF
	movaps xmm2, xmm0		;Save original vector in xmm2

	;Square components and sum
	mulps xmm0, xmm0		;xmm0 = 0*0 | z*z | y*y | x*x
	haddps xmm0, xmm0		;xmm0 = 0*0+z*z | y*y+x*x | 0*0+z*z | y*y+x*x
	haddps xmm0, xmm0		;xmm0 = 0*0+z*z+y*y+x*x | 0*0+z*z+y*y+x*x | 0*0+z*z+y*y+x*x | 0*0+z*z+y*y+x*x
	
	;Get reciprocal square root (estimate) and multiply to perform cheap square root
	rsqrtps xmm1, xmm0			;xmm1 = 1.0f / sqrtf(z*z + y*y + x*x), all components; equal to 1.0/mag
	mulps xmm2, xmm1			;xmm0 = 0/mag | z/mag | y/mag | x/mag

	;Write out result
	movaps [eax], xmm2
	ret
END_SYMBOL(SIMDx86Vector_Normalize_SSE3)
SIZE_SYMBOL SIMDx86Vector_Normalize_SSE3 

BEGIN_SYMBOL(SIMDx86Vector_Normalize_HIPREC_SSE3)
	mov eax, [esp+4]
	movaps xmm0, [eax]	;xmm0 = ? | z | y | x
	andps xmm0, [_SIMDx86_float_SSE_NO_W_MASK]		;xmm0 = ? & 0x0 | z & 0xFFFFFFFF | y & 0xFFFFFFFF | x & 0xFFFFFFFF
	movaps xmm2, xmm0		;Save original vector in xmm2

	;Square components and sum
	mulps xmm0, xmm0		;xmm0 = 0*0 | z*z | y*y | x*x
	haddps xmm0, xmm0		;xmm0 = 0*0+z*z | y*y+x*x | 0*0+z*z | y*y+x*x
	haddps xmm0, xmm0		;xmm0 = 0*0+z*z+y*y+x*x | 0*0+z*z+y*y+x*x | 0*0+z*z+y*y+x*x | 0*0+z*z+y*y+x*x
	
	;Get full square root and divide
	sqrtss xmm1, xmm0			;xmm1 = ? | ? | ? | sqrtf(z*z + y*y + x*x) == mag. Since all values are the same, doing a scalar sqrt + shuffle rather than quad-square root (slower).
	shufps xmm1, xmm1, 0x00	;xmm1 = mag | mag | mag | mag
	divps xmm2, xmm1			;xmm0 = 0/mag | z/mag | y/mag | x/mag

	;Write out result
	movaps [eax], xmm2
	ret
END_SYMBOL(SIMDx86Vector_Normalize_HIPREC_SSE3)
SIZE_SYMBOL SIMDx86Vector_Normalize_HIPREC_SSE3

BEGIN_SYMBOL(SIMDx86Vector_NormalizeOf_SSE3) ;void SIMDx86Vector_NormalizeOf(SIMDx86Vector* pOut, const SIMDx86Vector* pVec)
	mov eax, [esp+8] ;pVec
	mov edx, [esp+4] ;pOut
	movaps xmm0, [eax]	;xmm0 = ? | z | y | x
	andps xmm0, [_SIMDx86_float_SSE_NO_W_MASK]		;xmm0 = ? & 0x0 | z & 0xFFFFFFFF | y & 0xFFFFFFFF | x & 0xFFFFFFFF
	movaps xmm2, xmm0		;Save original vector in xmm2

	;Square components and sum
	mulps xmm0, xmm0		;xmm0 = 0*0 | z*z | y*y | x*x
	haddps xmm0, xmm0		;xmm0 = 0*0+z*z | y*y+x*x | 0*0+z*z | y*y+x*x
	haddps xmm0, xmm0		;xmm0 = 0*0+z*z+y*y+x*x | 0*0+z*z+y*y+x*x | 0*0+z*z+y*y+x*x | 0*0+z*z+y*y+x*x
	
	;Get reciprocal square root (estimate) and multiply to perform cheap square root
	rsqrtps xmm1, xmm0			;xmm1 = 1.0f / sqrtf(z*z + y*y + x*x), all components; equal to 1.0/mag
	mulps xmm2, xmm1			;xmm0 = 0/mag | z/mag | y/mag | x/mag

	;Write out result
	movaps [edx], xmm2
	ret
END_SYMBOL(SIMDx86Vector_NormalizeOf_SSE3)
SIZE_SYMBOL SIMDx86Vector_NormalizeOf_SSE3

BEGIN_SYMBOL(SIMDx86Vector_NormalizeOf_HIPREC_SSE3) ; void SIMDx86Vector_NormalizeOf(SIMDx86Vector* pOut, const SIMDx86Vector* pVec)
	mov eax, [esp+8] ;pVec
	mov edx, [esp+4] ;pOut
	movaps xmm0, [eax]	;xmm0 = ? | z | y | x
	andps xmm0, [_SIMDx86_float_SSE_NO_W_MASK]		;xmm0 = ? & 0x0 | z & 0xFFFFFFFF | y & 0xFFFFFFFF | x & 0xFFFFFFFF
	movaps xmm2, xmm0		;Save original vector in xmm2

	;Square components and sum
	mulps xmm0, xmm0		;xmm0 = 0*0 | z*z | y*y | x*x
	haddps xmm0, xmm0		;xmm0 = 0*0+z*z | y*y+x*x | 0*0+z*z | y*y+x*x
	haddps xmm0, xmm0		;xmm0 = 0*0+z*z+y*y+x*x | 0*0+z*z+y*y+x*x | 0*0+z*z+y*y+x*x | 0*0+z*z+y*y+x*x
	
	;Get full square root and divide
	sqrtss xmm1, xmm0			;xmm1 = ? | ? | ? | sqrtf(z*z + y*y + x*x) == mag. Since all values are the same, doing a scalar sqrt + shuffle rather than quad-square root (slower).
	shufps xmm1, xmm1, 0x00	;xmm1 = mag | mag | mag | mag
	divps xmm2, xmm1			;xmm0 = 0/mag | z/mag | y/mag | x/mag

	;Write out result
	movaps [edx], xmm2
	ret
END_SYMBOL(SIMDx86Vector_NormalizeOf_HIPREC_SSE3)
SIZE_SYMBOL SIMDx86Vector_NormalizeOf_HIPREC_SSE3

BEGIN_SYMBOL(SIMDx86Vector_Distance_SSE3) ;float SIMDx86Vector_Distance(const SIMDx86Vector* pVec1, const SIMDx86Vector* pVec2)
	mov eax, [esp+4]
	mov edx, [esp+8]
	
	;Load vector 1 and subtract vector 2 to find resultant
	movaps xmm0, [eax]
	subps xmm0, [edx]
	
	;Mask of 'w' component (which is undefined), then horizontally add to find magnitude squared
	andps xmm0, [_SIMDx86_float_SSE_NO_W_MASK]
	haddps xmm0, xmm0
	haddps xmm0, xmm0

	;Cheap reciprocal of a reciprocal square root (fast, but imperfect)
	rsqrtss xmm0, xmm0
	rcpss xmm0, xmm0
	
	movss [esp-4], xmm0
	fld dword [esp-4]
	ret
END_SYMBOL(SIMDx86Vector_Distance_SSE3)
SIZE_SYMBOL SIMDx86Vector_Distance_SSE3 

BEGIN_SYMBOL(SIMDx86Vector_Distance_HIPREC_SSE3) ;float SIMDx86Vector_Distance(const SIMDx86Vector* pVec1, const SIMDx86Vector* pVec2)
	mov eax, [esp+4]
	mov edx, [esp+8]
	
	;Load vector 1 and subtract vector 2 to find resultant
	movaps xmm0, [eax]
	subps xmm0, [edx]
	
	;Mask of 'w' component (which is undefined), then horizontally add to find distance squared
	andps xmm0, [_SIMDx86_float_SSE_NO_W_MASK]
	haddps xmm0, xmm0
	haddps xmm0, xmm0

	;Full square root to find distance
	sqrtss xmm0, xmm0
	
	movss [esp-4], xmm0
	fld dword [esp-4]
	ret
END_SYMBOL(SIMDx86Vector_Distance_HIPREC_SSE3)
SIZE_SYMBOL SIMDx86Vector_Distance_HIPREC_SSE3
