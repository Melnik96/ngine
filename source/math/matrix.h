#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "math/SIMDx86/matrix.h"

typedef union {
  float m[3][3];
  float _m[9];
} mat3;

typedef union {
  float m[4][4];
  float _m[16];
} mat4;

// typedef float mat4[4][4];
static const mat4 identitymatrix = {
  {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  }
};

// int mat4_mul(mat4* _mat, mat4* _f, mat4* _s);k

#define mat4_mul_of SIMDx86Matrix_MultiplyOf
#define mat4_mul_aligned_of SIMDx86Matrix_AlignedMultiplyOf

#endif
