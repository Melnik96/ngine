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

#include "scenegraph/sc_node.h"
#include "scenegraph/camera.h"

#include "render_target.h"

struct ngine_render_target* ngine_render_target_create(struct ngine_sc_node* _camera, uint32_t _w, uint32_t _h) {
  struct ngine_render_target* new_target = calloc(1, sizeof(struct ngine_render_target));
  
  if(_camera) {
    ngine_render_target_attach_cam(new_target, _camera);
    ngine_render_target_size(new_target, _w, _h);
  }
  
  return new_target;
}

void ngine_render_target_delete(struct ngine_render_target* _self) {

}

inline void ngine_render_target_update(struct ngine_render_target* _self) {
//   if(_self->need_update) {
    struct ngine_camera* cam = (struct ngine_camera*)(ngine_sc_node_get_attached(_self->camera));
//     kmMat4PerspectiveProjection(&_self->proj_mat, cam->fov, (float)_self->fbuf->width/(float)_self->fbuf->height, cam->near, cam->far);
    kmMat4Inverse(&_self->view_mat, &(ngine_sc_node_get_matrix(_self->camera)));
//   }
}

void ngine_render_target_attach_cam(struct ngine_render_target* _self, struct ngine_sc_node* _cam_node) {
  _self->camera = _cam_node;
}

void ngine_render_target_size(struct ngine_render_target* _self, uint32_t _w, uint32_t _h) {
  struct ngine_camera* cam = (struct ngine_camera*)(ngine_sc_obj_get_attached(_self->camera));
  kmMat4PerspectiveProjection(&_self->proj_mat, 
			      ngine_camera_get_fov(cam), 
			      (float)_w/(float)_h, 
			      cam->near, 
			      cam->far);
}
