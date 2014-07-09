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

#include "physics/rigidbody/RBI_api.h"
#include "sc_obj.h"

#include "scene.h"

struct ngine_scene* ngine_scene_create(char* _name, char _dynamics, char _auto_create_root_obj) {
  struct ngine_scene* new_scene = malloc(sizeof(struct ngine_scene));
  new_scene->name = _name;
  
  if(_dynamics) {
    ngine_scene_dynamics_create(new_scene, &(vec3){0,-1,0});
//     ngine_scene_dynamics_enable(new_scene);
  }
  
  if(_auto_create_root_obj) {
    new_scene->root_object = ngine_sc_node_create(new_scene, "root_object", "null");
  } else {
    new_scene->root_object = NULL;
  }
  
  return new_scene;
}

void ngine_scene_dynamics_create(struct ngine_scene* _self, vec3* _gravity) {
  _self->dyn_world = RB_dworld_new(_gravity);
}
