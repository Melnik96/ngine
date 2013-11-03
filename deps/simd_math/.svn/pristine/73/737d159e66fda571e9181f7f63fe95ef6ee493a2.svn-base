#include <stdio.h>
#include <SIMDx86/SIMDx86.h>

/*

	TO TEST:
	void SIMDx86Quaternion_Normalize(SIMDx86Quaternion* pQuat);
	void SIMDx86Quaternion_NormalizeOf(SIMDx86Quaternion* pOut, const SIMDx86Quaternion* pQuat);
	float  SIMDx86Quaternion_Length(const SIMDx86Quaternion* pQuat);
	float  SIMDx86Quaternion_LengthSq(const SIMDx86Quaternion* pQuat);
	void SIMDx86Quaternion_Multiply(SIMDx86Quaternion* pLeft, const SIMDx86Quaternion* pRight);
	void SIMDx86Quaternion_MultiplyOf(SIMDx86Quaternion* pOut, const SIMDx86Quaternion* pLeft, const SIMDx86Quaternion* pRight);
	void SIMDx86Quaternion_Conjugate(SIMDx86Quaternion* pQuat);
	void SIMDx86Quaternion_ConjugateOf(SIMDx86Quaternion* pOut, const SIMDx86Quaternion* pSrc);
	void SIMDx86Quaternion_ToMatrix(SIMDx86Matrix* pMat, const SIMDx86Quaternion* pQuat);
	void SIMDx86Quaternion_Rotate(SIMDx86Quaternion* pOut, float rads, float x, float y, float z);
	void SIMDx86Quaternion_Slerp(SIMDx86Quaternion* pOut, const SIMDx86Quaternion* pSrc1, const SIMDx86Quaternion* pSrc2, float scalar);
*/

SIMDx86Quaternion out, in1, in2;

static void reset()
{
	in1.x = 1.0f;
	in1.y = 2.0f;
	in1.z = 3.0f;
	in1.w = 4.0f;

	in2.x = 10.0f;
	in2.y = 20.0f;
	in2.z = 30.0f;
	in2.w = 40.0f;

	out.x = 0.0f;
	out.y = 0.0f;
	out.z = 0.0f;
	out.w = 0.0f;

}

static void printq(SIMDx86Quaternion* pQ)
{
	printf("%f %f %f %f\n", pQ->x, pQ->y, pQ->x, pQ->w);
}

static void printm(SIMDx86Matrix* pM)
{
	printf(
	"%f %f %f %f\n"
	"%f %f %f %f\n"
	"%f %f %f %f\n"
	"%f %f %f %f\n",
	pM->m[ 0], pM->m[ 1], pM->m[ 2], pM->m[ 3],
	pM->m[ 4], pM->m[ 5], pM->m[ 6], pM->m[ 7],
	pM->m[ 8], pM->m[ 9], pM->m[10], pM->m[11],
	pM->m[12], pM->m[13], pM->m[14], pM->m[15]);

}


static void TestNormalize()
{
	reset();
	printf("Testing Normalize()...");
	SIMDx86Quaternion_Normalize(&in1);
	printq(&in1);
}

static void TestNormalizeOf()
{
	reset();
	printf("Testing NormalizeOf()...");
	SIMDx86Quaternion_NormalizeOf(&out, &in1);
	printq(&out);
}

static void TestLength()
{
	reset();
	printf("Testing Length()...%f\n", SIMDx86Quaternion_Length(&in1));
}

static void TestLengthSq()
{
	reset();
	printf("Testing LengthSq()...%f\n", SIMDx86Quaternion_LengthSq(&in1));
}

static void TestMultiply()
{
	reset();
	printf("Testing Multiply()...");
	SIMDx86Quaternion_Multiply(&in1, &in2);
	printq(&in1);
}

static void TestMultiplyOf()
{
	reset();
	printf("Testing MultiplyOf()...");
	SIMDx86Quaternion_MultiplyOf(&out, &in1, &in2);
	printq(&out);
}

static void TestConjugate()
{
	reset();
	printf("Testing Conjugate()...");
	SIMDx86Quaternion_Conjugate(&in1);
	printq(&in1);
}

static void TestConjugateOf()
{
	reset();
	printf("Testing ConjugateOf()...");
	SIMDx86Quaternion_ConjugateOf(&out, &in1);
	printq(&out);
}

static void TestToMatrix()
{
	SIMDx86Matrix m;

	reset();
	printf("Testing ToMatrix()...");
	SIMDx86Quaternion_ToMatrix(&m, &in1);
	printm(&m);
}

static void TestRotate()
{
	reset();
	printf("Testing Rotate()...");
	SIMDx86Quaternion_Rotate(&out, 3.1415, 0.0f, 0.333f, 0.666f);
	printq(&out);
}

static void TestSlerp()
{
	reset();

	SIMDx86Quaternion_Rotate(&in1, 3.1415, 1.0f, 0.0f, 0.0f);
	SIMDx86Quaternion_Rotate(&in2, 2*3.1415, 1.0f, 0.0f, 0.0f);

	printf("Testing Slerp()...");
	SIMDx86Quaternion_Slerp(&out, &in1, &in2, 0.5f);
	printq(&out);
}


int main()
{
	printf("Official libSIMDx86 Quaternion Compliance Test\n"
	"Built against libSIMDx86 v%d.%d.%d (%s)\n",
	SIMDx86_GetMajorVersion(),
	SIMDx86_GetMinorVersion(),
	SIMDx86_GetRevisionVersion(),
	SIMDx86_GetBuildString()
	);

	TestNormalize();
	TestNormalizeOf();
	TestLength();
	TestLengthSq();
	TestMultiply();
	TestMultiplyOf();
	TestConjugate();
	TestConjugateOf();
	TestToMatrix();
	TestRotate();
	TestSlerp();

}
