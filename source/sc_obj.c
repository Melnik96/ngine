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
#include "scene.h"

#include "sc_obj.h"

struct ngine_sc_node* ngine_sc_node_create(struct ngine_scene* _scene, char* _name, int _type) {
  struct ngine_sc_node* new_obj = calloc(1, sizeof(struct ngine_sc_node));
  new_obj->listener = calloc(1, sizeof(struct ngine_sc_node_listener));
  new_obj->name = _name;
  new_obj->type = _type;
  
  kmMat4Identity(&new_obj->matrix);
  
  
  return new_obj;
}

void ngine_sc_node_phys_setup(struct ngine_sc_node* _self, struct ngine_phys_info* _phys, int _shape_type) {
//   if(_self->type == NGINE_SC_OBJ_ENTITY) {
//     if(_shape_type == NGINE_SHAPE_BOX) {
//       RB_shape_new_box(1, 1, 1);
//     } else if(_shape_type == NGINE_SHAPE_POINT) {
//       RB_shape_new_gimpact_mesh();
//     } else if(_shape_type == NGINE_SHAPE_SPHERE) {
//       RB_shape_new_gimpact_mesh();
//     } else if(_shape_type == NGINE_SHAPE_TRIMESH) {
//       RB_shape_new_gimpact_mesh();
//     } else if(_shape_type == NGINE_SHAPE_CONVEX) {
//       RB_shape_new_gimpact_mesh();
//     } else if(_shape_type == NGINE_SHAPE_GIMPACT) {
//       RB_trimesh_data_new();
//       RB_trimesh_add_vertices();
//       // fot every chunk
//       RB_trimesh_add_triangle_indices();
//       RB_trimesh_finish();
//       
//       RB_shape_new_gimpact_mesh();
//     }
//   } else {
//     
//   }
//   
//   RB_body_new();
//   RB_dworld_add_body();
}

// intern
struct ngine_sc_node* ngine_sc_node_upd_mat(struct ngine_sc_node* _self) {
  kmMat4* tmp_mat = malloc(sizeof(kmMat4));

//   kmMat4Identity(tmp_mat);
  kmMat4Identity(&_self->matrix);

//   kmMat4Scaling(tmp_mat, _self->scale, _self->scale, _self->scale);
//   kmMat4Multiply(&_self->matrix, &_self->matrix, tmp_mat);
  sleep(0.1);
  
  kmMat4RotationQuaternion(tmp_mat, &_self->orient);
  kmMat4Multiply(&_self->matrix, tmp_mat, &_self->matrix);
  
  kmMat4Translation(tmp_mat, _self->pos.x, _self->pos.y, _self->pos.z);
  kmMat4Multiply(&_self->matrix, tmp_mat, &_self->matrix);
// 
  if(_self->link.parent != NULL) {
    kmMat4Multiply(&_self->matrix, &((struct ngine_sc_node*)_self->link.parent)->matrix, &_self->matrix);
  }// all parents must be updated already
}
