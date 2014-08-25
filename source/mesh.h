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
#ifndef __MESH_H__
#define __MESH_H__

#include <stdint.h>
#include "math/vector.h"

struct ngine_mesh {
  uint32_t 		num_vertices;
  
  vec3* 		vertices;// position
  vec3* 		normals;
  vec2* 		uvs;
//   vec3* 	tangent;
//   vec3* 	colors;
  // weights
  
  uint16_t 		num_chunks;
  struct {
    uint32_t 			num_indices;
    uint32_t* 			indices;
    struct ngine_material* 	mtl;
    uint32_t 			hw_vao;
    uint32_t 			hw_index;
  } *chunk;
  
  union {
    aabb 			aabb;
    vec2 			plane_size;
  };
  
  struct rbCollisionShape* coll_shape;
  
  struct {
    uint32_t vert;
    uint32_t color;
    uint32_t uv;
    uint32_t norm;
  } hw_buf;
};

struct ngine_mesh* 		ngine_mesh_create(int _num_chunks);
// 				update gpu beffers. possibly will renamed to ngine_mesh_gpu
void 				ngine_mesh_update(struct ngine_mesh* _self);

enum {
  NGINE_SHAPE_POINT = 0,
  NGINE_SHAPE_BOX,
  NGINE_SHAPE_SPHERE,
  NGINE_SHAPE_CONVEX,
  NGINE_SHAPE_GIMPACT,
  NGINE_SHAPE_TRIMESH
};

struct rbCollisionShape* 	ngine_mesh_make_coll_shape(struct ngine_mesh* _self, int _shape_type);

#endif /* __MESH_H__ */
