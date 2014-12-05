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

#include <malloc.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <kazmath/kazmath.h>

#include "math/matrix.h"

#include "core/log.h"
#include "scene.h"
#include "entity.h"
#include "light.h"
#include "mesh/mesh.h"

#include "sc_node.h"

def_modable_struct(ngine_sc_node);

struct ngine_sc_node {
  struct tree 			link;
  
  char* 			name;
  uint32_t 			type;
  
  struct ngine_scene* 		scene;
  // translation
  vec3 				pos;
  quat 				orient;
  float 			scale;
  
  mat4 				matrix;
  
  void* 			attached_obj;
  
  // indicators
  char 				translated;
  
  uint32_t 			num_intersect_cbs;
  struct intesect* 		intesect_cbs;
  
  uint32_t 			num_update_cbs;
  sc_node_update_cb_t* 		update_cbs;
  
  uint32_t 			num_mods;
  void** 			mods;
};

struct ngine_sc_node* ngine_sc_node_create(struct ngine_scene* _scene, char* _name, int _type) {
  struct ngine_sc_node* new_obj = calloc(1, sizeof(struct ngine_sc_node));
  new_obj->name = _name;
  new_obj->type = _type;
  new_obj->scene = _scene;
  
  return new_obj;
}

void ngine_sc_node_delete(struct ngine_sc_node* _self)
{

}

char* ngine_sc_node_name(struct ngine_sc_node* _self, const char* _name) {
  if(_name) {
    _self->name = _name;
  } else {
    return _self->name;
  }
}

void ngine_sc_node_set_name(struct ngine_sc_node* _self, const char* _name) {
  _self->name = _name;
}

void ngine_sc_node_add_update_cb(struct ngine_sc_node* _self, sc_node_update_cb_t _upd_cb) {
  _self->update_cbs = realloc(_self->update_cbs, sizeof(sc_node_update_cb_t)*(_self->num_update_cbs+1));
  _self->update_cbs[_self->num_update_cbs] = _upd_cb;
  _self->num_update_cbs += 1;
}

void ngine_sc_node_translate(struct ngine_sc_node* _self, vec3* _vec, int _relative) {
  if(_relative == NGINE_TRANS_LOCAL) {
    vec3 tvec;
    kmQuaternionMultiplyVec3(&tvec, &_self->orient, _vec);
    kmVec3Add(&_self->pos, &tvec, &_self->pos);
//     if(_self->rigid_body) {
// //     RB_body_set_loc_rot(_self->rigid_body, &_self->pos, &_self->orient);
//       RB_body_translate(_self->rigid_body, tvec.val);
//       RB_body_activate(_self->rigid_body);
//     }
  } else if(_relative == NGINE_TRANS_PARENT) {
    kmVec3Add(&_self->pos, _vec, &_self->pos);
  } else if(_relative == NGINE_TRANS_WORLD) {
    vec3 tvec;
    kmQuaternionMultiplyVec3(&tvec, &((struct ngine_sc_node*)tree_get_head(_self))->orient, _vec);
    kmVec3Add(&_self->pos, &tvec, &_self->pos);
  } else {
    error("sc_node trans type invalid");
  }
//   if(_self->rigid_body) {
// //     RB_body_set_loc_rot(_self->rigid_body, &_self->pos, &_self->orient);
//     RB_body_translate(_self->rigid_body, &_self->pos);
//   }
  _self->translated = 1;
}

void ngine_sc_node_rotate(struct ngine_sc_node* _self, quat* _orient, int _relative) {
  kmQuaternionAdd(&_self->orient, _orient, &_self->orient);
  kmQuaternionNormalize(&_self->orient, &_self->orient);
}
