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
#include <math.h>
#include <kazmath/kazmath.h>

#include "ngine.h"

#include "sc_obj.h"
#include <matrix.h>

# define M_PI		3.14159265358979323846	/* pi */

#define deg2rad(x) (float)(((x) * M_PI / 180.0f))
#define rad2deg(x) (float)(((x) * 180.0f / M_PI))

#define true 1
#define false 0

struct ngine_sc_node* ngine_sc_node_create(char* _name, int _type) {
  struct ngine_sc_node* new_obj = calloc(1, sizeof(struct ngine_sc_node));
  new_obj->name = _name;
  new_obj->type = _type;
  
  kmMat4Identity(&new_obj->matrix);
  
  return new_obj;
}
struct ngine_sc_node* ngine_sc_node_upd_mat(struct ngine_sc_node* _self) {
  kmMat4* tmp_mat = malloc(sizeof(kmMat4));

//   kmMat4Identity(tmp_mat);
  kmMat4Identity(&_self->matrix);

//   kmMat4Scaling(tmp_mat, _self->scale, _self->scale, _self->scale);
//   kmMat4Multiply(&_self->matrix, &_self->matrix, tmp_mat);
  
  kmMat4RotationQuaternion(tmp_mat, &_self->orient);
  kmMat4Multiply(&_self->matrix, tmp_mat, &_self->matrix);
  
  kmMat4Translation(tmp_mat, _self->pos.x, _self->pos.y, _self->pos.z);
  kmMat4Multiply(&_self->matrix, tmp_mat, &_self->matrix);
// 
  if(_self->link.parent != NULL) {
    kmMat4Multiply(&_self->matrix, &_self->matrix, &((struct ngine_sc_node*)_self->link.parent)->matrix);
  }// all parents must be updated already
}
