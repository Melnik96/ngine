#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdint.h>

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
    float flb;
    float flt;
    float frt;
    float frb;
    float nrb;
    float nlb;
    float nlt;
    float nrt;
  };
  float values[8];
} aabb;

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

#endif
