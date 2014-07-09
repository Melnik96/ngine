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

#include "kazmath/kazmath.h"

#include "sc_obj.h"
#include "camera.h"

#include "render_target.h"

struct ngine_render_target* ngine_render_target_create(struct ngine_sc_node* _camera, uint32_t _w, uint32_t _h) {
  struct ngine_render_target* new_target = calloc(1, sizeof(struct ngine_render_target));
  new_target->width = _w;
  new_target->height = _h;
  new_target->camera = _camera;
  
  struct ngine_camera* cam = (struct ngine_camera*)(_camera->attached_obj);
  
  kmMat4PerspectiveProjection(&new_target->mat_proj, cam->fov, (float)_w/(float)_h, cam->near, cam->far);
  
  return new_target;
}

// void ngine_render_target_create(struct ngine_sc_node* _camera, uint32_t _w, uint32_t _h) {
//   struct ngine_render_target* new_target = calloc(1, sizeof(struct ngine_render_target));
//   new_target->width = _w;
//   new_target->height = _h;
//   new_target->camera = _camera;
//   
//   struct ngine_camera* cam = (struct ngine_camera*)(_camera->attached_obj);
//   
//   kmMat4PerspectiveProjection(&new_target->mat_proj, cam->fov, (float)_w/(float)_h, cam->near, cam->far);
// }
