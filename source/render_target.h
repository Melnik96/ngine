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

#ifndef RENDER_TARGET_H
#define RENDER_TARGET_H

#include "stdint.h"

#include "math/matrix.h"

struct ngine_render_target {
  union {
    struct ngine_texture* 	rtt_tex;
    struct ngine_framebuffer* 	fbuf;
  };
  
  mat4 mat_proj;
  
  uint32_t width;
  uint32_t height;
  
  struct ngine_sc_node* camera;
};

struct ngine_render_target* ngine_render_target_create(struct ngine_sc_node* _camera, uint32_t _w, uint32_t _h);

#endif // RENDER_TARGET_H
