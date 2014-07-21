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

#ifndef PASS_H
#define PASS_H

#include <stdint.h>

struct ngine_render_pass {
  struct ngine_shdr_prog* shdr_prog;
  // subroutines needs to be active
  uint32_t* subroutine_ids;
  
  uint32_t fbo_read;
  uint32_t fbo_draw;
  
  // vertex data attribs
  char a_vert;
  char a_color;
  char a_uv;
  char a_norm;
  
  // uniforms
  char u_mvp;
  char u_model;
  char u_tex;
  char u_time;
  
  // input textures
  uint32_t num_tex_in;
  uint32_t tex_in_type;// GLRGB
  // in_textures
//   uint32_t* frag_data_locs;
  
  // output textures
  uint32_t num_tex_out;
  uint32_t tex_out_type;
  uint32_t* frag_data_locs;
  
  // gl active states
  uint32_t* active_states;
  uint32_t polygon_mode;
};

#endif // PASS_H
