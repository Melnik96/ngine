; vector_3dnow.asm -- 3DNow! accelerated vector functions
; Written by Patrick Baggett, 2006 (baggett.patrick@gmail.com)
; Under LGPL License
; Part of SIMDx86 Project

%include "SIMDx86asm.inc"

EXTERN _SIMDx86_float_3DNOW_NO_W_MASK		;in consts.c, when AND'ed with a mmreg, it removes the top 32 bits (y | x) -> ( 0 | x)

section .text

EXPORT_SYMBOL(SIMDx86Vector_Sum_3DNow)
EXPORT_SYMBOL(SIMDx86Vector_SumOf_3DNow)
EXPORT_SYMBOL(SIMDx86Vector_Diff_3DNow)
EXPORT_SYMBOL(SIMDx86Vector_DiffOf_3DNow)
EXPORT_SYMBOL(SIMDx86Vector_Scale_3DNow)
EXPORT_SYMBOL(SIMDx86Vector_ScaleOf_3DNow)
EXPORT_SYMBOL(SIMDx86Vector_Dot_3DNow)
EXPORT_SYMBOL(SIMDx86Vector_Dot4_3DNow)
EXPORT_SYMBOL(SIMDx86Vector_LengthSq_3DNow)
EXPORT_SYMBOL(SIMDx86Vector_Length_3DNow)
EXPORT_SYMBOL(SIMDx86Vector_Length_HIPREC_3DNow)
EXPORT_SYMBOL(SIMDx86Vector_Cross_3DNow)
EXPORT_SYMBOL(SIMDx86Vector_CrossOf_3DNow)
EXPORT_SYMBOL(SIMDx86Vector_Normalize_3DNow)
EXPORT_SYMBOL(SIMDx86Vector_Normalize_HIPREC_3DNow)
EXPORT_SYMBOL(SIMDx86Vector_NormalizeOf_3DNow)
EXPORT_SYMBOL(SIMDx86Vector_NormalizeOf_HIPREC_3DNow)
EXPORT_SYMBOL(SIMDx86Vector_Distance_3DNow)
EXPORT_SYMBOL(SIMDx86Vector_Distance_HIPREC_3DNow)

; 3DNow! still has some uses despite what most people think. It performs as well as SSE on a number of things, and sometimes better. There are
; indeed a few things that SSE can do better, but they are fewer than people think. 3DNow! has an absurdly low latency of just 2 cycles for any
; operation, and two pipes: MUL and ADD. The MUL pipe includes PFMUL, PFRCPIT1, and the other reciprocal instructions. The ADD pipe includes PFADD,
; PFSUB, PAND, POR, PXOR, and the other ALU operations. K6-2 and Athlons can issue 2 SIMD instructions/cycle, specifically one from each pipe.


; All of these functions include an FEMMS/RET combination reguardless of if SIMDX86FLAGS_NOEMMS is set
; The code overlay system will replace FEMMS/RET with just a RET/NOP/NOP combination at runtime. Some functions
; require FEMMS because they return a value in the FPU, so those will not be changed.

; FEMMS 0x0F, 0x0E   ->   RET 0xC9
; RET	0xC9		 ->   NOP, NOP 0x90, 0x90 (The code shouldn't ever get here, technically...


BEGIN_SYMBOL(SIMDx86Vector_Sum_3DNow) ; void SIMDx86Vector_Sum(SIMDx86Vector* pOut, const SIMDx86Vector* pIn);
	mov eax, [esp+4]
	mov edx, [esp+4]
	
	;Load vector 1
	movq mm0, [eax]
	movd mm1, [eax+8]
	
	;Add vector 2
	pfadd mm0, [edx]
	pfadd mm1, [edx+8]
	
	;Store
	movq [eax], mm0
	movd [eax+8], mm1
	
	femms
	ret
END_SYMBOL(SIMDx86Vector_Sum_3DNow)
SIZE_SYMBOL SIMDx86Vector_Sum_3DNow


BEGIN_SYMBOL(SIMDx86Vector_SumOf_3DNow) ;void SIMDx86Vector_SumOf(SIMDx86Vector* pOut, const SIMDx86Vector* pIn1, const SIMDx86Vector* pIn2);
	mov eax, [esp+8]
	mov edx, [esp+12]
	
	;Load vector 1
	movq mm0, [eax]
	movd mm1, [eax+8]
	
	;Add vector 2
	pfadd mm0, [edx]
	mov eax, [esp+4]		;Hide 2 cycle latency of pfadd if possible
	pfadd mm1, [edx+8]
	
	;Store
	movq [eax], mm0
	movd [eax+8], mm1
	
	femms
	ret
END_SYMBOL(SIMDx86Vector_SumOf_3DNow)
SIZE_SYMBOL SIMDx86Vector_SumOf_3DNow 

BEGIN_SYMBOL(SIMDx86Vector_Diff_3DNow)
	mov eax, [esp+4]
	mov edx, [esp+4]
	
	;Load vector 1
	movq mm0, [eax]
	movd mm1, [eax+8]
	
	;Add vector 2
	pfsub mm0, [edx]
	pfsub mm1, [edx+8]
	
	;Store
	movq [eax], mm0
	movd [eax+8], mm1
	
	femms
	ret
END_SYMBOL(SIMDx86Vector_Diff_3DNow)
SIZE_SYMBOL SIMDx86Vector_Diff_3DNow


BEGIN_SYMBOL(SIMDx86Vector_DiffOf_3DNow)
	mov eax, [esp+8]
	mov edx, [esp+12]
	
	;Load vector 1
	movq mm0, [eax]
	movd mm1, [eax+8]
	
	;Add vector 2
	pfsub mm0, [edx]
	mov eax, [esp+4]		;Hide 2 cycle latency of pfadd if possible
	pfsub mm1, [edx+8]
	
	;Store
	movq [eax], mm0
	movd [eax+8], mm1
	
	femms
	ret

END_SYMBOL(SIMDx86Vector_DiffOf_3DNow)
SIZE_SYMBOL SIMDx86Vector_DiffOf_3DNow

BEGIN_SYMBOL(SIMDx86Vector_Scale_3DNow) ;void SIMDx86Vector_Scale(SIMDx86Vector* pOut, float scalar)
	mov eax, [esp+4]		;eax = pOut
	movd mm0, [esp+8]		;mm0 = 0 | scalar	(would movq be faster? The next punpckldq will just overwrite the entire upper half)
	
	movq mm1, [eax]			;mm1 = y | x
	punpckldq mm0, mm0		;mm0 = scalar | scalar
	movd mm2, [eax+8]		;mm2 = 0 | z  (same thing, would movq be faster?)
	pfmul mm1, mm0			;mm1 = y*scalar | x*scalar
	pfmul mm2, mm0			;mm2 = 0*scalar | z*scalar
	movq [eax], mm1
	movd [eax+8], mm2
	
	femms
	ret
END_SYMBOL(SIMDx86Vector_Scale_3DNow)
SIZE_SYMBOL SIMDx86Vector_Scale_3DNow

BEGIN_SYMBOL(SIMDx86Vector_ScaleOf_3DNow) ;void SIMDx86Vector_ScaleOf(SIMDx86Vector* pOut, const SIMDx86Vector* pIn, float scalar)
	mov eax, [esp+8]		;eax = pIn
	movd mm0, [esp+12]		;mm0 = 0 | scalar	(would movq be faster? The next punpckldq will just overwrite the entire upper half)
	
	movq mm1, [eax]			;mm1 = y | x
	punpckldq mm0, mm0		;mm0 = scalar | scalar
	movd mm2, [eax+8]		;mm2 = 0 | z  (same thing, would movq be faster?)
	pfmul mm1, mm0			;mm1 = y*scalar | x*scalar
	mov eax, [esp+4]		;eax = pOut
	pfmul mm2, mm0			;mm2 = 0*scalar | z*scalar
	movq [eax], mm1
	movd [eax+8], mm2
	
	femms
	ret
END_SYMBOL(SIMDx86Vector_ScaleOf_3DNow)
SIZE_SYMBOL SIMDx86Vector_ScaleOf_3DNow

BEGIN_SYMBOL(SIMDx86Vector_Dot_3DNow) ;float SIMDx86Vector_Dot(const SIMDx86Vector* pSrc1, const SIMDx86Vector* pSrc2)
	mov eax, [esp+4]
	mov edx, [esp+8]
	
	movq mm0, [eax]			; y1 | x1
	movd mm1, [eax+8]		;  0 | z1
		
	pfmul mm0, [edx]		; y1*y2 | x1*x2
	pfmul mm1, [edx+8]		; 0     | z1*z2

	pfadd mm1, mm0			; y1*y2 | x1*x2+z1*z2
	pfacc mm1, mm1			; x1*x2+y1*y2+z1*z2 | x1*x2+y1*y2+z1*z2
	
	movd [esp-4], mm1
	femms
	fld dword [esp-4]
	ret
END_SYMBOL(SIMDx86Vector_Dot_3DNow)
SIZE_SYMBOL SIMDx86Vector_Dot_3DNow

BEGIN_SYMBOL(SIMDx86Vector_Dot4_3DNow) ;float SIMDx86Vector_Dot4(const float* pSrc4D1, const float* pSrc4D2)
	mov eax, [esp+4]
	mov edx, [esp+8]
	
	movq mm0, [eax]			; y1 | x1
	movq mm1, [eax+8]		; w1 | z1
		
	pfmul mm0, [edx]		; y1*y2 | x1*x2
	pfmul mm1, [edx+8]		; w1*w2 | z1*z2

	pfadd mm1, mm0			; y1*y2+w1*w2 | x1*x2+z1*z2
	pfacc mm1, mm1			; x1*x2+y1*y2+z1*z2+w1*w2 | x1*x2+y1*y2+z1*z2+w1*w2
	
	movd [esp-4], mm1
	femms
	fld dword [esp-4]
	ret
END_SYMBOL(SIMDx86Vector_Dot4_3DNow)
SIZE_SYMBOL SIMDx86Vector_Dot4_3DNow

BEGIN_SYMBOL(SIMDx86Vector_LengthSq_3DNow) ;float SIMDx86Vector_LengthSq(const SIMDx86Vector* pVec)
	mov eax, [esp+4]
	
	movq mm0, [eax]			; y1 | x1
	movd mm1, [eax+8]		;  0 | z1
		
	pfmul mm0, mm0			; y1*y2 | x1*x2
	pfmul mm1, mm1			; 0     | z1*z2

	pfadd mm1, mm0			; y1*y2 | x1*x2+z1*z2
	pfacc mm1, mm1			; x1*x2+y1*y2+z1*z2 | x1*x2+y1*y2+z1*z2
	
	movd [esp-4], mm1
	femms
	fld dword [esp-4]
	ret
END_SYMBOL(SIMDx86Vector_LengthSq_3DNow)
SIZE_SYMBOL SIMDx86Vector_LengthSq_3DNow

BEGIN_SYMBOL(SIMDx86Vector_Length_3DNow) ;float SIMDx86Vector_Length(const SIMDx86Vector* pVec)
	mov eax, [esp+4]
	
	movq mm0, [eax]			;mm0 = y | x
	movd mm1, [eax+8]		;mm1 = 0  | z
	
	pfmul mm0, mm0			;mm0 = y*y | x*x
	pfmul mm1, mm1			;mm1 = 0*0 | z*z
	
	pfadd mm1, mm0			; y*y+0*0 | x*x+z*z
	pfacc mm1, mm1			; x*x+y*y+z*z | x*x+y*y+z*z

	;Get 1.0/sqrtf(mag) in mm2, then multiply by original mag to get sqrtf(mag) in about 4 cycles (K6-2/Athlon)	
	pfrsqrt mm2, mm1		; 1/sqrtf(x*x+y*y+z*z) | 1/sqrtf(x*x+y*y+z*z)
	pfmul mm1, mm2			; len(vector) | len(vector)

	movd [esp-4], mm1
	femms
	fld dword [esp-4]
	ret
END_SYMBOL(SIMDx86Vector_Length_3DNow)
SIZE_SYMBOL SIMDx86Vector_Length_3DNow

BEGIN_SYMBOL(SIMDx86Vector_Length_HIPREC_3DNow) ;float SIMDx86Vector_Length(const SIMDx86Vector* pVec)
END_SYMBOL(SIMDx86Vector_Length_HIPREC_3DNow)
	mov eax, [esp+4]
	
	movq mm0, [eax]			;mm0 = y | x
	movd mm1, [eax+8]		;mm1 = 0  | z
	
	pfmul mm0, mm0			;mm0 = y*y | x*x
	pfmul mm1, mm1			;mm1 = 0*0 | z*z
	
	pfadd mm1, mm0			; y*y+0*0 | x*x+z*z
	pfacc mm1, mm1			; x*x+y*y+z*z | x*x+y*y+z*z == magsquared(vector) 

	;Do full precision reciprocal square root using hw Newton-Raphson iterations (follow AMD 3DNow! documents as their instructions are a bit unusual)
	movq mm1, mm7			;mm7 = x*x+y*y+z*z | x*x+y*y+z*z
	pfrsqrt mm2, mm1		;mm2 = x0 = 1/sqrtf(x*x+y*y+z*z) | 1/sqrtf(x*x+y*y+z*z)
	movq mm3, mm2			;mm3 = x0 = 1/sqrtf(x*x+y*y+z*z) | 1/sqrtf(x*x+y*y+z*z)
	pfmul mm2, mm2			;mm2 = x1 = x0*x0
	pfrsqit1 mm1, mm2		;mm1 = x2 = pfrsqit1(mag*mag, x1)
	pfrcpit2 mm1, mm3		;mm1 = 1/sqrtf(mag*mag) = pfrcpit2(x2, x0)
	
	pfmul mm1, mm7			;mm1 = mag*mag / sqrtf(mag*mag) = sqrtf(mag*mag) = mag

	movd [esp-4], mm1
	femms
	fld dword [esp-4]
	ret
SIZE_SYMBOL SIMDx86Vector_Length_HIPREC_3DNow

;Ok, this crossproduct should be a great improvement upon the <= 0.4.0 versions. It is as properly scheduled as I think it can get,
;that is, MUL and ADD pipes are kept busy and interleaved so that no dependency/execution pipe stalls occur, save for the last instruction.
;The number of memory accesses may be a bit large though, and they could be loaded into registers first (as mm4 and mm5 are never used), but
;by the time they are used for the pfmul instructions, the data should already be in L1 cache and therefore not have extra latency.

BEGIN_SYMBOL(SIMDx86Vector_Cross_3DNow) ;void SIMDx86Vector_Cross(SIMDx86Vector* pLeft, const SIMDx86Vector* pRight)
	mov eax, [esp+4]
	mov edx, [esp+8]
	
	movq mm0, [eax]			;mm0 = Ly | Lx
	movq mm1, [eax+8]		;mm1 = ?? | Lz
	movq mm6, mm0			;mm6 = Ly | Lx
	
	punpckldq mm1, mm0		;mm1 = Lx | Lz
	movq mm2, [edx]			;mm2 = Ry | Rx
	movq mm3, [edx+8]		;mm3 = ?? | Rz

	pfmul mm1, [edx+4]									;mm1 = Lx*Rz | Lz*Ry	RIGHT TOP
	movq mm7, mm2										;mm7 = Ry | Rx
	punpckldq mm2, mm3									;mm2 = Rx | Rz
	pand mm6, [_SIMDx86_float_3DNOW_NO_W_MASK]			;mm6 = 0  | Lx
	pfmul mm2, [eax+4]									;mm2 = Lz*Rx | Ly*Rz    LEFT TOP
	pand mm7, [_SIMDx86_float_3DNOW_NO_W_MASK]			;mm7 = 0  | Rx
	pfmul mm6, [edx+4]									;mm6 = 0*Rz | Lx*Ry	LEFT BOTTOM
	pfsub mm2, mm1										;mm2 = Lz*Rx-Lx*Rz | Ly*Rz-Lz*Ry  DIFF1
	pfmul mm7, [eax+4]									;mm7 = 0*Lz | Ly*Rx	RIGHT BOTTOM 
	movq [eax], mm2										;Out = xprod.y | xprod.x
	pfsub mm6, mm7										;mm6 = 0 | 
	movd [eax+8], mm6									;Out = xprod.z

	femms
	ret
END_SYMBOL(SIMDx86Vector_Cross_3DNow)
SIZE_SYMBOL SIMDx86Vector_Cross_3DNow

BEGIN_SYMBOL(SIMDx86Vector_CrossOf_3DNow) ;void SIMDx86Vector_CrossOf(SIMDx86Vector* pOut, const SIMDx86Vector* pLeft, const SIMDx86Vector* pRight)
	
	mov eax, [esp+8]
	mov edx, [esp+12]

	movq mm0, [eax]			;mm0 = Ly | Lx
	movq mm1, [eax+8]		;mm1 = ?? | Lz
	movq mm6, mm0			;mm6 = Ly | Lx
	
	punpckldq mm1, mm0		;mm1 = Lx | Lz
	movq mm2, [edx]			;mm2 = Ry | Rx
	movq mm3, [edx+8]		;mm3 = ?? | Rz

	mov ecx, [esp+4]

	pfmul mm1, [edx+4]									;mm1 = Lx*Rz | Lz*Ry	RIGHT TOP
	movq mm7, mm2										;mm7 = Ry | Rx
	punpckldq mm2, mm3									;mm2 = Rx | Rz
	pand mm6, [_SIMDx86_float_3DNOW_NO_W_MASK]			;mm6 = 0  | Lx
	pfmul mm2, [eax+4]									;mm2 = Lz*Rx | Ly*Rz    LEFT TOP
	pand mm7, [_SIMDx86_float_3DNOW_NO_W_MASK]			;mm7 = 0  | Rx
	pfmul mm6, [edx+4]									;mm6 = 0*Rz | Lx*Ry	LEFT BOTTOM
	pfsub mm2, mm1										;mm2 = Lz*Rx-Lx*Rz | Ly*Rz-Lz*Ry  DIFF1
	pfmul mm7, [eax+4]									;mm7 = 0*Lz | Ly*Rx	RIGHT BOTTOM 
	movq [ecx], mm2										;Out = xprod.y | xprod.x
	pfsub mm6, mm7										;mm6 = 0 | 
	movd [ecx+8], mm6									;Out = xprod.z

	femms
	ret
END_SYMBOL(SIMDx86Vector_CrossOf_3DNow)
SIZE_SYMBOL SIMDx86Vector_CrossOf_3DNow

BEGIN_SYMBOL(SIMDx86Vector_Normalize_3DNow) ;void SIMDx86Vector_Normalize(SIMDx86Vector* pVec)
	mov eax, [esp+4]
	
	movq mm0, [eax]			;mm0 = y | x
	movd mm1, [eax+8]		;mm1 = 0  | z

	movq mm0, mm4			;mm4 = y | x
	movq mm1, mm5			;mm5 = 0 | z
	
	pfmul mm0, mm0			;mm0 = y*y | x*x
	pfmul mm1, mm1			;mm1 = 0*0 | z*z
	
	pfadd mm1, mm0			; y*y+0*0 | x*x+z*z
	pfacc mm1, mm1			; x*x+y*y+z*z | x*x+y*y+z*z == magsquared(vector) 

	;Do full precision reciprocal square root using hw Newton-Raphson iterations (follow AMD 3DNow! documents as their instructions are a bit unusual)
	pfrsqrt mm2, mm1		;mm2 = 1/sqrtf(x*x+y*y+z*z) | 1/sqrtf(x*x+y*y+z*z)	
	pfmul mm4, mm2			;mm4 = y/mag | x/mag		
	pfmul mm5, mm2			;mm5 = 0     | z/mag

	movq [eax], mm4
	movq [eax+8], mm5

	femms
	ret
END_SYMBOL(SIMDx86Vector_Normalize_3DNow)
SIZE_SYMBOL SIMDx86Vector_Normalize_3DNow

BEGIN_SYMBOL(SIMDx86Vector_Normalize_HIPREC_3DNow) ;void SIMDx86Vector_Normalize(SIMDx86Vector* pVec)
	mov eax, [esp+4]
	
	movq mm0, [eax]			;mm0 = y | x
	movd mm1, [eax+8]		;mm1 = 0  | z

	movq mm0, mm4			;mm4 = y | x
	movq mm1, mm5			;mm5 = 0 | z
	
	pfmul mm0, mm0			;mm0 = y*y | x*x
	pfmul mm1, mm1			;mm1 = 0*0 | z*z
	
	pfadd mm1, mm0			; y*y+0*0 | x*x+z*z
	pfacc mm1, mm1			; x*x+y*y+z*z | x*x+y*y+z*z == magsquared(vector) 

	;Do full precision reciprocal square root
	pfrsqrt mm2, mm1		;mm2 = x0 = 1/sqrtf(x*x+y*y+z*z) | 1/sqrtf(x*x+y*y+z*z)
	movq mm3, mm2			;mm3 = x0 = 1/sqrtf(x*x+y*y+z*z) | 1/sqrtf(x*x+y*y+z*z)
	pfmul mm2, mm2			;mm2 = x1 = x0*x0
	pfrsqit1 mm1, mm2		;mm1 = x2 = pfrsqit1(mag*mag, x1)
	pfrcpit2 mm1, mm3		;mm1 = 1/sqrtf(mag*mag) = pfrcpit2(x2, x0)
	
	pfmul mm4, mm1			;mm4 = y/mag | x/mag		
	pfmul mm5, mm1			;mm5 = 0     | z/mag

	movq [eax], mm4
	movq [eax+8], mm5

	femms
	ret
END_SYMBOL(SIMDx86Vector_Normalize_HIPREC_3DNow)
SIZE_SYMBOL SIMDx86Vector_Normalize_HIPREC_3DNow

BEGIN_SYMBOL(SIMDx86Vector_NormalizeOf_3DNow) ;void SIMDx86Vector_NormalizeOf(SIMDx86Vector* pOut, const SIMDx86Vector* pVec)
	mov eax, [esp+8]
	
	movq mm0, [eax]			;mm0 = y | x
	movd mm1, [eax+8]		;mm1 = 0  | z

	movq mm0, mm4			;mm4 = y | x
	movq mm1, mm5			;mm5 = 0 | z
	
	pfmul mm0, mm0			;mm0 = y*y | x*x
	pfmul mm1, mm1			;mm1 = 0*0 | z*z
	
	pfadd mm1, mm0			; y*y+0*0 | x*x+z*z
	pfacc mm1, mm1			; x*x+y*y+z*z | x*x+y*y+z*z == magsquared(vector) 

	;Do full precision reciprocal square root using hw Newton-Raphson iterations (follow AMD 3DNow! documents as their instructions are a bit unusual)
	pfrsqrt mm2, mm1		;mm2 = 1/sqrtf(x*x+y*y+z*z) | 1/sqrtf(x*x+y*y+z*z)	
	mov edx, [esp+4]		;edx = pOut
	pfmul mm4, mm2			;mm4 = y/mag | x/mag		
	pfmul mm5, mm2			;mm5 = 0     | z/mag

	movq [edx], mm4			;pOut->y = y/mag | pOut->x = x/mag
	movq [edx+8], mm5		;pOut->pad = 0   | pOut->z = z/mag

	femms
	ret
END_SYMBOL(SIMDx86Vector_NormalizeOf_3DNow)
SIZE_SYMBOL SIMDx86Vector_NormalizeOf_3DNow

BEGIN_SYMBOL(SIMDx86Vector_NormalizeOf_HIPREC_3DNow) ;void SIMDx86Vector_NormalizeOf(SIMDx86Vector* pOut, const SIMDx86Vector* pVec)
	mov eax, [esp+8]
	mov edx, [esp+4]	

	movq mm0, [eax]			;mm0 = y | x
	movd mm1, [eax+8]		;mm1 = 0  | z

	movq mm0, mm4			;mm4 = y | x
	movq mm1, mm5			;mm5 = 0 | z
	
	pfmul mm0, mm0			;mm0 = y*y | x*x
	pfmul mm1, mm1			;mm1 = 0*0 | z*z
	
	pfadd mm1, mm0			; y*y+0*0 | x*x+z*z
	pfacc mm1, mm1			; x*x+y*y+z*z | x*x+y*y+z*z == magsquared(vector) 

	;Do full precision reciprocal square root
	pfrsqrt mm2, mm1		;mm2 = x0 = 1/sqrtf(x*x+y*y+z*z) | 1/sqrtf(x*x+y*y+z*z)
	movq mm3, mm2			;mm3 = x0 = 1/sqrtf(x*x+y*y+z*z) | 1/sqrtf(x*x+y*y+z*z)
	pfmul mm2, mm2			;mm2 = x1 = x0*x0
	pfrsqit1 mm1, mm2		;mm1 = x2 = pfrsqit1(mag*mag, x1)
	pfrcpit2 mm1, mm3		;mm1 = 1/sqrtf(mag*mag) = pfrcpit2(x2, x0)
	
	pfmul mm4, mm1			;mm4 = y/mag | x/mag		
	pfmul mm5, mm1			;mm5 = 0     | z/mag

	movq [edx], mm4
	movq [edx+8], mm5

	femms
	ret
END_SYMBOL(SIMDx86Vector_NormalizeOf_HIPREC_3DNow)
SIZE_SYMBOL SIMDx86Vector_NormalizeOf_HIPREC_3DNow

BEGIN_SYMBOL(SIMDx86Vector_Distance_3DNow) ;float SIMDx86Vector_Distance(const SIMDx86Vector* pVec1, const SIMDx86Vector* pVec2)
	mov eax, [esp+4]
	mov edx, [esp+8]
	
	movq mm0, [eax]		;mm0 = y1 | x1
	movd mm1, [eax+8]	;mm1 = 0  | z1

	;Find resultant D = V1 - V2
	pfsub mm0, [edx]	;mm0 = y1-y2 | x1-x2   == dy | dx
	pfsub mm1, [edx+8]	;mm1 = ????? | z1-z2   == ?? | dz

	;Calculate magnitude of D
	pfmul mm0, mm0		;mm0 = dy*dy | dx*dx
	pand mm1, [_SIMDx86_float_3DNOW_NO_W_MASK]	;mm1 = 0 | dz
	pfacc mm0, mm0		;mm0 = dy*dy+dx*dx | dy*dy+dx*dx
	pfmul mm1, mm1		;mm1 = 0 | dz*dz
	pfadd mm1, mm0		;mm1 = ? | dy*dy+dx*dx+dz*dz == dist*dist, stall for 1-2 cycles
	
	;Find square root of the squared magnitude
	pfrsqrt mm2, mm1	;mm2 = 1/sqrtf(dist*dist)
	pfmul mm2, mm1		;mm2 = dist*dist/sqrtf(dist*dist) == dist
	
	;exit 3DNow and push result into x87 FPU
	movd [esp-4], mm2
	femms
	fld dword [esp-4]
	ret
END_SYMBOL(SIMDx86Vector_Distance_3DNow)
SIZE_SYMBOL SIMDx86Vector_Distance_3DNow

BEGIN_SYMBOL(SIMDx86Vector_Distance_HIPREC_3DNow) ;float SIMDx86Vector_Distance(const SIMDx86Vector* pVec1, const SIMDx86Vector* pVec2)
	mov eax, [esp+4]
	mov edx, [esp+8]
	
	movq mm0, [eax]		;mm0 = y1 | x1
	movd mm1, [eax+8]	;mm1 = 0  | z1

	;Find resultant D = V1 - V2
	pfsub mm0, [edx]	;mm0 = y1-y2 | x1-x2   == dy | dx
	pfsub mm1, [edx+8]	;mm1 = ????? | z1-z2   == ?? | dz

	;Calculate magnitude of D
	pfmul mm0, mm0		;mm0 = dy*dy | dx*dx
	pand mm1, [_SIMDx86_float_3DNOW_NO_W_MASK]	;mm1 = 0 | dz
	pfacc mm0, mm0		;mm0 = dy*dy+dx*dx | dy*dy+dx*dx
	pfmul mm1, mm1		;mm1 = 0 | dz*dz
	pfadd mm1, mm0		;mm1 = ? | dy*dy+dx*dx+dz*dz == dist*dist, stall for 1-2 cycles
	
	movq mm1, mm7			;mm7 = x*x+y*y+z*z | x*x+y*y+z*z
	pfrsqrt mm2, mm1		;mm2 = x0 = 1/sqrtf(x*x+y*y+z*z) | 1/sqrtf(x*x+y*y+z*z)
	movq mm3, mm2			;mm3 = x0 = 1/sqrtf(x*x+y*y+z*z) | 1/sqrtf(x*x+y*y+z*z)
	pfmul mm2, mm2			;mm2 = x1 = x0*x0
	pfrsqit1 mm1, mm2		;mm1 = x2 = pfrsqit1(mag*mag, x1)
	pfrcpit2 mm1, mm3		;mm1 = 1/sqrtf(mag*mag) = pfrcpit2(x2, x0)

	pfmul mm1, mm7			;mm1 = mag*mag / sqrtf(mag*mag) = sqrtf(mag*mag) = mag
	
	;exit 3DNow and push result into x87 FPU
	movd [esp-4], mm1
	femms
	fld dword [esp-4]
	ret
END_SYMBOL(SIMDx86Vector_Distance_HIPREC_3DNow)
SIZE_SYMBOL SIMDx86Vector_Distance_HIPREC_3DNow

