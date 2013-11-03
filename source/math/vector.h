#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdint.h>

typedef union {
  struct {
    float x,y;
  };
  float val[2];
} vec2;
typedef union {
  struct {
    float x,y,z;
    float __simd_pad;
  } __attribute__((aligned(16)));
  float val[3];
} vec3;
typedef union {
  struct {
    float x,y,z,w;
  };
  float val[4];
} vec4;
/*
vec_mul() {
  SIMDx86Vector_Cross();
  SIMDx86Matrix_VectorMultiply();
}*/

// #define vec3_mat4_mul SIMDx86Matrix_VectorMultiply
// #define vec3_mat4_mul_of SIMDx86Matrix_VectorMultiplyOf

typedef enum {
  FAR_LEFT_BOTTOM = 0,
  FAR_LEFT_TOP = 1,
  FAR_RIGHT_TOP = 2,
  FAR_RIGHT_BOTTOM = 3,
  NEAR_RIGHT_BOTTOM = 7,
  NEAR_LEFT_BOTTOM = 6,
  NEAR_LEFT_TOP = 5,
  NEAR_RIGHT_TOP = 4
} CornerEnum;

typedef union {
  struct {
    vec3 flb;
    vec3 flt;
    vec3 frt;
    vec3 frb;
    vec3 nrb;
    vec3 nlb;
    vec3 nlt;
    vec3 nrt;
  };
  vec3 val[8];
} aabb;

#endif
