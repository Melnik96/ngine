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
#ifndef __SCENE_OBJECT_H__
#define __SCENE_OBJECT_H__

#include "math/vector.h"
#include "math/matrix.h"
#include "cntr/tree.h"

struct sc_obj_listener {
  void(*on_update)();
  void(*on_colide)();
  void(*on_key_pressed)();
};

enum sc_obj_type {
  SC_OBJ_NULL,
  SC_OBJ_ENTITY,
  SC_OBJ_CAMERA
  //user defined types
};

struct sc_obj {
  struct tree link;
//   struct engine* engine;
  
  char name[32];
  int type;// sc_obj_type
  // translation
  vec3 pos;
  quat orient;
  float scale;
  
  mat4 matrix;
  
  // indicators
  int16_t translated;
  int16_t updated;//need update gpu buffer
  
  struct list* typed_objs;//ptr to list of entities or cameras
  
  struct sc_obj_listener* listener;
};

int sc_obj_init(struct sc_obj* _self, char* _name, int _type);
struct sc_obj* sc_obj_create(char* _name, int _type);

//intern
struct sc_obj* sc_obj_upd_mat(struct sc_obj* _self);
struct sc_obj* sc_obj_upd_mat_inv(struct sc_obj* _self);

#endif /* __SCENE_OBJECT_H__ */
