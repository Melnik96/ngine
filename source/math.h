/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2013  <copyright holder> <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/* inclusion guard */
#ifndef __MATH_H__
#define __MATH_H__

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
    float x,y,z;
  };
  float values[3];
} vec3;
typedef union {
  struct {
    float x,y,z,w;
  };
  float values[4];
} vec4;

// typedef union {
//   float values[3][3];
//   float values[9];
// } mat3;

typedef union {
  float m[4][4];
  float _m[16];
} mat4;

// typedef float mat4[4][4];
const mat4 identitymatrix;

int mat4_mul(mat4* _mat, mat4* _f, mat4* _s);

#endif /* __MATH_H__ */
