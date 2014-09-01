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
#include <tiff.h>

#include "log.h"
#include "iofile.h"
#include "sc_obj.h"
#include "entity.h"
#include "mesh.h"
#include "material.h"
#include "shader_prog.h"

#include "import/obj/obj.h"
#include <../targa/tga.h>

#include "framebuffer.h"
#include "texture.h"

#include "technique.h"
#include "pass.h"

#include "techs/gl30_tech.h"

#include "render.h"
#include <light.h>
#include <render_target.h>

// internal
struct ngine_tech* ngine_create_tech_gl21_low();
void gl_debug_callback(GLenum source,
                                           GLenum type,
                                           GLuint id,
                                           GLenum severity,
                                           GLsizei length,
                                           const GLchar* message,
                                           void* userParam);

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
  
  int max_gl_draw_bufs = 0;
  glGetIntegerv(GL_MAX_DRAW_BUFFERS, &max_gl_draw_bufs);
  
  debug("\n  OpenGL Info:\n"
	"    vendor: %s\n"
	"    renderer: %s\n"
	"    version: %s\n"
	"    max draw buffers: %i", new_render->gl_vendor_string, new_render->gl_renderer_string, new_render->gl_version_string, max_gl_draw_bufs);
  
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
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(gl_debug_callback, new_render);
    debug("render: gl debug message callback set");
  } else if(GLEW_ARB_debug_output) {
    debug("render: gl debug message callback not set");
  } else if(GLEW_AMD_debug_output) {
//     glDebugMessageCallbackAMD();
    debug("render: gl debug message callback not set");
  }
#endif
  
  // sutup techniqueue
  /*if(new_render->gl_ver >= 44) {
    debug("render: technique 'gl44'");
    new_render->tech = ngine_create_tech_gl44();;
  } else *//*if(new_render->gl_ver >= 30) {
    debug("render: technique 'gl30'");
    new_render->tech = ngine_create_tech_gl30();;
  } else */if(new_render->gl_ver >= 21) {
    debug("render: technique 'gl21_low'");
    new_render->tech = ngine_create_tech_gl21_low();
  } else {
    error("render: all render techniques not supported on this device");
  }
  
  if(new_render->tech->deferred) {
    new_render->sphere_mesh = ngine_mesh_import_obj("media/models/sphere.obj");
    ngine_mesh_update(new_render->sphere_mesh);
  }
  if(new_render->tech->ssao) {
    new_render->quad_mesh = ngine_mesh_create(1);
    new_render->quad_mesh->num_vertices = 4;
    new_render->quad_mesh->vertices = (vec3[]){
      {-1, -1, 0},
      {-1,  1, 0},
      { 1,  1, 0},
      { 1, -1, 0}
    };
    new_render->quad_mesh->chunk->num_indices = 6;
    new_render->quad_mesh->chunk->indices = (uint32_t[]){0,2,3, 0,1,2};
    ngine_mesh_update(new_render->quad_mesh);
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
  struct ngine_render_queue* 	cur_queue = NULL;
  struct ngine_render_pass* 	cur_pass = NULL;
  struct ngine_render_item* 	cur_item = NULL;
  struct ngine_entity* 		cur_entity = NULL;
  struct ngine_shdr_prog* 	last_shdr_prog = NULL;
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  for(uint32_t i = 0; i != _self->num_queues; ++i) {				// queue
    cur_queue = &_self->render_queue[i];
    for(uint32_t i2 = 0; i2 != _self->tech->num_render_passes; ++i2) {		// pass
      cur_pass = &_self->tech->render_passes[i2];
      
      if(cur_pass->pass_start) { cur_pass->pass_start(); }
      
      if(cur_pass->shdr_prog != last_shdr_prog) {
	last_shdr_prog = cur_pass->shdr_prog;
	glUseProgram(cur_pass->shdr_prog->id);
	// if subroutines supported, change subroutine and not switch shader
      }
      
      if(cur_pass->texs_read) {
	for(int i = 0; i != cur_pass->num_texs_read; ++i) {
	  glActiveTexture(GL_TEXTURE0 + cur_pass->texs_read[i]->id);
	  glBindTexture(GL_TEXTURE_2D, cur_pass->texs_read[i]->id);
	  glUniform1i(cur_pass->shdr_prog->uniform_locs[NGINE_UNIFORM_GTEX0+i], cur_pass->texs_read[i]->id);
	}
      }
      if(cur_pass->fbuf_draw) {
	ngine_framebuffer_bind_draw(cur_pass->fbuf_draw);
      } else {
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
      }
      
      // render entities
      if(cur_pass->render_ents) {
	for(uint32_t i3 = 0; i3 != _self->render_queue[i].num_entities; ++i3) {	// render_op
	  cur_item = &cur_queue->entities[i3];
	
	  if(cur_pass->u_mvp) {
	    glUniformMatrix4fv(cur_pass->shdr_prog->uniform_locs[NGINE_UNIFORM_MVP], 1, 0, cur_item->mvp_mat);
	  }
	  if(cur_pass->u_model) {
	    glUniformMatrix4fv(cur_pass->shdr_prog->uniform_locs[NGINE_UNIFORM_MODEL], 1, 0, &cur_item->sc_node->matrix);
	  }
	
	  cur_entity = (struct ngine_entity*)cur_item->sc_node->attached_obj;
	  for(uint32_t i4 = 0; i4 != cur_entity->mesh->num_chunks; ++i4) {
	    if(cur_pass->u_tex) {
	      if(cur_entity->mesh->chunk[i4].mtl && cur_entity->mesh->chunk[i4].mtl->tex_color) {
		glActiveTexture(GL_TEXTURE0 + cur_entity->mesh->chunk[i4].mtl->tex_color->id);
		glBindTexture(GL_TEXTURE_2D, cur_entity->mesh->chunk[i4].mtl->tex_color->id);
		glUniform1i(cur_pass->shdr_prog->uniform_locs[NGINE_UNIFORM_TEX], cur_entity->mesh->chunk[i4].mtl->tex_color->id);
	      }
	    }
	  
	    // send material to shader
	  
	    glBindVertexArray(cur_entity->mesh->chunk[i4].hw_vao);
	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cur_entity->mesh->chunk[i4].hw_index);
	    glDrawElements(GL_TRIANGLES, cur_entity->mesh->chunk[i4].num_indices, GL_UNSIGNED_INT, NULL);
	  }
	}
      }
	
      if(cur_pass->render_lights) {
	// draw sphares around all lights
	for(uint32_t i = 0; i != cur_queue->num_lights; ++i) {
	  struct ngine_light* l = cur_queue->lights[i].sc_node->attached_obj;
	  vec3* l_pos = &cur_queue->lights[i].sc_node->pos;
	  glUniformMatrix4fv(cur_pass->shdr_prog->uniform_locs[NGINE_UNIFORM_MVP], 1, 0, cur_queue->lights[i].mvp_mat);
	  glUniform3fv(cur_pass->shdr_prog->uniform_locs[NGINE_UNIFORM_LIGHT_DIFUSE], 1, &l->diffuse);
	  glUniform3fv(cur_pass->shdr_prog->uniform_locs[NGINE_UNIFORM_LIGHT_POS], 1, l_pos);
	  
	  glBindVertexArray(_self->sphere_mesh->chunk->hw_vao);
	  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _self->sphere_mesh->chunk->hw_index);
	  glDrawElements(GL_TRIANGLES, _self->sphere_mesh->chunk->num_indices, GL_UNSIGNED_INT, NULL);
	}
      }
      
      if(cur_pass->render_screen_quad) {
// 	ngine_shder_prog_unf(NGINE_UNIFORM_PROJ, ptr*);
	glUniformMatrix4fv(cur_pass->shdr_prog->uniform_locs[NGINE_UNIFORM_PROJ], 1, 0, &cur_queue->render_target->proj_mat);
	glUniformMatrix4fv(cur_pass->shdr_prog->uniform_locs[NGINE_UNIFORM_VIEW], 1, 0, &cur_queue->render_target->view_mat);
	
	glBindVertexArray(_self->quad_mesh->chunk->hw_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _self->quad_mesh->chunk->hw_index);
	glDrawElements(GL_TRIANGLES, _self->quad_mesh->chunk->num_indices, GL_UNSIGNED_INT, NULL);
      }
      
      if(cur_pass->pass_end) { cur_pass->pass_end(); }
    }
      _self->render_queue[i].num_entities = 0;
      _self->render_queue[i].num_lights = 0;
  }
#ifndef NDEBUG
  uint32_t err = 0;
  if((err = glGetError()) != GL_NO_ERROR) {
    error("OpenGL error: %s", glewGetErrorString(err));
  }
#endif
}

void ngine_render_queue_add_item(struct ngine_render_queue* _self, uint32_t _type, struct ngine_render_item* _item) {
  if(_type == NGINE_SC_OBJ_ENTITY) {
    if(_self->num_entities == _self->alloc_entities) {
      _self->entities = realloc(_self->entities, sizeof(struct ngine_render_item)*(_self->num_entities+1));
    }
    _self->entities[_self->num_entities] = *_item;
    _self->num_entities++;
    _self->alloc_entities++;
  } else if(_type == NGINE_SC_OBJ_LIGHT) {
    if(_self->num_lights == _self->alloc_lights) {
      _self->lights = realloc(_self->lights, sizeof(struct ngine_render_item)*(_self->num_lights+1));
    }
    _self->lights[_self->num_lights] = *_item;
    _self->num_lights++;
    _self->alloc_lights++;
  }
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
  
  pass0->render_ents = 1;
  
  new_tech->deferred = 1;
  pass0->render_lights = 1;
  
  pass0->a_vert = 1;
  pass0->u_mvp = 1;
  pass0->u_tex = 1;
  
  pass0->shdr_prog = shdr = ngine_shdr_prog_create("base_gl21_low");
  
  ngine_shdr_prog_compile(shdr, file_rdbufp("../../shaders/techniques/render/gl21/base.vert"), GL_VERTEX_SHADER);
  ngine_shdr_prog_compile(shdr, file_rdbufp("../../shaders/techniques/render/gl21/base.frag"), GL_FRAGMENT_SHADER);
  
  ngine_shdr_prog_bind_attr(shdr, NGINE_ATTR_VERTEX, "a_vert");
  ngine_shdr_prog_bind_attr(shdr, NGINE_ATTR_UV, "a_uv");
  
  ngine_shdr_prog_link(shdr);
  
  shdr->uniform_locs[NGINE_UNIFORM_MVP] = glGetUniformLocation(shdr->id, "u_mvp");
  if(shdr->uniform_locs[NGINE_UNIFORM_MVP] == -1) {
    error("shader program: get uniform failled");
  }
  shdr->uniform_locs[NGINE_UNIFORM_TEX] = glGetUniformLocation(shdr->id, "u_tex");
  if(shdr->uniform_locs[NGINE_UNIFORM_TEX] == -1) {
    error("shader program: get uniform failled");
  }
  // ngine_shdr_prog_uniform
  
//           параметры OpenGL
//   glClearColor(.4f, 0.2f, 0.0f, 1.0f);
  glEnable(GL_CULL_FACE);
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  
#if CHACHE_SHDR
  ngine_shdr_prog_get_binary();// save binary
#endif
  
  return new_tech;
}

// intern
void gl_debug_callback(GLenum source,
                                           GLenum type,
                                           GLuint id,
                                           GLenum severity,
                                           GLsizei length,
                                           const GLchar* message,
                                           void* userParam) {

    debug("%s", message);
//     debug("type: ");
// //     switch (type) {
// //     case GL_DEBUG_TYPE_ERROR:
// //         cout << "ERROR";
// //         break;
// //     case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
// //         cout << "DEPRECATED_BEHAVIOR";
// //         break;
// //     case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
// //         cout << "UNDEFINED_BEHAVIOR";
// //         break;
// //     case GL_DEBUG_TYPE_PORTABILITY:
// //         cout << "PORTABILITY";
// //         break;
// //     case GL_DEBUG_TYPE_PERFORMANCE:
// //         cout << "PERFORMANCE";
// //         break;
// //     case GL_DEBUG_TYPE_OTHER:
// //         cout << "OTHER";
// //         break;
// //     }
// //     cout << endl;
//  
// //     cout << "id: "<    cout << "severity: ";
// //     switch (severity){
// //     case GL_DEBUG_SEVERITY_LOW:
// //         cout << "LOW";
// //         break;
// //     case GL_DEBUG_SEVERITY_MEDIUM:
// //         cout << "MEDIUM";
// //         break;
// //     case GL_DEBUG_SEVERITY_HIGH:
// //         cout << "HIGH";
// //         break;
// //     }
// //     cout << endl;
//     printf("---------------------opengl-callback-end--------------\n");
}
