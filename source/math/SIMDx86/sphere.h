/*
	sphere.h -- SIMDx86 Sphere Library
	Written by Patrick Baggett, 2005 (baggett.patrick@gmail.com)
	Under LGPL License
	Part of SIMDx86 Project
*/

#ifndef _SIMDX86_SPHERE_H
#define _SIMDX86_SPHERE_H

#include <SIMDx86/vector.h>
#include <SIMDx86/polygon.h>
#include <SIMDx86/align.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ALIGNMENT_PREFIX SIMDx86Sphere
{
	SIMDx86Vector Center;
	float radius;
	float __SIMD_pad__[3]; /* Pad to 16th byte for efficient SIMD operation */
} SIMDx86Sphere ALIGNMENT_SUFFIX;


int SIMDx86Sphere_SphereCollision(const SIMDx86Sphere* pIn1, const SIMDx86Sphere* pIn2);
int SIMDx86Sphere_ContainsPoint(const SIMDx86Sphere* pSphere, const SIMDx86Vector* pVec);
int SIMDx86Sphere_ContainsPolygon(const SIMDx86Sphere* pSphere, const SIMDx86Polygon* pPoly);
float SIMDx86Sphere_DistanceToPoint(const SIMDx86Sphere* pSphere, const SIMDx86Vector* pVec);
float SIMDx86Sphere_DistanceToPointSq(const SIMDx86Sphere* pSphere, const SIMDx86Vector* pVec);
float SIMDx86Sphere_DistanceToSphere(const SIMDx86Sphere* pSphere1, const SIMDx86Sphere* pSphere2);
float SIMDx86Sphere_DistanceToSphereSq(const SIMDx86Sphere* pSphere1, const SIMDx86Sphere* pSphere2);

#ifdef __cplusplus
}
#endif


#endif
