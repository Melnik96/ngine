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

#ifndef __SCENE_H__
#define __SCENE_H__

#include "math/vector.h"

typedef void(*sc_node_update_handler_t)(struct ngine_sc_node*);

struct ngine_scene {
  char* 			name;
  struct ngine_sc_node* 	root_object;
  struct rbDynamicsWorld* 	dyn_world;
  
  uint32_t 			num_sc_node_update_handlers;
  sc_node_update_handler_t* 	sc_node_update_handlers;
};

struct ngine_scene* 	ngine_scene_create(char* _name, char auto_create_root_obj);
void 			ngine_scene_delete(struct ngine_scene* _self);
void 			ngine_scene_update(struct ngine_scene* _self, float _elapsed);
void 			ngine_scene_add_update_handler(struct ngine_scene* _self, sc_node_update_handler_t _handler);

void 			ngine_scene_dynamics_create(struct ngine_scene* _self, vec3* _gravity);
void 			ngine_scene_dynamics_enable(struct ngine_scene* _self);
void 			ngine_scene_dynamics_disable(struct ngine_scene* _self);

#endif /* __SCENE_H__ */
