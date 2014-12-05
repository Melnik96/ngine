/*
	polygon.c -- SIMDx86 Polygon Library
	Written by Patrick Baggett, 2005 (baggett.patrick@gmail.com)
	Under LGPL License
	Part of SIMDx86 Project
*/

#include <SIMDx86/polygon.h>

void SIMDx86Polygon_PlaneNormal(SIMDx86Vector* pNormal, const SIMDx86Polygon* pPoly)
{
	SIMDx86Vector d0, d1;

	/* d0 = a - b; d1 = c - b*/
	SIMDx86Vector_DiffOf(&d0, &pPoly->a, &pPoly->b);
	SIMDx86Vector_DiffOf(&d1, &pPoly->c, &pPoly->b);

	/* Normal = d0 x d1 */
	SIMDx86Vector_CrossOf(pNormal, &d0, &d1);
}
