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

#include <malloc.h>
#include <string.h>
#include <stddef.h>
#include <math.h>

#include "engine.h"

#include "sc_obj.h"
















# define M_PI		3.14159265358979323846	/* pi */

#define ToRadian(x) (float)(((x) * M_PI / 180.0f))
#define ToDegree(x) (float)(((x) * 180.0f / M_PI))


mat4* mat_scale(float ScaleX, float ScaleY, float ScaleZ) {
  mat4* m = malloc(sizeof(mat4));
  m->m[0][0] = ScaleX; m->m[0][1] = 0.0f;   m->m[0][2] = 0.0f;   m->m[0][3] = 0.0f;
  m->m[1][0] = 0.0f;   m->m[1][1] = ScaleY; m->m[1][2] = 0.0f;   m->m[1][3] = 0.0f;
  m->m[2][0] = 0.0f;   m->m[2][1] = 0.0f;   m->m[2][2] = ScaleZ; m->m[2][3] = 0.0f;
  m->m[3][0] = 0.0f;   m->m[3][1] = 0.0f;   m->m[3][2] = 0.0f;   m->m[3][3] = 1.0f;
  
  return (mat4*)m;
}

mat4* mat_rotation(float _rot_x, float _rot_y, float _rot_z)
{
    mat4 rx, ry, rz;
    mat4* sum_mat = malloc(sizeof(mat4));

    const float x = ToRadian(_rot_x);
    const float y = ToRadian(_rot_y);
    const float z = ToRadian(_rot_z);

    rx.m[0][0] = 1.0f; rx.m[0][1] = 0.0f   ; rx.m[0][2] = 0.0f    ; rx.m[0][3] = 0.0f;
    rx.m[1][0] = 0.0f; rx.m[1][1] = cosf(x); rx.m[1][2] = -sinf(x); rx.m[1][3] = 0.0f;
    rx.m[2][0] = 0.0f; rx.m[2][1] = sinf(x); rx.m[2][2] = cosf(x) ; rx.m[2][3] = 0.0f;
    rx.m[3][0] = 0.0f; rx.m[3][1] = 0.0f   ; rx.m[3][2] = 0.0f    ; rx.m[3][3] = 1.0f;

    ry.m[0][0] = cosf(y); ry.m[0][1] = 0.0f; ry.m[0][2] = -sinf(y); ry.m[0][3] = 0.0f;
    ry.m[1][0] = 0.0f   ; ry.m[1][1] = 1.0f; ry.m[1][2] = 0.0f    ; ry.m[1][3] = 0.0f;
    ry.m[2][0] = sinf(y); ry.m[2][1] = 0.0f; ry.m[2][2] = cosf(y) ; ry.m[2][3] = 0.0f;
    ry.m[3][0] = 0.0f   ; ry.m[3][1] = 0.0f; ry.m[3][2] = 0.0f    ; ry.m[3][3] = 1.0f;

    rz.m[0][0] = cosf(z); rz.m[0][1] = -sinf(z); rz.m[0][2] = 0.0f; rz.m[0][3] = 0.0f;
    rz.m[1][0] = sinf(z); rz.m[1][1] = cosf(z) ; rz.m[1][2] = 0.0f; rz.m[1][3] = 0.0f;
    rz.m[2][0] = 0.0f   ; rz.m[2][1] = 0.0f    ; rz.m[2][2] = 1.0f; rz.m[2][3] = 0.0f;
    rz.m[3][0] = 0.0f   ; rz.m[3][1] = 0.0f    ; rz.m[3][2] = 0.0f; rz.m[3][3] = 1.0f;

    mat4_mul_of(sum_mat, &rz, &ry);
    mat4_mul(sum_mat, &rx);
    
    return sum_mat;
}

mat4* mat_translation(float x, float y, float z) {
  mat4* m = malloc(sizeof(mat4));
  m->m[0][0] = 1.0f; m->m[0][1] = 0.0f; m->m[0][2] = 0.0f; m->m[0][3] = x;
  m->m[1][0] = 0.0f; m->m[1][1] = 1.0f; m->m[1][2] = 0.0f; m->m[1][3] = y;
  m->m[2][0] = 0.0f; m->m[2][1] = 0.0f; m->m[2][2] = 1.0f; m->m[2][3] = z;
  m->m[3][0] = 0.0f; m->m[3][1] = 0.0f; m->m[3][2] = 0.0f; m->m[3][3] = 1.0f;
  
  return (mat4*)m;
}















struct sc_obj* sc_obj_create(struct engine* _eng, char* _name, char* _type) {
  struct sc_obj* new_obj = malloc(sizeof(struct sc_obj));
//   strcpy(new_obj->name, _name);
//   strcpy(new_obj->type, _type);
  memset(new_obj, 0, sizeof(struct sc_obj));
  strcpy(new_obj->name, _name);
  strcpy(new_obj->type, _type);
  mat4_identity(&new_obj->model_matrix);
  new_obj->engine = _eng;
  new_obj->updated = 1;
  
  return new_obj;
}

void sc_obj_update_matrix(struct sc_obj* _self) {
  mat4_mul_of(&_self->model_matrix, 
	      mat_translation(_self->pos.x,_self->pos.y,_self->pos.z), 
	      mat_rotation(_self->rot.x,_self->rot.y,_self->rot.z));
  mat4_mul(&_self->model_matrix, mat_scale(_self->scale.x,_self->scale.y,_self->scale.z));
}
