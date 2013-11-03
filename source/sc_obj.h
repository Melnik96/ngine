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

#include "math/matrix.h"
#include "math/vector.h"

struct sc_obj_listener {
  void(*on_colide)();
};

struct sc_obj {
  //scene node tree
  struct tree* parent;
  struct tree* next;
  struct tree* childs;
  
  struct engine* engine;
  
  char name[32];
  char type[32];
  vec3 pos,rot;
  mat4 model_matrix;
  int updated;//need update gpu buffer
  void* typed_obj;//ptr to entity or camera
//   char* script;
  struct sc_obj_listener* listener;
};

struct sc_obj* sc_obj_create(char* _name, char* _type);
int sc_obj_add_child(struct sc_obj* _self, struct sc_obj* _child);
// void sc_obj_translate(vec3 _pos);
void sc_obj_update_matrix(struct sc_obj* _self);

#endif /* __SCENE_OBJECT_H__ */
