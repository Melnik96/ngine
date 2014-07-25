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

#include "matrix.h"
#include "physics/rigidbody/RBI_api.h"

#include "ngine.h"
#include "log.h"
#include "scene.h"
#include "entity.h"
#include "light.h"

#include "sc_obj.h"
#include "mesh.h"

struct ngine_sc_node* ngine_sc_node_create(struct ngine_scene* _scene, char* _name, int _type) {
  struct ngine_sc_node* new_obj = calloc(1, sizeof(struct ngine_sc_node));
  new_obj->listener = calloc(1, sizeof(struct ngine_sc_node_listener));
  new_obj->name = _name;
  new_obj->type = _type;
  new_obj->scene = _scene;
  
  kmMat4Identity(&new_obj->matrix);
  
  return new_obj;
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

void ngine_sc_node_set_lin_vel(struct ngine_sc_node* _self, vec3* _vel, int _relative) {
  RB_body_activate(_self->rigid_body);
  if(_relative == NGINE_TRANS_LOCAL) {
    vec3 tvec;
    kmQuaternionMultiplyVec3(&tvec, &_self->orient, _vel);
    RB_body_set_linear_velocity(_self->rigid_body, tvec.val);
  } else if(_relative == NGINE_TRANS_PARENT) {
    vec3 tvec;
    kmQuaternionMultiplyVec3(&tvec, &((struct ngine_sc_node*)_self->link.parent)->orient, _vel);
    RB_body_set_linear_velocity(_self->rigid_body, tvec.val);
  } else if(_relative == NGINE_TRANS_WORLD) {
    RB_body_set_linear_velocity(_self->rigid_body, _vel->val);
  } else {
    error("sc_node trans type invalid");
  }
//   _self->translated = 1;
}

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

// intern
struct ngine_sc_node* ngine_sc_node_upd_mat(struct ngine_sc_node* _self) {
  kmMat4* tmp_mat = malloc(sizeof(kmMat4));

//   kmMat4Identity(tmp_mat);
  kmMat4Identity(&_self->matrix);

//   if(_self->type == NGINE_SC_OBJ_LIGHT) {
//     float radius = ((struct ngine_light*)_self->attached_obj)->radius;
//     printf("radius = %f\n", radius);
//     kmMat4Scaling(tmp_mat, radius, radius, radius);
//     kmMat4Multiply(&_self->matrix, tmp_mat, &_self->matrix);
//   }
//   kmMat4Scaling(tmp_mat, _self->scale, _self->scale, _self->scale);
//   kmMat4Multiply(&_self->matrix, &_self->matrix, tmp_mat);
  
  kmMat4RotationQuaternion(tmp_mat, &_self->orient);
  kmMat4Multiply(&_self->matrix, tmp_mat, &_self->matrix);
  
  kmMat4Translation(tmp_mat, _self->pos.x, _self->pos.y, _self->pos.z);
  kmMat4Multiply(&_self->matrix, tmp_mat, &_self->matrix);
// 
  if(_self->link.parent != NULL) {
    kmMat4Multiply(&_self->matrix, &((struct ngine_sc_node*)_self->link.parent)->matrix, &_self->matrix);
  }// all parents must be updated already
}
