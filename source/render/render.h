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

#include <stdint.h>

#include "math/matrix.h"
#include "math/vector.h"

enum {
  GL_VENDOR_NONE = 0,
  GL_VENDOR_NV,
  GL_VENDOR_AMD,
  GL_VENDOR_INTEL,
};

struct ngine_render_entity {
  mat4 			mvp_mat;
  struct ngine_mesh*	mesh;
};

struct ngine_render_light {
  mat4* 	mvp_mat;
};

struct ngine_render_queue {
  unsigned char 		done;
  
  struct ngine_render_target* 	render_target;
  struct ngine_tech* 		tech;
  
  uint32_t 			alloc_lights;
  uint32_t 			num_lights;
  struct ngine_render_light* 	lights;
  
  // TODO change to array
  uint32_t 			alloc_entities;
  uint32_t 			num_entities;
  struct ngine_render_entity* 	entities;
  
  // mutex
}; // then send it to render backend

struct ngine_render_front {
  struct ngine_render_back* back_render;
};

struct ngine_render_back { // seems like it may be one backrender per window
  // gl version and exensions
  uint8_t gl_ver;
  uint8_t glsl_ver;
  uint8_t gl_vendor;// enum
  
  // strings
  const char* gl_vendor_string;
  const char* gl_renderer_string;
  const char* gl_version_string;
  const char* gl_extensions_string;
  
  struct ngine_window* 		render_window;
  
  uint32_t 			num_queues;
  struct ngine_render_queue* 	render_queue;
  // render target contain queue
  
  struct ngine_tech* tech; // comment it!
  
  // options
//   struct {
//     char ssao;
//     float ssao_totStrength;
//     float ssao_strength;
//     float ssao_offset;
//     float ssao_falloff;
//     float ssao_rad;
//   } otps;
};

struct ngine_render_front* 	ngine_render_front_create();
void 				ngine_render_front_delete(struct ngine_render_front* _self);
void 				ngine_render_front_start(struct ngine_render_front* _self);
void 				ngine_render_front_update(struct ngine_render_front* _self);

void 				ngine_render_front_set_backend(struct ngine_render_front* _self, struct ngine_render_back* _rndr_back);

struct ngine_render_queue*	ngine_render_front_add_target(struct ngine_render_front* _self, struct ngine_render_target* _target, struct ngine_tech* _rndr_tech);

// ------------------intern-----------may not use by user--------------
void 				ngine_render_queue_add_entity(struct ngine_render_queue* _self, struct ngine_mesh* _mesh, mat4* _model);
void 				ngine_render_queue_add_light(struct ngine_render_queue* _self, vec3 _pos, quat _rot);
void 				ngine_render_queue_done(struct ngine_render_queue* _self); // now it can be rendered
// --------------------------------------------------------------------

// backend run in separate thread
struct ngine_render_back* 	ngine_render_back_create(struct GLFWwindow* _win);
void 				ngine_render_back_delete(struct ngine_render_back* _self);
void 				ngine_render_back_start(struct ngine_render_back* _self);
void 				ngine_render_back_frame(struct ngine_render_back* _self, double _elapsed); // render render_targets that done setup
void 				ngine_render_context_current(struct ngine_render_back* _self);

/**
 * - vao
 * - set(pos,rot,scale)
 * - material
 */
/**
 * - render fronted - calculate and sort object(matrices and other data). build mvp matrix.
 * - render backend - send data to gpu
 */

#endif // RENDER_H
