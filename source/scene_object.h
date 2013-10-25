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

#include "mesh.h"
#include "math.h"

struct scene_object_listener {
  void(*on_colide)();
};

struct scene_object {
  char name[32];
  char type[32];
  vector3 pos,rot;
  matrix4x4 model_matrix;
  void* ptr_to_typed_obj;//ptr to entity or camera
//   char* script;
  struct scene_object_listener* listener;
  
//   uint8_t num_childs;
  struct scene_object* childs;
};

void scene_object_translate(vector3 _pos);

#endif /* __SCENE_OBJECT_H__ */
