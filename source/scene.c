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

#include <string.h>
#include <malloc.h>

#include "sc_obj.h"

#include "scene.h"

struct scene* scene_create(char* _name, char _auto_create_root_obj) {
  struct scene* new_scene = malloc(sizeof(struct scene));
  strcpy(new_scene->name, _name);
  
  if(_auto_create_root_obj) {
    new_scene->root_object = ngine_sc_node_create("root_object", "null");
  } else {
    new_scene->root_object = NULL;
  }
  return new_scene;
}
