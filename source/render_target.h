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

#include <stdint.h>

#include "math/matrix.h"

#include "render/framebuffer.h"

/**
 * render tardet texture connet to some material texture slot
 * 
 * ngine_render_target_create - if {_w, _h} = 0 then fbuf = 0 (not create fb), render to screan 
 * 
 * ngine_render_target_update - update proj_mat
 */

struct ngine_render_target {
  struct ngine_sc_node* 	camera;
  struct ngine_framebuffer* 	fbuf;
  mat4* 			proj_mat;
  char 				need_update;
};

struct ngine_render_target* 	ngine_render_target_create(struct ngine_sc_node* _camera, uint32_t _w, uint32_t _h);
void 				ngine_render_target_delete(struct ngine_render_target* _self);
void 				ngine_render_target_update(struct ngine_render_target* _self);
inline void 			ngine_render_target_attach_cam(struct ngine_render_target* _self, struct ngine_sc_mode* _cam_node);

#endif // RENDER_TARGET_H
