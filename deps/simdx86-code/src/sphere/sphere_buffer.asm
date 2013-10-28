; sphere_buffer.asm -- Buffer space for code overlays
; Written by Patrick Baggett, 2007 (baggett.patrick@gmail.com)
; Under LGPL License
; Part of SIMDx86 Project

section .text 

%include "SIMDx86asm.inc"

;List of symbols this module provides
EXPORT_SYMBOL(SIMDx86Sphere_SphereCollision)
EXPORT_SYMBOL(SIMDx86Sphere_ContainsPoint)
EXPORT_SYMBOL(SIMDx86Sphere_ContainsPolygon)
EXPORT_SYMBOL(SIMDx86Sphere_DistanceToPoint)
EXPORT_SYMBOL(SIMDx86Sphere_DistanceToPointSq)
EXPORT_SYMBOL(SIMDx86Sphere_DistanceToSphere)
EXPORT_SYMBOL(SIMDx86Sphere_DistanceToSphereSq)

; The "times OVERLAY_SIZE_MEDIUM db 0xC9" reserves a buffer space of code bytes to be overlayed, filling it with ret's	
BEGIN_SYMBOL(SIMDx86Sphere_SphereCollision)
	times OVERLAY_SIZE_MEDIUM db 0xc9
BEGIN_SYMBOL(SIMDx86Sphere_ContainsPoint)
	times OVERLAY_SIZE_MEDIUM db 0xc9
BEGIN_SYMBOL(SIMDx86Sphere_ContainsPolygon)
	times OVERLAY_SIZE_MEDIUM db 0xc9
BEGIN_SYMBOL(SIMDx86Sphere_DistanceToPoint)
	times OVERLAY_SIZE_MEDIUM db 0xc9
BEGIN_SYMBOL(SIMDx86Sphere_DistanceToPointSq)
	times OVERLAY_SIZE_MEDIUM db 0xc9
BEGIN_SYMBOL(SIMDx86Sphere_DistanceToSphere)
	times OVERLAY_SIZE_MEDIUM db 0xc9
BEGIN_SYMBOL(SIMDx86Sphere_DistanceToSphereSq)
	times OVERLAY_SIZE_MEDIUM db 0xc9
