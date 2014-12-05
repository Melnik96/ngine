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
#include "core/struct_mod.h"

typedef void(*sc_node_update_handler_t)(struct ngine_sc_node*);

struct ngine_scene;

struct ngine_scene* 	ngine_scene_create(char* _name, char auto_create_root_obj);
void 			ngine_scene_delete(struct ngine_scene* _self);
void 			ngine_scene_update(struct ngine_scene* _self, float _elapsed);
void 			ngine_scene_start(struct ngine_scene* _self);
void 			ngine_scene_set_name(struct ngine_scene* _self, const char* _name);
const char* 		ngine_scene_get_name(struct ngine_scene* _self);
struct ngine_sc_node* 	ngine_scene_get_root_node(struct ngine_scene* _self);
void 			ngine_scene_add_update_handler(struct ngine_scene* _self, sc_node_update_handler_t _handler);

#endif /* __SCENE_H__ */
