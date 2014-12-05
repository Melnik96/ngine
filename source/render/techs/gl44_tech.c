/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2014  <copyright holder> <email>
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

#include <GL/glew.h>
#include <malloc.h>

#include "render/technique.h"
#include "render/render.h"
#include "render/mesh.h"
#include "render/shader_prog.h"
#include "core/iofile.h"

#include "gl44_tech.h"

void gl44_render_frame(struct ngine_render_queue* _queue);

struct ngine_gl44_tech* ngine_create_tech_gl44() {
  struct ngine_gl44_tech* new_tech = malloc(sizeof(struct ngine_gl44_tech));
  
  struct ngine_shdr_prog* shdr = ngine_shdr_prog_create("gl44");
  
  ngine_shdr_prog_compile(shdr, file_rdbufp("base.vert"), GL_VERTEX_SHADER);
  ngine_shdr_prog_compile(shdr, file_rdbufp("base.frag"), GL_FRAGMENT_SHADER);
  
  ngine_shdr_prog_bind_attr(shdr, NGINE_ATTR_VERTEX, "a_vert");
//   ngine_shdr_prog_bind_attr(shdr, NGINE_ATTR_NORMAL, "a_norm");
  
  ngine_shdr_prog_link(shdr);
  
  shdr->uniform_locs[NGINE_UNIFORM_MVP] = ngine_shdr_prog_get_unf_loc(shdr, "u_mvp");
  
  new_tech->shdr = shdr;
  
  new_tech->base_tech.render_frame_cb = gl44_render_frame;
  
}

void gl44_render_frame(struct ngine_render_queue* _queue) {
  // need
  // - mesh
  // - transform
  
  glUseProgram(((struct ngine_gl44_tech*)_queue->tech)->shdr->id);
  
  for(uint32_t m_id = 0; m_id != _queue->num_entities; ++m_id) {
    struct ngine_mesh* cur_mesh = _queue->entities[m_id].mesh;
    mat4* cur_mvp = &_queue->entities[m_id].mvp_mat;
    
    if(cur_mesh->hw_buf_need_update) { ngine_mesh_update(cur_mesh); cur_mesh->hw_buf_need_update = 0; }
    
    glUniformMatrix4fv(((struct ngine_gl44_tech*)_queue->tech)->shdr->uniform_locs[NGINE_UNIFORM_MVP], 1, 0, cur_mvp);
    
//     int row, columns;
//     for (int row=0; row<4; row++) {
//       for(int columns=0; columns<4; columns++)
//         printf("%f     ", cur_mvp->m[row][columns]);
//       
//       printf("\n");
//     }
    
    for(uint32_t c_id = 0; c_id != cur_mesh->num_chunks; ++c_id) {
      struct ngine_chunk* cur_chunk = &cur_mesh->chunk[c_id];
      
      glBindVertexArray(cur_chunk->hw_vao);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cur_chunk->hw_index); // seams like it need only with intel gpu
      glDrawElements(GL_TRIANGLES, cur_chunk->num_indices, GL_UNSIGNED_INT, NULL);
    }
  }
}
