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

#include "RBI_api.h"
#include "core/log.h"
#include "core/struct_mod.h"
#include "scenegraph/sc_node.h"
#include "scenegraph/entity.h"
#include "scenegraph/scene.h"
#include "mesh/mesh.h"
#include "physics/scene_phys.h"

#include "sc_node_phys.h"

void ngine_sc_node_make_dynamic(struct ngine_sc_node* _self, float _mass) {
  if(_self->mods == NULL) {
    _self->mods = realloc(_self->mods, ngine_sc_node_mods_num*sizeof(void*));
    _self->num_mods += 1;
  }
  struct ngine_sc_node_mod_phys* _self_mod = _self->mods[struct_mod_id(ngine_sc_node, phys)] = calloc(1, sizeof(struct ngine_sc_node_mod_phys));
  
  if(_self->type == NGINE_SC_OBJ_ENTITY) {
//     _self->pos.z *= -1;
//     _self->orient.y *= -1;
//     _self->orient.w *= -1;
    _self_mod->rigid_body = RB_body_new(((struct ngine_entity*)_self->attached_obj)->mesh->coll_shape, &_self->pos, &_self->orient);
    debug("create rigidbody for entity");
  } else {
    // TODO
  }
  
  obj_get_mod(_scene_phys, _self, ngine_scene, phys);
  RB_dworld_add_body(_scene_phys->dyn_world, _self_mod->rigid_body, 1);
  RB_body_activate(_self_mod->rigid_body);
  RB_body_set_mass(_self_mod->rigid_body, _mass);
  
  _self_mod->dynamic = 1;
}

void ngine_sc_node_set_lin_vel(struct ngine_sc_node* _self, vec3* _vel, int _relative) {
  struct ngine_sc_node_mod_phys* _self_mod = _self->mods[struct_mod_id(ngine_sc_node, phys)];
  
  RB_body_activate(_self_mod->rigid_body);
  if(_relative == NGINE_TRANS_LOCAL) {
    vec3 tvec;
    kmQuaternionMultiplyVec3(&tvec, &_self->orient, _vel);
    RB_body_set_linear_velocity(_self_mod->rigid_body, tvec.val);
  } else if(_relative == NGINE_TRANS_PARENT) {
    vec3 tvec;
    kmQuaternionMultiplyVec3(&tvec, &((struct ngine_sc_node*)_self->link.parent)->orient, _vel);
    RB_body_set_linear_velocity(_self_mod->rigid_body, tvec.val);
  } else if(_relative == NGINE_TRANS_WORLD) {
    RB_body_set_linear_velocity(_self_mod->rigid_body, _vel->val);
  } else {
    error("sc_node trans type invalid");
  }
//   _self->translated = 1;
}
