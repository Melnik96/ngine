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

struct entity {
//parent struct scene_object
//   char name[32];
//   char type[32];
//   char* script;
//   struct entity* entity;
//   matrix4x4 model_matrix;
//   struct scene_object_listener* listener;
//   struct scene_object* childs;
  
  char name[32];
//   struct physics* phys;
  struct mesh* meshes;
  struct material* material;
  
  struct hw_buffer* hw;
  
  struct entity* childs;
};

#endif /* __ENTITY_H__ */
