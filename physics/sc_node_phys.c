/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2014  <copyright holder> <email>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * 
 */

#include "physics/rigidbody/RBI_api.h"

#include "sc_node_phys.h"

void ngine_sc_node_make_dynamic(struct ngine_sc_node* _self, struct ngine_phys_info* _phys) {
  if(_self->type == NGINE_SC_OBJ_ENTITY) {
//     _self->pos.z *= -1;
//     _self->orient.y *= -1;
//     _self->orient.w *= -1;
    _self->rigid_body = RB_body_new(((struct ngine_entity*)_self->attached_obj)->mesh->coll_shape, &_self->pos, &_self->orient);
    debug("create rigidbody for entity");
  } else {
    // TODO
  }
  
  RB_dworld_add_body(_self->scene->dyn_world, _self->rigid_body, 1);
  RB_body_activate(_self->rigid_body);
  RB_body_set_mass(_self->rigid_body, _phys->mass);
  
  _self->dynamic = 1;
}
