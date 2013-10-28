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

#include "sc_obj.h"

struct sc_obj* sc_obj_create(char* _name, char* _type) {
  struct sc_obj* new_obj = malloc(sizeof(struct sc_obj));
//   strcpy(new_obj->name, _name);
//   strcpy(new_obj->type, _type);
//   memset(new_obj->pos, 0, 
// 	 offsetof(new_obj, new_obj->rot) - offsetof(new_obj, new_obj->childs)
// 	 +sizeof(void*));
  memset(new_obj, 0, sizeof(struct sc_obj));
  strcpy(new_obj->name, _name);
  strcpy(new_obj->type, _type);
  
  return new_obj;
}

int sc_obj_add_child(struct sc_obj* _self, struct sc_obj* _child) {
//   _self->childs = realloc(_self->childs, sizeof(void*));
//   _self->childs[_self->num_childs+1] = _child;
//   _self->num_childs += 1;
}

void sc_obj_update_matrix(struct sc_obj* _self) {
  _self->model_matrix.m[0][0] = 1;
  _self->model_matrix.m[0][1] = 0;
  _self->model_matrix.m[0][2] = 0;
  _self->model_matrix.m[0][3] = _self->pos.x;
  
  _self->model_matrix.m[1][0] = 0;
  _self->model_matrix.m[1][1] = 1;
  _self->model_matrix.m[1][2] = 0;
  _self->model_matrix.m[1][3] = _self->pos.y;
  
  _self->model_matrix.m[2][0] = 0;
  _self->model_matrix.m[2][1] = 0;
  _self->model_matrix.m[2][2] = 1;
  _self->model_matrix.m[2][3] = _self->pos.z;
  
  _self->model_matrix.m[3][0] = 0;
  _self->model_matrix.m[3][1] = 0;
  _self->model_matrix.m[3][2] = 0;
  _self->model_matrix.m[3][3] = 1;
  
  _self->updated = 1;
}
