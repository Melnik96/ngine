/*
	polygon_compliance.c -- Official libSIMDx86 Polygon Compliance Test
	Written by Patrick Baggett, 2005 (baggett.patrick@gmail.com)
	Part of SIMDx86
	Under LGPL License
*/

#include <SIMDx86/SIMDx86.h>
#include <stdio.h>

SIMDx86Vector out;
SIMDx86Polygon in;

static void reset()
{

	out.x = out.y = out.z = 0.0f;

	in.a.x = 5.0;
	in.a.y = 0.0;
	in.a.z = 0.0;

	in.b.x = 5.0;
	in.b.y = 0.0;
	in.b.z = 5.0;

	in.c.x = 0.0;
	in.c.y = 0.0;
	in.c.z = 5.0;

}

static void printp(const SIMDx86Polygon* pPoly)
{

	printf("a: %f %f %f\n", pPoly->a.x, pPoly->a.y, pPoly->a.z );
	printf("b: %f %f %f\n", pPoly->b.x, pPoly->b.y, pPoly->b.z );
	printf("c: %f %f %f\n", pPoly->c.x, pPoly->c.y, pPoly->c.z );

}

static void printv(const SIMDx86Vector* pVec)
{
	printf("%f %f %f\n", pVec->x, pVec->y, pVec->z);
}

static void TestPlaneNormal()
{
	reset();
	printf("Testing PlaneNormal()\n");
	SIMDx86Polygon_PlaneNormal(&out, &in1);
	printp(&in);
	printv(&out);
}

int main()
{
	printf("Official libSIMDx86 Vector Compliance Test\n"
	"Built against libSIMDx86 v%d.%d.%d (%s)\n",
	SIMDx86_GetMajorVersion(),
	SIMDx86_GetMinorVersion(),
	SIMDx86_GetRevisionVersion(),
	SIMDx86_GetBuildString()
	);

	TestPlaneNormal();
	fgetc(stdin);
}
