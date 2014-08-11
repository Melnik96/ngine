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
  
  if(_camera) {
    new_target->camera = _camera;
    struct ngine_camera* cam = (struct ngine_camera*)(_camera->attached_obj);
    kmMat4PerspectiveProjection(&new_target->proj_mat, cam->fov, (float)_w/(float)_h, cam->near, cam->far);
  }
  
  return new_target;
}

void ngine_render_target_delete(struct ngine_render_target* _self) {

}

inline void ngine_render_target_update(struct ngine_render_target* _self) {
  struct ngine_camera* cam = (struct ngine_camera*)_self->camera->attached_obj;
  if(_self->need_update || cam->updated) {
    if(cam->orto) {
      kmMat4OrthographicProjection(&_self->proj_mat, cam->left, cam->right, cam->bottom, cam->top, cam->near, cam->far);
    } else {
      kmMat4PerspectiveProjection(&_self->proj_mat, cam->fov, (float)_self->fbuf->width/(float)_self->fbuf->height, cam->near, cam->far);
    }
  }
  if(_self->camera->translated) {
    kmMat4Inverse(&_self->view_mat, &_self->camera->matrix);
  }
}
