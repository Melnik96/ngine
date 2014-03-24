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
#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "anim/bone.h"

struct entity {
//  struct list 		link;
  
  char 			name[32];
//   struct physics* phys;
//   uint num_meshes;
//   uint num_materials;
  int 			updated;
  struct mesh* 		mesh;
  struct material* 	material;
  struct skel 		skel;
  
  struct hw_buffers* 	hw;
};

int 		entity_init(struct entity* _ent, char* _name, struct mesh* _mesh, struct material* _material);
struct entity* 	entity_create(char* _name, struct mesh* _mesh, struct material* _material);
int 		entity_update_hw(struct entity* _ent);//call in engine.c if entity.updated == 1
//note: mesh may never change in cpu. Animation, soft body and teselation may compute on gpu.

#endif /* __ENTITY_H__ */
