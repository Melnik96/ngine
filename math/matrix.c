#include <memory.h>
#include <math.h>

#include "math/matrix.h"
#include "math/deg2rad.h"

void mat4_identity(mat4* pMat) {
	memset(pMat, 0, sizeof(mat4));
	pMat->_m[0] = pMat->_m[5] = pMat->_m[10] = pMat->_m[15] = 1.0f;
}

void mat4_mul(mat4* _f, mat4* _s) {
#if defined(USE_SSE)
  asm(
    "movaps   (%0), %%xmm0\n"	/* xmm0 = _s[0..3] */
    "movaps 16(%0), %%xmm1\n"	/* xmm1 = _s[5..7] */
    "movaps 32(%0), %%xmm2\n"	/* xmm2 = _s[8..11] */
    "movaps 48(%0), %%xmm3\n"	/* xmm3 = _s[12..15] */

    /* Processes 1/2 of the matrix at a time (2x4), unrolled loop */
    "movss    (%1), %%xmm4\n"
    "movss   4(%1), %%xmm6\n"
    "movss  16(%1), %%xmm5\n"
    "movss  20(%1), %%xmm7\n"
    "shufps $0x00, %%xmm4, %%xmm4\n"
    "shufps $0x00, %%xmm5, %%xmm5\n"
    "shufps $0x00, %%xmm6, %%xmm6\n"
    "shufps $0x00, %%xmm7, %%xmm7\n"
    "mulps %%xmm0, %%xmm4\n"
    "mulps %%xmm0, %%xmm5\n"
    "mulps %%xmm1, %%xmm6\n"
    "mulps %%xmm1, %%xmm7\n"
    "addps %%xmm7, %%xmm5\n"
    "addps %%xmm6, %%xmm4\n"


    "movss  8(%1), %%xmm6\n"
    "movss 24(%1), %%xmm7\n"
    "shufps $0x00, %%xmm6, %%xmm6\n"
    "shufps $0x00, %%xmm7, %%xmm7\n"
    "mulps %%xmm2, %%xmm6\n"
    "mulps %%xmm2, %%xmm7\n"
    "addps %%xmm6, %%xmm4\n"
    "addps %%xmm7, %%xmm5\n"

    "movss  12(%1), %%xmm6\n"
    "movss  28(%1), %%xmm7\n"
    "shufps $0x00, %%xmm6, %%xmm6\n"
    "shufps $0x00, %%xmm7, %%xmm7\n"
    "mulps %%xmm3, %%xmm6\n"
    "mulps %%xmm3, %%xmm7\n"
    "addps %%xmm6, %%xmm4\n"
    "addps %%xmm7, %%xmm5\n"

    "movaps %%xmm4, (%1)\n"
    "movaps %%xmm5, 16(%1)\n"

    /* second half of the matrix */
    "movss  32(%1), %%xmm4\n"
    "movss  36(%1), %%xmm6\n"
    "movss  48(%1), %%xmm5\n"
    "movss  52(%1), %%xmm7\n"
    "shufps $0x00, %%xmm4, %%xmm4\n"
    "shufps $0x00, %%xmm5, %%xmm5\n"
    "mulps %%xmm0, %%xmm4\n"
    "mulps %%xmm0, %%xmm5\n"

    "shufps $0x00, %%xmm6, %%xmm6\n"
    "shufps $0x00, %%xmm7, %%xmm7\n"
    "mulps %%xmm1, %%xmm6\n"
    "mulps %%xmm1, %%xmm7\n"
    "addps %%xmm6, %%xmm4\n"
    "addps %%xmm7, %%xmm5\n"


    "movss 40(%1), %%xmm6\n"
    "movss 56(%1), %%xmm7\n"
    "shufps $0x00, %%xmm6, %%xmm6\n"
    "shufps $0x00, %%xmm7, %%xmm7\n"
    "mulps %%xmm2, %%xmm6\n"
    "mulps %%xmm2, %%xmm7\n"
    "addps %%xmm6, %%xmm4\n"
    "addps %%xmm7, %%xmm5\n"

    "movss  44(%1), %%xmm6\n"
    "movss  60(%1), %%xmm7\n"
    "shufps $0x00, %%xmm6, %%xmm6\n"
    "shufps $0x00, %%xmm7, %%xmm7\n"
    "mulps %%xmm3, %%xmm6\n"
    "mulps %%xmm3, %%xmm7\n"
    "addps %%xmm6, %%xmm4\n"
    "addps %%xmm7, %%xmm5\n"

    "movaps %%xmm4, 32(%1)\n"
    "movaps %%xmm5, 48(%1)\n"

    :
    : "r"(_s), "r"(_f)
  );


#elif defined(USE_3DNOW)
  asm(
    "movl $4, %%ecx\n"
    "MatrixMultiply_3DNow_Loop%=:\n"
    "movd   (%0), %%mm0\n"			/* mm0 = ? | x */
    "movd  4(%0), %%mm2\n"			/* mm2 = ? | y */
    "movd  8(%0), %%mm4\n"			/* mm4 = ? | z */
    "movd 12(%0), %%mm6\n"			/* mm6 = ? | w */
    "prefetchw 16(%0)\n"			/* prefetch_for_writing(m[4]...m[7]);  */
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
    "movq %%mm6,  (%0)\n"
    "movq %%mm7, 8(%0)\n"
    "addl $16, %0\n"
    "loop MatrixMultiply_3DNow_Loop%=\n"
    :
    : "r"(_f), "r"(_s)
    : "%ecx"
  );

  /* Execute 'femms' if desired */
#ifndef NO_EMMS
  asm("femms\n");
#endif


#else

  /*
  	This is ugly: Since the matrix cannot be stored in registers, it must have a stack copy or else the matrix
  	is being overwritten as it is being multiplied.
  	This results in some bad performance when benched against an SIMD implementation
  */
  mat4 temp;

  memcpy(&temp, _f, sizeof(mat4));

  mat4_mul_of(_f, &temp, _s);


#endif
}
void mat4_mul_of(mat4* _mat, mat4* _f, mat4* _s) {
#if defined(USE_SSE)
  asm(
    "movaps   (%0), %%xmm0\n"	/* xmm0 = _s[0..3] */
    "movaps 16(%0), %%xmm1\n"	/* xmm1 = _s[5..7] */
    "movaps 32(%0), %%xmm2\n"	/* xmm2 = _s[8..11] */
    "movaps 48(%0), %%xmm3\n"	/* xmm3 = _s[12..15] */

    /* Processes 1/2 of the matrix at a time (2x4), unrolled loop */
    "movss    (%1), %%xmm4\n"
    "movss   4(%1), %%xmm6\n"
    "movss  16(%1), %%xmm5\n"
    "movss  20(%1), %%xmm7\n"
    "shufps $0x00, %%xmm4, %%xmm4\n"
    "shufps $0x00, %%xmm5, %%xmm5\n"
    "shufps $0x00, %%xmm6, %%xmm6\n"
    "shufps $0x00, %%xmm7, %%xmm7\n"
    "mulps %%xmm0, %%xmm4\n"
    "mulps %%xmm0, %%xmm5\n"
    "mulps %%xmm1, %%xmm6\n"
    "mulps %%xmm1, %%xmm7\n"
    "addps %%xmm7, %%xmm5\n"
    "addps %%xmm6, %%xmm4\n"


    "movss  8(%1), %%xmm6\n"
    "movss 24(%1), %%xmm7\n"
    "shufps $0x00, %%xmm6, %%xmm6\n"
    "shufps $0x00, %%xmm7, %%xmm7\n"
    "mulps %%xmm2, %%xmm6\n"
    "mulps %%xmm2, %%xmm7\n"
    "addps %%xmm6, %%xmm4\n"
    "addps %%xmm7, %%xmm5\n"

    "movss  12(%1), %%xmm6\n"
    "movss  28(%1), %%xmm7\n"
    "shufps $0x00, %%xmm6, %%xmm6\n"
    "shufps $0x00, %%xmm7, %%xmm7\n"
    "mulps %%xmm3, %%xmm6\n"
    "mulps %%xmm3, %%xmm7\n"
    "addps %%xmm6, %%xmm4\n"
    "addps %%xmm7, %%xmm5\n"

    "movaps %%xmm4, (%2)\n"
    "movaps %%xmm5, 16(%2)\n"

    /* second half of the matrix */
    "movss  32(%1), %%xmm4\n"
    "movss  36(%1), %%xmm6\n"
    "movss  48(%1), %%xmm5\n"
    "movss  52(%1), %%xmm7\n"
    "shufps $0x00, %%xmm4, %%xmm4\n"
    "shufps $0x00, %%xmm5, %%xmm5\n"
    "mulps %%xmm0, %%xmm4\n"
    "mulps %%xmm0, %%xmm5\n"

    "shufps $0x00, %%xmm6, %%xmm6\n"
    "shufps $0x00, %%xmm7, %%xmm7\n"
    "mulps %%xmm1, %%xmm6\n"
    "mulps %%xmm1, %%xmm7\n"
    "addps %%xmm6, %%xmm4\n"
    "addps %%xmm7, %%xmm5\n"


    "movss 40(%1), %%xmm6\n"
    "movss 56(%1), %%xmm7\n"
    "shufps $0x00, %%xmm6, %%xmm6\n"
    "shufps $0x00, %%xmm7, %%xmm7\n"
    "mulps %%xmm2, %%xmm6\n"
    "mulps %%xmm2, %%xmm7\n"
    "addps %%xmm6, %%xmm4\n"
    "addps %%xmm7, %%xmm5\n"

    "movss  44(%1), %%xmm6\n"
    "movss  60(%1), %%xmm7\n"
    "shufps $0x00, %%xmm6, %%xmm6\n"
    "shufps $0x00, %%xmm7, %%xmm7\n"
    "mulps %%xmm3, %%xmm6\n"
    "mulps %%xmm3, %%xmm7\n"
    "addps %%xmm6, %%xmm4\n"
    "addps %%xmm7, %%xmm5\n"

    "movaps %%xmm4, 32(%2)\n"
    "movaps %%xmm5, 48(%2)\n"

    :
    : "r"(_s), "r"(_f), "r"(_mat)
  );

#elif defined(USE_3DNOW)
  asm(
    "movl $4, %%ecx\n"
    "MatrixMultiplyOf_3DNow_Loop%=:\n"
    "movd   (%0), %%mm0\n"			/* mm0 = ? | x */
    "movd  4(%0), %%mm2\n"			/* mm2 = ? | y */
    "movd  8(%0), %%mm4\n"			/* mm4 = ? | z */
    "movd 12(%0), %%mm6\n"			/* mm6 = ? | w */
    "prefetch 16(%0)\n"				/* prefetch_for_reading(in+4);  */
    "prefetchw 16(%2)\n"			/* prefetch_for_writing(out+4); */
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
    "addl $16, %0\n"
    "addl $16, %2\n"
    "loop MatrixMultiplyOf_3DNow_Loop%=\n"
    :
    : "r"(_f), "r"(_s), "r"(_mat)
    : "%ecx"
  );

  /* Execute 'femms' if desired */
#ifndef NO_EMMS
  asm("femms\n");
#endif

#else

  _mat->_m[0] = _s->_m[0] * _f->_m[0] + _s->_m[4] * _f->_m[1] + _s->_m[8] * _f->_m[2] + _s->_m[12] * _f->_m[3];
  _mat->_m[1] = _s->_m[1] * _f->_m[0] + _s->_m[5] * _f->_m[1] + _s->_m[9] * _f->_m[2] + _s->_m[13] * _f->_m[3];
  _mat->_m[2] = _s->_m[2] * _f->_m[0] + _s->_m[6] * _f->_m[1] + _s->_m[10] * _f->_m[2] + _s->_m[14] * _f->_m[3];
  _mat->_m[3] = _s->_m[3] * _f->_m[0] + _s->_m[7] * _f->_m[1] + _s->_m[11] * _f->_m[2] + _s->_m[15] * _f->_m[3];

  _mat->_m[4] = _s->_m[0] * _f->_m[4] + _s->_m[4] * _f->_m[5] + _s->_m[8] * _f->_m[6] + _s->_m[12] * _f->_m[7];
  _mat->_m[5] = _s->_m[1] * _f->_m[4] + _s->_m[5] * _f->_m[5] + _s->_m[9] * _f->_m[6] + _s->_m[13] * _f->_m[7];
  _mat->_m[6] = _s->_m[2] * _f->_m[4] + _s->_m[6] * _f->_m[5] + _s->_m[10] * _f->_m[6] + _s->_m[14] * _f->_m[7];
  _mat->_m[7] = _s->_m[3] * _f->_m[4] + _s->_m[7] * _f->_m[5] + _s->_m[11] * _f->_m[6] + _s->_m[15] * _f->_m[7];

  _mat->_m[8] = _s->_m[0] * _f->_m[8] + _s->_m[4] * _f->_m[9] + _s->_m[8] * _f->_m[10] + _s->_m[12] * _f->_m[11];
  _mat->_m[9] = _s->_m[1] * _f->_m[8] + _s->_m[5] * _f->_m[9] + _s->_m[9] * _f->_m[10] + _s->_m[13] * _f->_m[11];
  _mat->_m[10] = _s->_m[2] * _f->_m[8] + _s->_m[6] * _f->_m[9] + _s->_m[10] * _f->_m[10] + _s->_m[14] * _f->_m[11];
  _mat->_m[11] = _s->_m[3] * _f->_m[8] + _s->_m[7] * _f->_m[9] + _s->_m[11] * _f->_m[10] + _s->_m[15] * _f->_m[11];

  _mat->_m[12] = _s->_m[0] * _f->_m[12] + _s->_m[4] * _f->_m[13] + _s->_m[8] * _f->_m[14] + _s->_m[12] * _f->_m[15];
  _mat->_m[13] = _s->_m[1] * _f->_m[12] + _s->_m[5] * _f->_m[13] + _s->_m[9] * _f->_m[14] + _s->_m[13] * _f->_m[15];
  _mat->_m[14] = _s->_m[2] * _f->_m[12] + _s->_m[6] * _f->_m[13] + _s->_m[10] * _f->_m[14] + _s->_m[14] * _f->_m[15];
  _mat->_m[15] = _s->_m[3] * _f->_m[12] + _s->_m[7] * _f->_m[13] + _s->_m[11] * _f->_m[14] + _s->_m[15] * _f->_m[15];
#endif
}


void OpenGlFrustum(float l, float r, float b, float t, float n, float f, mat4* mat)
{
    mat->m[0][0] = 2 * n / (r - l);
    mat->m[0][1] = 0;
    mat->m[0][2] = 0;
    mat->m[0][3] = 0;
 
    mat->m[1][0] = 0;
    mat->m[1][1] = 2 * n / (t - b);
    mat->m[1][2] = 0;
    mat->m[1][3] = 0;
 
    mat->m[2][0] = (r + l) / (r - l);
    mat->m[2][1] = (t + b) / (t - b);
    mat->m[2][2] = -(f + n) / (f - n);
    mat->m[2][3] = -1;
 
    mat->m[3][0] = 0;
    mat->m[3][1] = 0;
    mat->m[3][2] = -2 * f * n / (f - n);
    mat->m[3][3] = 0;
}
void mat_perspective(float fov, float aspect, float near, float far, float* mret) {
    float D2R = M_PI / 180.0;
    float yScale = 1.0 / tan(D2R * fov / 2);
    float xScale = yScale / aspect;
    float nearmfar = near - far;
    float m[] = {
        xScale, 0, 0, 0,
        0, yScale, 0, 0,
        0, 0, (far + near) / nearmfar, -1,
        0, 0, 2*far*near / nearmfar, 0
    };
    memcpy(mret, m, sizeof(float)*16);
}

void mat4_rot(mat4* m, float x, float y, float z)
{
        const float A = cosf(x), B = sinf(x), C = cosf(y),
                    D = sinf(y), E = cosf(z), F = sinf(z);
        const float AD = A * D, BD = B * D;

        m->_m[ 0] = C * E;           m->_m[ 1] = -C * F;          m->_m[ 2] = D;      m->_m[ 3] = 0;
        m->_m[ 4] = BD * E + A * F;  m->_m[ 5] = -BD * F + A * E; m->_m[ 6] = -B * C; m->_m[ 7] = 0;
        m->_m[ 8] = -AD * E + B * F; m->_m[ 9] = AD * F + B * E;  m->_m[10] = A * C;  m->_m[11] = 0;
        m->_m[12] = 0;               m->_m[13] = 0;               m->_m[14] = 0;      m->_m[15] = 1;
}
