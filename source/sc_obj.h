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
//   void(*on_key_pressed)();
};

enum sc_obj_type {
  NGINE_SC_OBJ_NULL = 0,
  NGINE_SC_OBJ_ENTITY,
  NGINE_SC_OBJ_LIGHT,
  NGINE_SC_OBJ_CAMERA,
  NGINE_SC_OBJ_SPEAKER,
  NGINE_SC_OBJ_LISTENER
  //user defined types
};

struct ngine_sc_obj {
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
  
  void* typed_objs;//ptr to list of entities or cameras
  
  struct sc_obj_listener* listener;
};

int	       ngine_sc_obj_init(struct ngine_sc_obj* _self, char* _name, int _type);
struct ngine_sc_obj* ngine_sc_obj_create(char* _name, int _type);

//intern
struct ngine_sc_obj* ngine_sc_obj_upd_mat(struct ngine_sc_obj* _self);
struct ngine_sc_obj* ngine_sc_obj_upd_mat_inv(struct ngine_sc_obj* _self);

// future
struct ngine_sc_node {/*...*/};
struct ngine_some_typed_obj {
  /* not pre pad */
  struct ngine_sc_node* sc_node;
  /*...*/
};

#endif /* __SCENE_OBJECT_H__ */
