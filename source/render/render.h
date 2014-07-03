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

#ifndef RENDER_H
#define RENDER_H

enum {
  GL_VENDOR_NONE = 0,
  GL_VENDOR_NV,
  GL_VENDOR_AMD,
  GL_VENDOR_INTEL,
};

struct ngine_render_op {
  mat4* 		mvp_mat;
  mat4* 		model_mat;
  
  struct ngine_sc_node* entity;
  
  uint32_t 		num_lights;
  struct ngine_sc_node* lights;// affect lights
  
};

struct ngine_render_queue {
  // framebuffer
  
  mat4* 		view_mat;
  mat4* 		proj_mat;
  
  // TODO change to array
  uint32_t 			alloc_render_ops;
  uint32_t 			num_render_ops;
  struct ngine_render_op* 	render_ops;
};// one per render target

struct ngine_render {
  // gl version and exensions
  uint8_t gl_ver;
  uint8_t glsl_ver;
  uint8_t gl_vendor;// enum
  
  // strings
  const char* gl_vendor_string;
  const char* gl_renderer_string;
  const char* gl_version_string;
  const char* gl_extensions_string;
  
  uint32_t 			num_queues;
  struct ngine_render_queue* 	render_queue;
  // render target contain queue
  
  struct ngine_tech* tech;
  
  // options
  struct {
    char ssao;
  } otps;
};

struct ngine_render* 		ngine_render_create();
void 				ngine_render_destroy(struct ngine_render* _self);
void 				ngine_render_update(struct ngine_render* _self);
void 				ngine_render_frame(struct ngine_render* _self, double _elapsed);
struct ngine_render_queue*	ngine_render_create_queue();

#endif // RENDER_H


/**
 * per frame pipeline
 *   Begin
 *   Render lights and shadows to texture(deferred_light)
 *   Render objects with color*deferred_light
 *   SSAO
 *   Post effects
 *   End
 */


/**
 * use only one shader_prog(with subroutines) per scene if possible.
 * 
 * render pass {
 *   render queue {
 *     sort entities
 *     sort lights
 *     
 *     create render operations
 *       assotiate entities with affect lights
 *     
 *     render operation {
 *       use_shader(if need)
 *       bind vao
 *       set uniforms
 *       gl_draw per chunk of mesh
 *     }
 *   }
 * }
 * 
 * render passes
 * 1. g_buffer
 * 2. light
 * 3. SSAO and other post processing(in one pass if possible)
 */
