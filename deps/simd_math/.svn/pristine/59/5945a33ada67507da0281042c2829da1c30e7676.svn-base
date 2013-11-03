/*
	vector_compliance.c -- Official libSIMDx86 Vector Compliance Test
	Written by Patrick Baggett, 2005 (baggett.patrick@gmail.com)
	Part of SIMDx86
	Under LGPL License
*/

#include <SIMDx86/SIMDx86.h>
#include <stdio.h>

SIMDx86Vector out, in1, in2;

static void reset()
{
	out.x = out.y = out.z = 0.0f;

	in1.x = 10.0f;
	in1.y = 20.0f;
	in1.z = 30.0f;

	in2.x = 1.0f;
	in2.y = 2.0f;
	in2.z = 3.0f;
}

static void printv(const SIMDx86Vector* pVec)
{
	printf("%f %f %f\n", pVec->x, pVec->y, pVec->z);
}

static void TestSum()
{
	reset();
	printf("Testing Sum()...");
	SIMDx86Vector_Sum(&in1, &in2);
	printv(&in1);
}

static void TestSumOf()
{
	reset();
	printf("Testing SumOf()...");
	SIMDx86Vector_SumOf(&out, &in1, &in2);
	printv(&out);
}

static void TestDiff()
{
	reset();
	printf("Testing Diff()...");
	SIMDx86Vector_Diff(&in1, &in2);
	printv(&in1);
}

static void TestDiffOf()
{
	reset();
	printf("Testing DiffOf()...");
	SIMDx86Vector_DiffOf(&out, &in1, &in2);
	printv(&out);
}

static void TestScale()
{
	reset();
	printf("Testing Scale()...");
	SIMDx86Vector_Scale(&in1, 100.0f);
	printv(&in1);
}

static void TestScaleOf()
{
	reset();
	printf("Testing ScaleOf()...");
	SIMDx86Vector_ScaleOf(&out, &in1, 100.0f);
	printv(&out);
}

static void TestDot()
{
	reset();
	printf("Testing Dot()...%f\n", SIMDx86Vector_Dot(&in1, &in2));

}

static void TestDot4()
{
	float in1[4] = { 1.0f, 2.0f, 3.0f, 4.0f };
	float in2[4] = { 5.0f, 6.0f, 7.0f, 8.0f };
	
	/* Should be 5 + 12 + 21 + 32 = 70 */
	printf("Testing Dot4()...%f\n", SIMDx86Vector_Dot4(in1, in2));

}


static void TestLengthSq()
{
	reset();
	printf("Testing LengthSq()...%f\n", SIMDx86Vector_LengthSq(&in2));
}

static void TestLength()
{
	reset();
	printf("Testing Length()...%f\n", SIMDx86Vector_Length(&in2));
}

static void TestCross()
{
	in1.x = 1.0f; in1.y = 0.0f; in1.z = 0.0f;
	in2.x = 0.0f; in2.y = 0.0f; in2.z = 1.0f;

	printf("Testing Cross()\n");
	SIMDx86Vector_Cross(&in1, &in2);
	printv(&in1);

}

static void TestCrossOf()
{
	in1.x = 1.0f; in1.y = 0.0f; in1.z = 0.0f;
	in2.x = 0.0f; in2.y = 0.0f; in2.z = 1.0f;

	printf("Testing CrossOf()\n");
	SIMDx86Vector_CrossOf(&out, &in1, &in2);
	printv(&out);
}

static void TestNormalize()
{
	reset();
	printf("Testing Normalize()\n");
	SIMDx86Vector_Normalize(&in1);
	printv(&in1);
}

static void TestNormalizeOf()
{
	reset();
	printf("Testing NormalizeOf()\n");
	SIMDx86Vector_NormalizeOf(&out, &in1);
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

	TestSum();
	TestSumOf();
	TestDiff();
	TestDiffOf();
	TestScale();
	TestScaleOf();
	TestDot();
	TestDot4();
	TestLengthSq();
	TestLength();
	TestCross();
	TestCrossOf();
	TestNormalize();
	TestNormalizeOf();
	fgetc(stdin);
}
