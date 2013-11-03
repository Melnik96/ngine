/*
	sphere.c -- SIMDx86 Sphere Library
	Written by Patrick Baggett, 2005 (baggett.patrick@gmail.com)
	Under LGPL License
	Part of SIMDx86 Project
*/

#include <SIMDx86/sphere.h>

int SIMDx86Sphere_SphereCollision(const SIMDx86Sphere* pIn1, const SIMDx86Sphere* pIn2)
{
	SIMDx86Vector dist;

	/* Find the distance squared between the two sphere */
	SIMDx86Vector_DiffOf(&dist, &pIn1->Center, &pIn2->Center);

	/* Compare the sum of the radii squared with the distance squared */
	return ((pIn1->radius+pIn2->radius)*(pIn1->radius+pIn2->radius)) >= SIMDx86Vector_LengthSq(&dist);
}

int SIMDx86Sphere_ContainsPoint(const SIMDx86Sphere* pSphere, const SIMDx86Vector* pVec)
{
	SIMDx86Vector dist;

	/* Find the distanced squared between the spheres and the point */
	SIMDx86Vector_DiffOf(&dist, &pSphere->Center, pVec);

	/* Compare the radius squared with distance square between the two */
	return SIMDx86Vector_LengthSq(&dist) <= (pSphere->radius*pSphere->radius);
}

int SIMDx86Sphere_ContainsPolygon(const SIMDx86Sphere* pSphere, const SIMDx86Polygon* pPoly)
{
	return SIMDx86Sphere_ContainsPoint(pSphere, &pPoly->a) && SIMDx86Sphere_ContainsPoint(pSphere, &pPoly->b) && SIMDx86Sphere_ContainsPoint(pSphere, &pPoly->c);
}

float SIMDx86Sphere_DistanceToPoint(const SIMDx86Sphere* pSphere, const SIMDx86Vector* pVec)
{
	return SIMDx86Vector_Distance(&pSphere->Center, pVec);
}

float SIMDx86Sphere_DistanceToPointSq(const SIMDx86Sphere* pSphere, const SIMDx86Vector* pVec)
{
	SIMDx86Vector v;

	SIMDx86Vector_DiffOf(&v, &pSphere->Center, pVec);

	return SIMDx86Vector_LengthSq(&v);
}

float SIMDx86Sphere_DistanceToSphere(const SIMDx86Sphere* pSphere1, const SIMDx86Sphere* pSphere2)
{
	SIMDx86Vector distvec;
	float dist;

	/* Find the distance vector between the two spheres */
	SIMDx86Vector_DiffOf(&distvec, &pSphere1->Center, &pSphere2->Center);

	/* Get magnitude of this vector */
	dist = SIMDx86Vector_Length(&distvec);

	/* return distance between spheres minus sum of radii */
	return dist - (pSphere1->radius + pSphere2->radius);
}

float SIMDx86Sphere_DistanceToSphereSq(const SIMDx86Sphere* pSphere1, const SIMDx86Sphere* pSphere2)
{
	SIMDx86Vector distvec;
	float dist;

	/* Find the distance vector between the two spheres */
	SIMDx86Vector_DiffOf(&distvec, &pSphere1->Center, &pSphere2->Center);

	/* real distance = length - rsum */
	dist = SIMDx86Vector_Length(&distvec) - (pSphere1->radius + pSphere2->radius);

	return dist * dist;
}
