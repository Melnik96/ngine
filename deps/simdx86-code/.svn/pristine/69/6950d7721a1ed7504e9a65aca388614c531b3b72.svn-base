/*
	math_compliance.c -- SIMDx86 Math compliance calculation
*/
#include <SIMDx86/SIMDx86.h>
#include <stdio.h>
#include <math.h>

static void test_sqrt();
static void test_sqrtf();
static void test_rsqrt();
static void test_rsqrtf();

#define EPSILON 0.001

int main()
{
	unsigned int ISAs;
	int i,j;
	printf("Official libSIMDx86 Math Compliance Test\n"
	"Built against libSIMDx86 v%d.%d.%d (%s)\n",
	SIMDx86_GetMajorVersion(),
	SIMDx86_GetMinorVersion(),
	SIMDx86_GetRevisionVersion(),
	SIMDx86_GetBuildString()
	);

	/* Print out epsilon value */
	printf("Using EPSILON of %g\n", EPSILON);

	/* Get all ISAs supported */
	ISAs = SIMDx86_GetCPUSupportedISA();

	/* Try each ISA... */
	for(i=0; i<SIMDX86ISA_MAX; i++)
	{
		/* Only execute this code path if supported by hardware */
		if((SIMDX86ISA_ISSUPPORTED(ISAs, i)))
		{
			/* We need to test both high-precision (j == 1) and low precision (j == 0)*/
			for(j=0; j<2; j++)
			{
				unsigned int flags;
				if(j == 1)
					flags = SIMDX86FLAGS_HIPREC;
				else
					flags = 0x00;

				printf("Testing ISA: \"%s\" %s\n", SIMDx86_GetISAString(i), flags == 0? "" : "(HIPREC)"); 
				printf("=================\n");
				if(SIMDx86_Initialize(i, flags) == 0)
					printf("FAILED TO INITIALIZE. SKIPPING.\n\n");
				else
				{
					test_sqrt();
					test_sqrtf();
					test_rsqrt();
					test_rsqrtf();
				}
				printf("=================\n");
			}
		}
	}


	return;
}

/* Value used as argument */
#define VALUE 27.0
#define VALUE_F ((float)VALUE)

static void test_sqrt()
{
	double x = SIMDx86_sqrt(VALUE);
	double y = sqrt(VALUE);

	printf("sqrt(%g): %g vs %g libc: %s\n",VALUE, x, y, fabs(x-y) > EPSILON ? "fail" : "pass"); 
}

static void test_sqrtf()
{
	float x = SIMDx86_sqrtf(VALUE_F);
	float y = sqrtf(VALUE_F);
	printf("sqrtf(%f): %f vs %f libc: %s\n",VALUE, x, y, fabsf(x-y) > EPSILON ? "fail" : "pass"); 
}

static void test_rsqrt()
{
	double x = SIMDx86_rsqrt(VALUE);
	double y = 1.0f / sqrt(VALUE);
	printf("rsqrt(%g): %g vs %g libc: %s\n",VALUE, x, y, fabs(x-y) > EPSILON ? "fail" : "pass"); 
}

static void test_rsqrtf()
{
	float x = SIMDx86_rsqrtf(VALUE_F);
	float y = 1.0f / sqrtf(VALUE_F);
	printf("rsqrtf(%f): %f vs %f libc: %s\n",VALUE_F, x, y, fabsf(x-y) > EPSILON ? "fail" : "pass"); 
}

