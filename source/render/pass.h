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
  
  struct ngine_framebuffer* fbuf_read;
  struct ngine_framebuffer* fbuf_draw;
  
//   void (*procces)(struct ngine_render_pass* _pass, struct ngine_render_queue* _queue);
  void (*pass_start)(void);
  void (*pass_end)(void);
  
  char render_ents;
  char render_lights;
  
  // vertex data attribs
  char a_vert;
  char a_color;
  char a_uv;
  char a_norm;
  
  // uniforms
  char u_mvp;
  char u_model;
  char u_tex;
  char u_light_pos;
  char u_light_dcolor;
  char u_time;
  
  // gl active states
  uint16_t* active_states;
  uint32_t polygon_mode;
};

#endif // PASS_H
