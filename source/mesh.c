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
#include <GL/glew.h>
#include <GL/gl.h>

#include "physics/rigidbody/RBI_api.h"
#include "shader_prog.h"

#include "mesh.h"

struct ngine_mesh* ngine_mesh_create(int _num_chunks) {
  struct ngine_mesh* new_mesh = calloc(1, sizeof(struct ngine_mesh));
  
  new_mesh->num_chunks = _num_chunks;
  new_mesh->chunk = calloc(_num_chunks, sizeof(*new_mesh->chunk));
  
  return new_mesh;
}

void ngine_mesh_update(struct ngine_mesh* _self) {
  // 	if(_self->tech->render_passes[i3].a_vert == 1) {}
	// note: when load mesh to VAOs bind only needed attribs 
	//       from render technique or if present material tech
  
  // for each chunk
  glGenVertexArrays(1, &_self->chunk->hw_vao);
  glBindVertexArray(_self->chunk->hw_vao);
  
  glGenBuffers(1, &_self->chunk->hw_index);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _self->chunk->hw_index);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * _self->chunk->num_indices, _self->chunk->indices, GL_STATIC_DRAW);
  
  // Create the buffers for the vertices attributes
  glGenBuffers(4, &_self->hw_buf);

  // Generate and populate the buffers with vertex attributes and the indices
  glBindBuffer(GL_ARRAY_BUFFER, _self->hw_buf.vert);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * _self->num_vertices, _self->vertices, GL_STATIC_DRAW);
  glEnableVertexAttribArray(NGINE_ATTR_VERTEX);
  glVertexAttribPointer(NGINE_ATTR_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, 0);

  if(_self->uvs) {
    glBindBuffer(GL_ARRAY_BUFFER, _self->hw_buf.uv);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * _self->chunk->num_indices, _self->uvs, GL_STATIC_DRAW);
    glEnableVertexAttribArray(NGINE_ATTR_UV);
    glVertexAttribPointer(NGINE_ATTR_UV, 2, GL_FLOAT, GL_FALSE, 0, 0);
  }
// 
//   if(_mesh->normals) {
//     glBindBuffer(GL_ARRAY_BUFFER, _ent->hw->normal);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * _ent->mesh->num_indices/3, _ent->mesh->normals, GL_STATIC_DRAW);
//     glEnableVertexAttribArray(GLSA_NORMAL);
//     glVertexAttribPointer(GLSA_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);
//   }

  
  glBindVertexArray(0);

#if DEBUG
  gl_get_error();
#endif
}

struct rbCollisionShape* ngine_mesh_make_coll_shape(struct ngine_mesh* _self, int _shape_type) {
  if(_shape_type == NGINE_SHAPE_BOX) {
    _self->coll_shape = RB_shape_new_box(30, 1, 30);
  } /*else if(_shape_type == NGINE_SHAPE_POINT) {
    coll_shape = RB_shape_new_gimpact_mesh();
  } */else if(_shape_type == NGINE_SHAPE_SPHERE) {
    _self->coll_shape = RB_shape_new_sphere(1);
  } else if(_shape_type == NGINE_SHAPE_TRIMESH) {
    uint32_t num_tris = 0;
    for(int i = 0; i != _self->num_chunks; ++i) {
      num_tris += _self->chunk[i].num_indices/3;
    }
    rbMeshData* mesh_data = RB_trimesh_data_new(num_tris, _self->num_vertices);
    RB_trimesh_add_vertices(mesh_data, _self->vertices, _self->num_vertices, 3*sizeof(float));
    // fot every chunk
    for(int i = 0; i != _self->num_chunks; ++i) {
      for(uint32_t ii = 0; ii != _self->chunk[i].num_indices/3; ++ii) {
	RB_trimesh_add_triangle_indices(mesh_data, ii, _self->chunk[i].indices[ii*3], _self->chunk[i].indices[ii*3+1], _self->chunk[i].indices[ii*3+2]);
      }
    }
    RB_trimesh_finish(mesh_data);
    _self->coll_shape = RB_shape_new_trimesh(mesh_data);
  } /*else if(_shape_type == NGINE_SHAPE_CONVEX) {
    coll_shape = RB_shape_new_convex_hull();
  } */else if(_shape_type == NGINE_SHAPE_GIMPACT) {
    uint32_t num_tris = 0;
    for(int i = 0; i != _self->num_chunks; ++i) {
      num_tris += _self->chunk[i].num_indices/3;
    }
    rbMeshData* mesh_data = RB_trimesh_data_new(num_tris, _self->num_vertices);
    RB_trimesh_add_vertices(mesh_data, _self->vertices, _self->num_vertices, 3*sizeof(float));
    // fot every chunk
    for(int i = 0; i != _self->num_chunks; ++i) {
      for(uint32_t ii = 0; ii != _self->chunk[i].num_indices/3; ++ii) {
	RB_trimesh_add_triangle_indices(mesh_data, ii, _self->chunk[i].indices[ii*3], _self->chunk[i].indices[ii*3+1], _self->chunk[i].indices[ii*3+2]);
      }
    }
    RB_trimesh_finish(mesh_data);

    _self->coll_shape = RB_shape_new_gimpact_mesh(mesh_data);
  }
  return _self->coll_shape;
}
