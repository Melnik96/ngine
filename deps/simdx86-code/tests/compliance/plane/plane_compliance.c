#include <stdio.h>
#include <SIMDx86/SIMDx86.h>

static void TestFromPolygon();
static void TestFromPoints();
static void TestDistToPoint();
static void TestDistToSphere();

int main()
{
	printf("Official libSIMDx86 Plane Compliance Test\n"
	"Built against libSIMDx86 v%d.%d.%d (%s)\n",
	SIMDx86_GetMajorVersion(),
	SIMDx86_GetMinorVersion(),
	SIMDx86_GetRevisionVersion(),
	SIMDx86_GetBuildString()
	);

	TestFromPolygon();
	TestFromPoints();
	TestDistToPoint();
	TestDistToSphere();
}


static void TestFromPolygon()
{
	SIMDx86Polygon p;
	SIMDx86Plane output;

	p.a.x = 5.0f;
	p.a.y = 15.0f;
	p.a.z = 25.0f;

	p.b.x = -15.0f;
	p.b.y = -15.0f;
	p.b.z = -15.0f;

	p.c.x = -25.0f;
	p.c.y = +25.0f;
	p.c.z = -25.0f;


	SIMDx86Plane_FromPolygon(&output, &p);

	printf("Testing FromPolygon()...\n");
	printf("a=%f b=%f c=%f d=%f\n", output.a, output.b, output.c, output.d);
}

static void TestFromPoints()
{
	SIMDx86Vector a, b, c;
	SIMDx86Plane output;

	a.x = 5.0f;
	a.y = 15.0f;
	a.z = 25.0f;

	b.x = -15.0f;
	b.y = -15.0f;
	b.z = -15.0f;

	c.x = -25.0f;
	c.y = +25.0f;
	c.z = -25.0f;

	SIMDx86Plane_FromPoints(&output, &a, &b, &c);
	printf("Testing FromPoints()...\n");
	printf("a=%f b=%f c=%f d=%f\n", output.a, output.b, output.c, output.d);
}

static void TestDistToPoint()
{
	SIMDx86Vector a;
	SIMDx86Plane p;

#if 0
	a.x = 5.0f;
	a.y = 15.0f;
	a.z = 25.0f;


	/* Contrived #'s, I know */
	p.a = 2.0f;
	p.b = 4.0f;
	p.c = 8.0f;
	p.d = 16.0f;
#endif

	a.x = 1.0f;
	a.y = 0.0f;
	a.z = 0.0f;
	
	p.a = -1.0f;
	p.b = 0.0f;
	p.c = 0.0f;
	p.d = 2.0f;

	/*
		x87:           		9.668565
		SSE (Low Prec): 	9.666290 (error 0.02%)
		SSE (High Prec):	9.668565
	*/

	printf("Testing DistToPoint()...\n");
	printf("Distance = %f\n", SIMDx86Plane_DistToPoint(&p, &a));


//	SIMDx86Vector_Normalize(&a);
//	SIMDx86Plane_Normalize(&p);

	printf("test2: %f\n", a.x*p.a + a.y*p.b + a.z*p.c + p.d);
}

static void TestDistToSphere()
{
	SIMDx86Sphere s;
	SIMDx86Plane p;

	s.Center.x = 5.0f;
	s.Center.y = 15.0f;
	s.Center.z = 25.0f;
	s.radius = 5.0f;
	
	/* Contrived #'s, I know */
	p.a = 2.0f;
	p.b = 4.0f;
	p.c = 8.0f;
	p.d = 16.0f;

	/*
		x87:           		9.668565
		SSE (Low Prec): 	9.666290 (error 0.02%)
		SSE (High Prec):	9.668565


	*/

	printf("Testing DistToSphere()...\n");
	printf("Distance = %f\n", SIMDx86Plane_DistToSphere(&p, &s));

}
