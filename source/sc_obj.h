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

struct ngine_sc_node_listener {
  void(*on_update)(struct ngine_sc_node* _sc_node, float _time_elapsed);
  void(*on_colide)();
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

enum {
  NGINE_TRANS_LOCAL = 0,
  NGINE_TRANS_PARENT,
  NGINE_TRANS_WORLD
};

struct ngine_sc_node {
  struct tree 		link;
  
  char* 		name;
  uint32_t 		type;
  
  struct ngine_scene* 	scene;
  // translation
  vec3 			pos;
  quat 			orient;
  float 		scale;
  
  mat4 			matrix;
  
  void* 		attached_obj;
  struct rbRigidBody* 	rigid_body;
  
  // indicators
  char 			translated;
  char 			dynamic;
  
  struct ngine_sc_node_listener* listener;
//   struct {
//     void(*on_update)(struct ngine_sc_node* _sc_node, float _time_elapsed);
//     void(*on_colide)();
//   };
};

struct ngine_sc_node* 	ngine_sc_node_create(struct ngine_scene* _scene, char* _name, int _type);
void 			ngine_sc_node_translate(struct ngine_sc_node* _self, vec3* _vec, int _relative);
void 			ngine_sc_node_rotate(struct ngine_sc_node* _self, quat* _orient, int _relative);
// only if sc_node dynamic
void 			ngine_sc_node_set_lin_vel(struct ngine_sc_node* _self, vec3* _vel, int _relative);

struct ngine_phys_info {
  float mass;
};

void 			ngine_sc_node_make_dynamic(struct ngine_sc_node* _self, struct ngine_phys_info* _phys);
// void 			ngine_sc_node_phys_activate(struct ngine_sc_node* _self, char _active);

//intern
struct ngine_sc_node* 	ngine_sc_node_upd_mat(struct ngine_sc_node* _self);

#endif /* __SCENE_OBJECT_H__ */
