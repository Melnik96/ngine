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

struct ngine_sc_node {
  struct tree 		link;
  
  char* 		name;
  int 			type;// sc_obj_type
  
  struct ngine_scene* 	scene;
  // translation
  vec3 			pos;
  quat 			orient;
  float 		scale;
  
  mat4 			matrix;
  
  void* 		attached_obj;
  
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

enum {
  NGINE_SHAPE_POINT = 0,
  NGINE_SHAPE_BOX,
  NGINE_SHAPE_SPHERE,
  NGINE_SHAPE_CONVEX,
  NGINE_SHAPE_GIMPACT,
  NGINE_SHAPE_TRIMESH
};

struct ngine_phys_info {};

void 			ngine_sc_node_make_dynamic(struct ngine_sc_node* _self, struct ngine_phys_info* _phys, int _shape_type);
// void 			ngine_sc_node_phys_activate(struct ngine_sc_node* _self, char _active);

//intern
struct ngine_sc_node* 	ngine_sc_node_upd_mat(struct ngine_sc_node* _self);

#endif /* __SCENE_OBJECT_H__ */
