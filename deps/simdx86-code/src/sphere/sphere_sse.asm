; sphere_sse.asm -- SIMDx86 Sphere Defines (NASM/YASM)
; Written by Jacob Lidman, 2007 (lidman@student.chalmers.se)
; Under LGPL License
; Part of SIMDx86 Project

; XXX Needs to be cleaned up, optimized, and tested!
; XXX Missing defines such as SPHERE_CENTER_VECTOR and SPHERE_RADIUS -- does not assemble 


%include "SIMDx86Sphere.inc"
%include "SIMDx86Polygon.inc"
%include "SIMDx86asm.inc"

EXPORT_SYMBOL(SIMDx86Sphere_SphereCollision_SSE)
EXPORT_SYMBOL(SIMDx86Sphere_ContainsPoint_SSE)
EXPORT_SYMBOL(SIMDx86Sphere_ContainsPolygon_SSE)
EXPORT_SYMBOL(SIMDx86Sphere_DistanceToPoint_SSE)
EXPORT_SYMBOL(SIMDx86Sphere_DistanceToPoint_HIPREC_SSE)
EXPORT_SYMBOL(SIMDx86Sphere_DistanceToPointSq_SSE)
EXPORT_SYMBOL(SIMDx86Sphere_DistanceToSphere_SSE)
EXPORT_SYMBOL(SIMDx86Sphere_DistanceToSphere_HIPREC_SSE)
EXPORT_SYMBOL(SIMDx86Sphere_DistanceToSphereSq_SSE)
EXPORT_SYMBOL(SIMDx86Sphere_DistanceToSphereSq_HIPREC_SSE)


section .text

BEGIN_SYMBOL(SIMDx86Sphere_SphereCollision_SSE) ;int SIMDx86Sphere_SphereCollision(const SIMDx86Sphere* pIn1, const SIMDx86Sphere* pIn2)
	mov eax, [esp+4] ;pIn1
	mov edx, [esp+8] ;pIn2
	movaps xmm0, [eax+SPHERE_CENTER_VECTOR]	;xmm0 = pIn1->Center
	movaps xmm1, [edx+SPHERE_CENTER_VECTOR]	;xmm1 = pIn2->Center
	subps xmm1, xmm0							;xmm1 = ? | dz | dy | dx = pIn2->Center - pIn1->Center

	;Find length of difference vector squared, as well as radius sum squared
	mulps xmm1,xmm1								;xmm1 = ? | dz*dz | dy*dy | dx*dx
	movss xmm2, [eax+SPHERE_RADIUS]				;xmm2 = pIn1->Radius
	movhlps xmm0, xmm1							;xmm0 = ? | ? | ? | dz*dz
	addss xmm2, [edx+SPHERE_RADIUS]				;xmm2 = pIn1->Radius + pIn2->Radius
	addss xmm0, xmm1							;xmm0 = ? | ? | ? | dx*dx + dz*dz
	mulps xmm2, xmm2							;xmm2 = (pIn1->Radius + pIn2->Radius)^2
	shufps xmm1, xmm1, 0x55						;xmm1 = dy*dy | dy*dy | dy*dy | dy*dy
	addss xmm0, xmm1							;xmm0 = ? | ? | ? | dx*dx + dy*dy + dz*dz = lengthsq(pIn2->Center - pIn1->Center)

	xor eax, eax
	comiss xmm2, xmm0   ;(pIn1->Radius + pIn2->Radius)^2 - lengthsq(pIn2->Center - pIn1->Center)

	ja SIMDx86Sphere_SphereCollision_SSE_return_FALSE
		inc eax
	
	SIMDx86Sphere_SphereCollision_SSE_return_FALSE
	ret
	
END_SYMBOL(SIMDx86Sphere_SphereCollision_SSE)
SIZE_SYMBOL SIMDx86Sphere_SphereCollision_SSE

BEGIN_SYMBOL(SIMDx86Sphere_ContainsPoint_SSE) ;int SIMDx86Sphere_ContainsPoint(const SIMDx86Sphere* pSphere, const SIMDx86Vector* pVec)
	mov eax, dword[esp+4] ;pSphere
	mov edx, dword[esp+8] ;pVec
	movaps xmm0, [eax+SPHERE_CENTER_VECTOR]
	movaps xmm1, [edx]
	subps xmm1, xmm0

	mulps xmm1,xmm1
	movhlps xmm0, xmm1
	addss xmm0, xmm1
	shufps xmm1, xmm1, 0x55
	addss xmm0, xmm1

	movss xmm1, [eax+SPHERE_RADIUS]
	xor eax, eax
	mulss xmm1, [edx+SPHERE_RADIUS]
	comiss xmm1, xmm0
	
	;if( (R1+R2)^2 < Dist^2) then return false
	jnae SIMDx86Sphere_ContainsPoint_SSE_return_FALSE
	inc eax
	
	SIMDx86Sphere_ContainsPoint_SSE_return_FALSE:
	ret

END_SYMBOL(SIMDx86Sphere_ContainsPoint_SSE)
SIZE_SYMBOL SIMDx86Sphere_ContainsPoint_SSE

BEGIN_SYMBOL(SIMDx86Sphere_ContainsPolygon_SSE) ;int SIMDx86Sphere_ContainsPolygon(const SIMDx86Sphere* pSphere, const SIMDx86Polygon* pPoly)
	 mov [esp-4], ebx  ;save ebx
     mov eax, dword[esp+4] ;pSphere
     mov ebx, dword[esp+8] ;pPoly
     movaps xmm0, [eax+SPHERE_CENTER_VECTOR]
     movaps xmm1, [edx+POLYGON_VERTEX_A_OFFSET]
     subps xmm1, xmm0
     
     movss xmm3, [eax+SPHERE_RADIUS]
     mulss xmm3, [ebx+SPHERE_RADIUS]
     ;Comparing with vertex a
                movaps xmm0, [eax+SPHERE_CENTER_VECTOR]
                movaps xmm1, [ebx+POLYGON_VERTEX_A_OFFSET]
                subps xmm1, xmm0

                mulps xmm1,xmm1
                movhlps xmm0, xmm1
                addss xmm0, xmm1
                shufps xmm1, xmm1, 0x55
                addss xmm0, xmm1

                comiss xmm3, xmm0
                mov ecx,0x1
                jna SIMDx86Sphere_ContainsPolygon_SSE_1
                    mov ecx,0x0
                SIMDx86Sphere_ContainsPolygon_SSE_1:
     ;Comparing with vertex b
                movaps xmm0, [eax+SPHERE_CENTER_VECTOR]
                movaps xmm1, [ebx+POLYGON_VERTEX_B_OFFSET]
                subps xmm1, xmm0     ;the diff. between pSphere and vertex a

                mulps xmm1,xmm1
                movhlps xmm0, xmm1
                addss xmm0, xmm1
                shufps xmm1, xmm1, 0x55
                addss xmm0, xmm1

                comiss xmm3, xmm0
                mov ecx,0x1
                jna SIMDx86Sphere_ContainsPolygon_SSE_2
                    mov ecx,0x0
                SIMDx86Sphere_ContainsPolygon_SSE_2:
                and ecx,edx
     ;Comparing with vertex c
                movaps xmm0, [eax+SPHERE_CENTER_VECTOR]
                movaps xmm1, [ebx+POLYGON_VERTEX_C_OFFSET]
                subps xmm1, xmm0     ;the diff. between pSphere and vertex a

                mulps xmm1,xmm1
                movhlps xmm0, xmm1
                addss xmm0, xmm1
                shufps xmm1, xmm1, 0x55
                addss xmm0, xmm1

                comiss xmm3, xmm0
                mov edx,0x1
                jna SIMDx86Sphere_ContainsPolygon_SSE_3
                    mov edx,0x0
                SIMDx86Sphere_ContainsPolygon_SSE_3:
                and ecx,edx
     ;Returning
			   mov ebx, [esp-4]
               mov eax,ecx
               ret
END_SYMBOL(SIMDx86Sphere_ContainsPolygon_SSE)
SIZE_SYMBOL SIMDx86Sphere_ContainsPolygon_SSE

BEGIN_SYMBOL(SIMDx86Sphere_DistanceToPoint_SSE) ;float SIMDx86Sphere_DistanceToPoint(const SIMDx86Sphere* pSphere, const SIMDx86Vector* pVec)
     mov eax, dword[esp+4] ;pSphere
     mov edx, dword[esp+8] ;pVec
     movaps xmm0, [eax+SPHERE_CENTER_VECTOR]
     movaps xmm1, [edx]
     subps xmm1, xmm0     ;the diff. between pIn1 and pIn2
     
     mulps xmm1,xmm1
     movhlps xmm0, xmm1
     addss xmm0, xmm1
     shufps xmm1, xmm1, 0x55
     addss xmm0, xmm1 
     rsqrtss xmm0, xmm0
     rcpss xmm0, xmm0
     movss [esp-4], xmm0
     fld dword [esp-4]
     ret
END_SYMBOL(SIMDx86Sphere_DistanceToPoint_SSE)
SIZE_SYMBOL SIMDx86Sphere_DistanceToPoint_SSE

BEGIN_SYMBOL(SIMDx86Sphere_DistanceToPoint_HIPREC_SSE) ;float SIMDx86Sphere_DistanceToPoint(const SIMDx86Sphere* pSphere, const SIMDx86Vector* pVec)
     mov eax, dword[esp+4] ;pSphere
     mov edx, dword[esp+8] ;pVec
     movaps xmm0, [eax+SPHERE_CENTER_VECTOR]
     movaps xmm1, [edx]
     subps xmm1, xmm0     ;the diff. between pIn1 and pIn2
     
     mulps xmm1,xmm1
     movhlps xmm0, xmm1
     addss xmm0, xmm1
     shufps xmm1, xmm1, 0x55
     addss xmm0, xmm1 
     sqrtss xmm0, xmm0
     movss [esp-4], xmm0
     fld dword [esp-4]
     ret
END_SYMBOL(SIMDx86Sphere_DistanceToPoint_HIPREC_SSE)
SIZE_SYMBOL SIMDx86Sphere_DistanceToPoint_HIPREC_SSE

BEGIN_SYMBOL(SIMDx86Sphere_DistanceToPointSq_SSE) ;float SIMDx86Sphere_DistanceToPointSq(const SIMDx86Sphere* pSphere, const SIMDx86Vector* pVec)
     mov eax, dword[esp+4] ;pSphere
     mov edx, dword[esp+8] ;pVec
     movaps xmm0, [eax+SPHERE_CENTER_VECTOR]
     movaps xmm1, [edx]
     subps xmm1, xmm0     ;the diff. between pIn1 and pIn2
     
     mulps xmm1,xmm1
     movhlps xmm0, xmm1
     addss xmm0, xmm1
     shufps xmm1, xmm1, 0x55
     addss xmm0, xmm1

     movss [esp-4], xmm0
     fld dword [esp-4]
     ret
END_SYMBOL(SIMDx86Sphere_DistanceToPointSq_SSE)
SIZE_SYMBOL SIMDx86Sphere_DistanceToPointSq_SSE

BEGIN_SYMBOL(SIMDx86Sphere_DistanceToSphere_SSE) ;float SIMDx86Sphere_DistanceToSphere(const SIMDx86Sphere* pSphere1, const SIMDx86Sphere* pSphere2)
     mov eax, [esp+4] ;pSphere1
     mov edx, [esp+8] ;pSphere2
     movaps xmm0, [eax+SPHERE_CENTER_VECTOR]
     movaps xmm1, [edx+SPHERE_CENTER_VECTOR]
     movss xmm3, [eax+SPHERE_RADIUS]
     subps xmm1, xmm0     ;the diff. between pIn1 and pIn2

     mulps xmm1,xmm1
     addss xmm3, [edx+SPHERE_RADIUS]
     movhlps xmm0, xmm1
     addss xmm0, xmm1
     shufps xmm1, xmm1, 0x55
     addss xmm0, xmm1
     rsqrtss xmm0, xmm0
     rcpss xmm0, xmm0
     subss xmm0, xmm3
     movss [esp-4], xmm0
     fld dword [esp-4]
     ret
END_SYMBOL(SIMDx86Sphere_DistanceToSphere_SSE)
SIZE_SYMBOL SIMDx86Sphere_DistanceToSphere_SSE

BEGIN_SYMBOL(SIMDx86Sphere_DistanceToSphere_HIPREC_SSE) ;float SIMDx86Sphere_DistanceToSphere(const SIMDx86Sphere* pSphere1, const SIMDx86Sphere* pSphere2)
     mov eax, [esp+4] ;pSphere1
     mov edx, [esp+8] ;pSphere2
     movaps xmm0, [eax+SPHERE_CENTER_VECTOR]
     movaps xmm1, [edx+SPHERE_CENTER_VECTOR]
     movss xmm3, [eax+SPHERE_RADIUS]
     subps xmm1, xmm0     ;the diff. between pIn1 and pIn2

     mulps xmm1,xmm1
     addss xmm3, [edx+SPHERE_RADIUS]
     movhlps xmm0, xmm1
     addss xmm0, xmm1
     shufps xmm1, xmm1, 0x55
     addss xmm0, xmm1
     sqrtss xmm0, xmm0
     subss xmm0, xmm3
     movss [esp-4], xmm0
     fld dword [esp-4]
     ret
END_SYMBOL(SIMDx86Sphere_DistanceToSphere_HIPREC_SSE)
SIZE_SYMBOL SIMDx86Sphere_DistanceToSphere_HIPREC_SSE

BEGIN_SYMBOL(SIMDx86Sphere_DistanceToSphereSq_SSE) ;float SIMDx86Sphere_DistanceToSphereSq(const SIMDx86Sphere* pSphere1, const SIMDx86Sphere* pSphere2)
     mov eax, dword[esp+4] ;pSphere1
     mov edx, dword[esp+8] ;pSphere2
     movaps xmm0, [eax+SPHERE_CENTER_VECTOR]
     movaps xmm1, [edx+SPHERE_CENTER_VECTOR]
     movss xmm3, [eax+SPHERE_RADIUS]
     subps xmm1, xmm0     ;the diff. between pIn1 and pIn2

     mulps xmm1,xmm1
     addss xmm3, [edx+SPHERE_RADIUS]
     movhlps xmm0, xmm1
     addss xmm0, xmm1
     shufps xmm1, xmm1, 0x55
     addss xmm0, xmm1
     rsqrtss xmm0, xmm0
     rcpss xmm0, xmm0
     subss xmm0, xmm3
     mulss xmm0, xmm0
     movss [esp-4], xmm0
     fld dword [esp-4]
     ret
END_SYMBOL(SIMDx86Sphere_DistanceToSphereSq_SSE)
SIZE_SYMBOL SIMDx86Sphere_DistanceToSphereSq_SSE

BEGIN_SYMBOL(SIMDx86Sphere_DistanceToSphereSq_HIPREC_SSE) ;float SIMDx86Sphere_DistanceToSphereSq(const SIMDx86Sphere* pSphere1, const SIMDx86Sphere* pSphere2)
     mov eax, [esp+4] ;pSphere1
     mov edx, [esp+8] ;pSphere2
     movaps xmm0, [eax+SPHERE_CENTER_VECTOR]
     movaps xmm1, [edx+SPHERE_CENTER_VECTOR]
     movss xmm3, [eax+SPHERE_RADIUS]
     subps xmm1, xmm0     ;the diff. between pIn1 and pIn2

     mulps xmm1,xmm1
     addss xmm3, [edx+SPHERE_RADIUS]
     movhlps xmm0, xmm1
     addss xmm0, xmm1
     shufps xmm1, xmm1, 0x55
     addss xmm0, xmm1
     sqrtss xmm0, xmm0
     subss xmm0, xmm3
     mulss xmm0, xmm0
     movss [esp-4], xmm0
     fld dword [esp-4]
     ret
END_SYMBOL(SIMDx86Sphere_DistanceToSphereSq_HIPREC_SSE)
SIZE_SYMBOL SIMDx86Sphere_DistanceToSphereSq_HIPREC_SSE
