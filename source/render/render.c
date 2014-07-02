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

#include "log.h"
#include "iofile.h"
#include "sc_obj.h"
#include "entity.h"
#include "mesh.h"
#include "material.h"
#include "shader_prog.h"

#include "technique.h"
#include "pass.h"

#include "render.h"

// internal
struct ngine_tech* ngine_create_tech_gl21_low();
void gl_debug_callback(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam) {
  debug("GL debug msg: %s", message);
}

struct ngine_render* ngine_render_create() {
  struct ngine_render* new_render = calloc(1, sizeof(struct ngine_render));
  
  uint32_t err = 0;
  if((err = glewInit()) != GLEW_OK) {
    error("glew_init failled: %s", glewGetErrorString(err));
  }
  
  new_render->gl_vendor_string = glGetString(GL_VENDOR);
  new_render->gl_version_string = glGetString(GL_VERSION);
  new_render->gl_renderer_string = glGetString(GL_RENDERER);
  new_render->gl_extensions_string = glGetString(GL_EXTENSIONS);
  
  debug("\n  OpenGL Info:\n"
	"    vendor: %s\n"
	"    renderer: %s\n"
	"    version: %s", new_render->gl_vendor_string, new_render->gl_renderer_string, new_render->gl_version_string);
  
  int tmp_gl_ver1 = 0, tmp_gl_ver2 = 0;
//   glGetIntegerv(GL_MAJOR_VERSION, &tmp_gl_ver1);
//   glGetIntegerv(GL_MINOR_VERSION, &tmp_gl_ver2);
  sscanf(new_render->gl_version_string, "%i.%i", &tmp_gl_ver1, &tmp_gl_ver2);
  new_render->gl_ver = tmp_gl_ver1*10 + tmp_gl_ver2;
  
  
  //check minimum needed extensions
  if(new_render->gl_ver <= 30 && !GLEW_ARB_vertex_array_object) {
    error("render: VAO not supported");
  }
  
#ifndef NDEBUG
  if(GLEW_KHR_debug) {
    glDebugMessageCallback(gl_debug_callback, new_render);
    debug("render: gl debug message callback set");
  } else if(GLEW_ARB_debug_output) {
    debug("render: gl debug message callback set");
  } else if(GLEW_AMD_debug_output) {
//     glDebugMessageCallbackAMD();
    debug("render: gl debug message callback set");
  }
#endif
  
  // sutup techniqueue
  if(new_render->gl_ver >= 21) {
    debug("render: technique 'gl21_low'");
    new_render->tech = ngine_create_tech_gl21_low();;
  } else {
    error("render: all render techniques not supported on this device");
  }
  
  // create first time render queue
  new_render->render_queue = calloc(1, sizeof(struct ngine_render_queue));
  new_render->num_queues = 1;
  
  return new_render;
}

void ngine_render_destroy(struct ngine_render* _self) {

}

void ngine_render_update(struct ngine_render* _self) {

}

void ngine_render_frame(struct ngine_render* _self, double _elapsed) {
  struct ngine_render_pass* 	cur_pass = NULL;
  struct ngine_render_op* 	cur_op = NULL;
  struct ngine_entity* 		cur_entity = NULL;
  struct ngine_shdr_prog* 	last_shdr_prog = NULL;
  
  // 1. build render queue
  // 2. send draw_calls to gpu
  
  for(uint32_t i = 0; i != _self->num_queues; ++i) {				// queue
    for(uint32_t i2 = 0; i2 != _self->tech->num_render_passes; ++i2) {		// pass
      cur_pass = &_self->tech->render_passes[i2];
      
      if(cur_pass->shdr_prog != last_shdr_prog) {
	last_shdr_prog = cur_pass->shdr_prog;
	glUseProgram(cur_pass->shdr_prog->id);
	// if subroutines supported, change subroutine and not switch shader
      }
      
      for(uint32_t i3 = 0; i3 != _self->render_queue[i].num_render_ops; ++i3) {	// render_op
	cur_op = &_self->render_queue[i].render_ops[i3];
	cur_entity = (struct ngine_entity*)cur_op->entity->typed_objs;
	
	for(uint32_t i4 = 0; i4 != cur_entity->mesh->num_chunks; ++i4) {
	  glBindVertexArray(cur_entity->mesh->chunk[i4].hw_vao);
	  
	  if(cur_pass->u_mvp) {
	    glUniformMatrix4fv(cur_pass->shdr_prog->uniform_locs[NGINE_UNIFORM_MVP], 1, 0, cur_op->mvp_mat);
	  }
	  
	  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cur_entity->mesh->chunk[i4].hw_index);
	  glDrawElements(GL_TRIANGLES, cur_entity->mesh->chunk[i4].num_indices, GL_UNSIGNED_INT, NULL);
	}
      }
    }
  }
#ifndef NDEBUG
  uint32_t err = 0;
  if((err = glGetError()) != GL_NO_ERROR) {
    error("OpenGL error: %s", glewGetErrorString(err));
  }
#endif
}




// internal
struct ngine_tech* ngine_create_tech_gl21_low() {
  struct ngine_tech* new_tech = calloc(1, sizeof(struct ngine_tech));
  struct ngine_render_pass* pass0 = calloc(1, sizeof(struct ngine_render_pass));// simple_forward_pass

  struct ngine_shdr_prog* shdr = NULL;
  
  new_tech->gl_vendor = GL_VENDOR_NONE;
  new_tech->gl_ver = 21;
  new_tech->glsl_ver = 12;
  
  new_tech->deferred = 0;
  new_tech->ssao = 0;
  
  new_tech->num_render_passes = 1;
  
  new_tech->render_passes = pass0;
  
  pass0->a_vert = 1;
  pass0->u_mvp = 1;
  
  pass0->shdr_prog = shdr = ngine_shdr_prog_create("base_gl21_low");
  
  ngine_shdr_prog_compile(shdr, file_rdbufp("../../shaders/techniques/render/gl21/base.vert"), GL_VERTEX_SHADER);
  ngine_shdr_prog_compile(shdr, file_rdbufp("../../shaders/techniques/render/gl21/base.frag"), GL_FRAGMENT_SHADER);
  
  ngine_shdr_prog_bind_attr(shdr, NGINE_ATTR_VERTEX, "a_vert");
  
  ngine_shdr_prog_link(shdr);
  
  shdr->uniform_locs[NGINE_UNIFORM_MVP] = glGetUniformLocation(shdr->id, "u_mvp");
  if(shdr->uniform_locs[NGINE_UNIFORM_MVP] == -1) {
    error("shader program: get uniform failled");
  }
  // ngine_shdr_prog_uniform
  
#if CHACHE_SHDR
  ngine_shdr_prog_get_binary();// save binary
#endif
  
  return new_tech;
}
