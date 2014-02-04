#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdint.h>

# define M_PI		3.14159265358979323846	/* pi */

#define deg2rad(x) (float)(((x) * M_PI / 180.0f))
#define rad2deg(x) (float)(((x) * 180.0f / M_PI))

typedef union {
  struct {
    float x,y;
  };
  float val[2];
} vec2;
typedef union {
  struct {
    float x,y,z;
  };
  float val[3];
} vec3;
typedef union {
  struct {
    float x,y,z,w;
  };
  float val[4];
} vec4;

// void vec3_mat4_mul_of(float* pOut4D, const float* pIn4D, const mat4* pMat);
void vec3_sum(vec3* _out, const vec3* _in);
void vec3_sum_of(vec3* _out, const vec3* _in1, const vec3* _in2);
void vec3_diff_of(vec3* pOut, const vec3* pLeft, const vec3* pRigh);
void vec3_cross_of(vec3* _out, const vec3* _in1, const vec3* _in2);

vec3* qrot(vec4* q, vec3* v);

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
