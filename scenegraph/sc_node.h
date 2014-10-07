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


#ifndef __SCENE_OBJECT_H__
#define __SCENE_OBJECT_H__

#include "math/vector.h"
#include "math/matrix.h"
#include "core/tree.h"

struct ngine_sc_node_listener {
  void(*on_update)(struct ngine_sc_node* _sc_node, float _time_elapsed);
  void(*on_colide)();
  // gui
  void(*on_active)();
  void(*on_deactive)();
  void(*on_btn_pressed)();
  void(*on_btn_relased)();
  void(*on_key_pressed)();
  void(*on_key_relesed)();
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

extern uint32_t ngine_sc_node_size; // for dinamic struct allocetion

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
  
  void* plugins_stol[4];
};

// struct ngine_sc_node_phys {
//   unsigned i :sizeof(struct ngine_sc_node);
// };

struct ngine_sc_node* 	ngine_sc_node_create(struct ngine_scene* _scene, char* _name, int _type);
void 			ngine_sc_node_delete(struct ngine_sc_node* _self);

char* 			ngine_sc_node_name(struct ngine_sc_node* _self, const char* _name);

void 			ngine_sc_node_set_name(struct ngine_sc_node* _self, const char* _name);
void 			ngine_sc_node_set_pos(struct ngine_sc_node* _self, vec3* _pos, int _relative);
void 			ngine_sc_node_set_rot(struct ngine_sc_node* _self, quat* _orient, int _relative);

void 			ngine_sc_node_translate(struct ngine_sc_node* _self, vec3* _vec, int _relative);
void 			ngine_sc_node_rotate(struct ngine_sc_node* _self, quat* _orient, int _relative);

#endif /* __SCENE_OBJECT_H__ */
