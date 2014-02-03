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
#include "cntr/tree.h"

struct sc_obj_listener {
  void(*on_update)();
  void(*on_colide)();
  void(*on_key_pressed)();
};

struct sc_obj {
  struct tree link;
  struct engine* engine;
  
  char name[32];
  char type[32];//TODO type_id: int
  vec3 pos;
  vec4 orient;
  float scale;
  vec3 last_pso;//if null, updated
  int updated;//need update gpu buffer
  struct list* typed_objs;//ptr to list of entities or cameras
  struct sc_obj_listener* listener;
};

struct sc_obj* sc_obj_create(struct engine* _eng, char* _name, char* _type);

#endif /* __SCENE_OBJECT_H__ */
