
#include <SIMDx86/SIMDx86.h>
#include <stdio.h>

#define TEST_ALIGNED

#if defined(TEST_ALIGNED)

	#undef SIMDx86Matrix_Sum
	#undef SIMDx86Matrix_SumOf
	#undef SIMDx86Matrix_Diff
	#undef SIMDx86Matrix_DiffOf
	#undef SIMDx86Matrix_Scale
	#undef SIMDx86Matrix_ScaleOf
	#undef SIMDx86Matrix_Multiply
	#undef SIMDx86Matrix_MultiplyOf
	#undef SIMDx86Matrix_Transpose
	#undef SIMDx86Matrix_TransposeOf
	#undef SIMDx86Matrix_VectorMultiply
	#undef SIMDx86Matrix_VectorMultiplyOf
	#undef SIMDx86Matrix_Vector4Multipy
	#undef SIMDx86Matrix_Vector4MultiplyOf

	#define SIMDx86Matrix_Sum       			SIMDx86Matrix_AlignedSum
	#define SIMDx86Matrix_SumOf                 SIMDx86Matrix_AlignedSumOf
	#define SIMDx86Matrix_Diff                  SIMDx86Matrix_AlignedDiff
	#define SIMDx86Matrix_DiffOf                SIMDx86Matrix_AlignedDiffOf
	#define SIMDx86Matrix_Scale                 SIMDx86Matrix_AlignedScale
	#define SIMDx86Matrix_ScaleOf               SIMDx86Matrix_AlignedScaleOf
	#define SIMDx86Matrix_Multiply              SIMDx86Matrix_AlignedMultiply
	#define SIMDx86Matrix_MultiplyOf            SIMDx86Matrix_AlignedMultiplyOf
	#define SIMDx86Matrix_Transpose             SIMDx86Matrix_AlignedTranspose
	#define SIMDx86Matrix_TransposeOf           SIMDx86Matrix_AlignedTransposeOf
	#define SIMDx86Matrix_VectorMultiply        SIMDx86Matrix_AlignedVectorMultiply
	#define SIMDx86Matrix_VectorMultiplyOf      SIMDx86Matrix_AlignedVectorMultiplyOf
	#define SIMDx86Matrix_Vector4Multipy        SIMDx86Matrix_AlignedVector4Multipy
	#define SIMDx86Matrix_Vector4MultiplyOf     SIMDx86Matrix_AlignedVector4MultiplyOf

#endif

SIMDx86Matrix out, in1, in2;
SIMDx86Vector v, outv;

static void reset()
{
	memset(&out, 0, sizeof(out));

	in1.m[ 0] = 1.0f;
	in1.m[ 1] = 0.0f;
	in1.m[ 2] = 0.0f;
	in1.m[ 3] = 0.0f;

	in1.m[ 4] = 0.0f;
	in1.m[ 5] = 1.0f;
	in1.m[ 6] = 0.0f;
	in1.m[ 7] = 0.0f;

	in1.m[ 8] = 0.0f;
	in1.m[ 9] = 0.0f;
	in1.m[10] = 1.0f;
	in1.m[11] = 0.0f;

	in1.m[12] = 0.0f;
	in1.m[13] = 0.0f;
	in1.m[14] = 0.0f;
	in1.m[15] = 1.0f;

	in2.m[ 0] = 1.0f;
	in2.m[ 1] = 0.0f;
	in2.m[ 2] = 0.0f;
	in2.m[ 3] = 0.0f;

	in2.m[ 4] = 0.0f;
	in2.m[ 5] = 1.0f;
	in2.m[ 6] = 0.0f;
	in2.m[ 7] = 0.0f;

	in2.m[ 8] = 0.0f;
	in2.m[ 9] = 0.0f;
	in2.m[10] = 1.0f;
	in2.m[11] = 0.0f;

	in2.m[12] = 10.0f;
	in2.m[13] = 20.0f;
	in2.m[14] = 30.0f;
	in2.m[15] = 1.0f;


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

static void printv(SIMDx86Vector* pV)
{
	printf(
	"%f %f %f\n", pV->x, pV->y, pV->z);
}
static void printv4(float v[4])
{
	printf(
	"%f %f %f %f\n", v[0], v[1], v[2], v[3]);
}

static void TestSum()
{
	reset();
	printf("Testing Sum()...\n");
	SIMDx86Matrix_Sum(&in1, &in2);
	printm(&in1);
}

static void TestSumOf()
{
	reset();
	printf("Testing SumOf()...\n");
	SIMDx86Matrix_SumOf(&out, &in1, &in2);
	printm(&out);
}

static void TestDiff()
{
	reset();
	printf("Testing Diff()...\n");
	SIMDx86Matrix_Diff(&in1, &in2);
	printm(&in1);
}

static void TestDiffOf()
{
	reset();
	printf("Testing DiffOf()...\n");
	SIMDx86Matrix_DiffOf(&out, &in1, &in2);
	printm(&out);
}

static void TestScale()
{
	reset();
	printf("Testing Scale()...\n");
	SIMDx86Matrix_Scale(&in2, 10.0f);
	printm(&in2);
}

static void TestScaleOf()
{
	reset();
	printf("Testing ScaleOf()...\n");
	SIMDx86Matrix_ScaleOf(&out, &in2, 10.0f);
	printm(&out);
}

static void TestMultiply()
{
	reset();
	printf("Testing Multiply()...\n");
	SIMDx86Matrix_Multiply(&in1, &in2);
	printm(&in1);
}

static void TestMultiplyOf()
{
	reset();
	printf("Testing MultiplyOf()...\n");
	SIMDx86Matrix_MultiplyOf(&out, &in1, &in2);
	printm(&out);
}

static void TestTranspose()
{
	int i;
	for(i=0; i<16; i++)
	{
		in2.m[i] = (float)i;
	}
	printf("Testing Transpose()...\n");
	SIMDx86Matrix_Transpose(&in2);
	printm(&in2);
}

static void TestTransposeOf()
{
	int i;
	
	for(i=0; i<16; i++)
	{
		in2.m[i] = (float)i;
	}

	printf("Testing TransposeOf()...\n");
	SIMDx86Matrix_TransposeOf(&out, &in2);
	printm(&out);
}

static void TestVectorMultiply()
{
	v.x = 5.0f;
	v.y = 10.0f;
	v.z = 15.0f;

	reset();
	printf("Testing VectorMultiply()...\n");
	SIMDx86Matrix_VectorMultiply(&v, &in2);
	printv(&v);
}

static void TestVectorMultiplyOf()
{
	v.x = 5.0f;
	v.y = 10.0f;
	v.z = 15.0f;

	reset();
	printf("Testing VectorMultiplyOf()...\n");
	SIMDx86Matrix_VectorMultiplyOf(&outv, &v, &in2);
	printv(&outv);
}

static void TestVector4Multiply()
{
	float ALIGNED v[4] = { 5.0f, 10.0f, 15.0f, 20.0f };
	reset();
	printf("Testing Vector4Multiply()...\n");
	SIMDx86Matrix_Vector4Multiply(v, &in2);
	printv4(v);
}

static void TestVector4MultiplyOf()
{
	float ALIGNED v[4] = { 5.0f, 10.0f, 15.0f, 20.0f };
	float ALIGNED s[4];

	reset();
	printf("Testing Vector4Multiply()...\n");
	SIMDx86Matrix_Vector4MultiplyOf(s, v, &in2);
	printv4(s);
}

int main()
{
	printf("Official libSIMDx86 Matrix Compliance Test\n"
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
	TestMultiply();
	TestMultiplyOf();
	TestTranspose();
	TestTransposeOf();
	TestVectorMultiply();
	TestVectorMultiplyOf();
	TestVector4Multiply();
	TestVector4MultiplyOf();

	fgetc(stdin);
	return;
}
