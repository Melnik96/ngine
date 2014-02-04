#include "vector.h"
#include "matrix.h"

void vec3_sum(vec3* _out, const vec3* _in) {
  _out->x += _in->x;
  _out->y += _in->y;
  _out->z += _in->z;
}
void vec3_sum_of(vec3* _out, const vec3* _in1, const vec3* _in2) {
  _out->x = _in1->x + _in2->x;
  _out->y = _in1->y + _in2->y;
  _out->z = _in1->z + _in2->z;
}
void vec3_diff_of(vec3* pOut, const vec3* pLeft, const vec3* pRight) {
  pOut->x = pLeft->x - pRight->x;
  pOut->y = pLeft->y - pRight->y;
  pOut->z = pLeft->z - pRight->z;
}
void vec3_cross_of(vec3* _out, const vec3* _in1, const vec3* _in2) {
  _out->x = (_in1->y * _in2->z) - (_in1->z * _in2->y);
  _out->y = (_in1->z * _in2->x) - (_in1->x * _in2->z);
  _out->z = (_in1->x * _in2->y) - (_in1->y * _in2->x);
}
void vec3_mul_coef_of(vec3* _out, const vec3* _in1, const int32_t _coef) {
  _out->x = _in1->x * _coef;
  _out->y = _in1->y * _coef;
  _out->z = _in1->z * _coef;
}
vec3* vec3r_mul_coef_of(const vec3* _in1, const int32_t _coef) {
  vec3 _out;
  vec3_mul_coef_of(&_out, _in1, _coef);
  return &_out;
}
vec3* vec3r_cross_of(const vec3* _in1, const vec3* _in2) {
  vec3 _out;
  vec3_cross_of(&_out, _in1, _in2);
  return &_out;
}
vec3* vec3r_sum_of(const vec3* _in1, const vec3* _in2) {
  vec3 _out;
  vec3_sum_of(&_out, _in1, _in2);
  return &_out;
}

vec3* qrot(vec4* q, vec3* v) {
//         return v + 2.0*cross(q.xyz, cross(q.xyz,v) + q.w*v);
  return vec3r_sum_of(v, vec3r_mul_coef_of(vec3r_cross_of(q, vec3r_sum_of(vec3r_cross_of(q,v), vec3r_mul_coef_of(v, q->w))), 2.f));
}

void vec3_mat4_mul_of(float* pOut4D, const float* pIn4D, const mat4* pMat)
{
	#if defined(USE_SSE)
	asm(
	"movaps (%1), %%xmm4\n"
	"movaps %%xmm4, %%xmm5\n"
	"movaps %%xmm4, %%xmm6\n"
	"movaps  %%xmm4, %%xmm7\n"
	"shufps $0x00, %%xmm4, %%xmm4\n"
	"shufps $0x55, %%xmm5, %%xmm5\n"
	"shufps $0xAA, %%xmm6, %%xmm6\n"
	"shufps $0xFF, %%xmm7, %%xmm7\n"

	/* Multiply with each row */
	"mulps   (%0), %%xmm4\n"
	"mulps 16(%0), %%xmm5\n"
	"mulps 32(%0), %%xmm6\n"
	"mulps 48(%0), %%xmm7\n"

	/* Sum results */
	"addps %%xmm4, %%xmm5\n"
	"addps %%xmm6, %%xmm7\n"
	"addps %%xmm5, %%xmm7\n"

	/* Store translated vector */
	"movaps %%xmm7, (%2)\n"
	:
	: "r" (pMat), "r" (pIn4D), "r" (pOut4D)
	);
	#elif defined(USE_3DNOW)

	asm(
	"movd   (%0), %%mm0\n"			/* mm0 = ? | x */
	"movd  4(%0), %%mm2\n"			/* mm2 = ? | y */
	"movd  8(%0), %%mm4\n"			/* mm4 = ? | z */
	"movd 12(%0), %%mm6\n"			/* mm6 = ? | w */
	"punpckldq %%mm0, %%mm0\n"		/* mm0 = x | x */
	"punpckldq %%mm2, %%mm2\n"		/* mm2 = y | y */
	"punpckldq %%mm4, %%mm4\n"		/* mm4 = z | z */
	"punpckldq %%mm6, %%mm6\n"		/* mm6 = w | w */
	"movq %%mm0, %%mm1\n"			/* mm1 = x | x */
	"movq %%mm2, %%mm3\n"			/* mm3 = y | y */
	"movq %%mm4, %%mm5\n"			/* mm5 = z | z */
	"movq %%mm6, %%mm7\n"			/* mm7 = w | w */
	"pfmul   (%1), %%mm0\n"			/* mm0 = x*m[1]  | x*m[0] */
	"pfmul  8(%1), %%mm1\n"			/* mm1 = x*m[3]  | x*m[2] */
	"pfmul 16(%1), %%mm2\n" 		/* mm2 = y*m[5]  | y*m[4] */
	"pfmul 24(%1), %%mm3\n" 		/* mm3 = y*m[7]  | y*m[6] */
	"pfmul 32(%1), %%mm4\n" 		/* mm4 = z*m[9]  | z*m[8] */
	"pfmul 40(%1), %%mm5\n" 		/* mm5 = z*m[11] | z*m[10] */
	"pfmul 48(%1), %%mm6\n" 		/* mm6 = w*m[13] | w*m[12] */
	"pfmul 56(%1), %%mm7\n" 		/* mm7 = w*m[15] | w*m[14] */
	"pfadd %%mm0, %%mm2\n"
	"pfadd %%mm1, %%mm3\n"
	"pfadd %%mm4, %%mm6\n"
	"pfadd %%mm5, %%mm7\n"
	"pfadd %%mm2, %%mm6\n"
	"pfadd %%mm3, %%mm7\n"
	"movq %%mm6,  (%2)\n"
	"movq %%mm7, 8(%2)\n"
	:
	: "r" (pIn4D), "r" (pMat), "r" (pOut4D)
	);

	/* Execute 'femms' if desired */
	#ifndef NO_EMMS
	asm("femms\n");
	#endif

	#else
	pOut4D[0] = (pIn4D[0]*pMat->_m[0]) + (pIn4D[1]*pMat->_m[4]) + (pIn4D[2]*pMat->_m[8]) + (pIn4D[3]*pMat->_m[12]);
	pOut4D[1] = (pIn4D[0]*pMat->_m[1]) + (pIn4D[1]*pMat->_m[5]) + (pIn4D[2]*pMat->_m[9]) + (pIn4D[3]*pMat->_m[13]);
	pOut4D[2] = (pIn4D[0]*pMat->_m[2]) + (pIn4D[1]*pMat->_m[6]) + (pIn4D[2]*pMat->_m[10]) + (pIn4D[3]*pMat->_m[14]);
	pOut4D[3] = (pIn4D[0]*pMat->_m[3]) + (pIn4D[1]*pMat->_m[7]) + (pIn4D[2]*pMat->_m[11]) + (pIn4D[3]*pMat->_m[15]);
	#endif
}