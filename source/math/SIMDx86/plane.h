/*
	plane.h -- SIMDx86 Plane Library
	Written by Patrick Baggett, 2005 (baggett.patrick@gmail.com)
	Under LGPL License
	Part of SIMDx86 Project
*/

#ifndef _SIMDX86_PLANE_H
#define _SIMDX86_PLANE_H

#include <SIMDx86/align.h>
#include <SIMDx86/vector.h>
#include <SIMDx86/polygon.h>
#include <SIMDx86/sphere.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
	Plane equation: ax + by + cz + dw = 0
	w is usually 1.0f, so it can usually be simplified to: ax + by + cz + d

*/
typedef struct ALIGNMENT_PREFIX SIMDx86Plane
{
	float a, b, c, d;
} SIMDx86Plane ALIGNMENT_SUFFIX;

void SIMDx86Plane_FromPolygon(SIMDx86Plane* pOut, const SIMDx86Polygon* pPoly);
void SIMDx86Plane_FromPoints(SIMDx86Plane* pOut, const SIMDx86Vector* pA, const SIMDx86Vector* pB,const SIMDx86Vector* pC);
float SIMDx86Plane_DistToPoint(const SIMDx86Plane* pPlane, const SIMDx86Vector* pPoint);
float SIMDx86Plane_DistToSphere(const SIMDx86Plane* pPlane, const SIMDx86Sphere* pSphere);
float SIMDx86Plane_DistToOrigin(const SIMDx86Plane* pPlane);
float SIMDx86Plane_Dot(const SIMDx86Plane* pPlane, const SIMDx86Vector* pVec);
float SIMDx86Plane_Dot4(const SIMDx86Plane* pPlane, const float* pVec4);
float SIMDx86Plane_DotNormal(const SIMDx86Plane* pPlane, const SIMDx86Vector* pVec);
float SIMDx86Plane_DotPlane(const SIMDx86Plane* pPlane1, const SIMDx86Plane* pPlane2);
void SIMDx86Plane_Normalize(SIMDx86Plane* pOut);
void SIMDx86Plane_NormalizeOf(SIMDx86Plane* pOut, SIMDx86Plane* pIn);
SIMDx86Vector* SIMDx86Plane_IntersectLineSegment(const SIMDx86Plane* pPlane, const SIMDx86Vector* pStart, const SIMDx86Vector* pEnd, SIMDx86Vector* pIntersectionPoint);

#ifdef __cplusplus
}
#endif

#endif
