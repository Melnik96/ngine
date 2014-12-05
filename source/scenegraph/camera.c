/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2013  <copyright holder> <email>
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

#include "camera.h"

struct ngine_camera {
  float fov;
  float near, far;
  float left;
  float right;
  float bottom;
  float top;
  
  char orto;
  char updated;
};

struct ngine_camera* ngine_camera_create() {
  struct ngine_camera* new_cam = calloc(1, sizeof(struct ngine_camera));
  return new_cam;
}

void ngine_camera_persp(struct ngine_camera* _self, float _fov) {
  _self->fov = _fov;
  _self->updated = 1;
}

void ngine_camera_orto(struct ngine_camera* _self, float _left, float _right, float _bottom, float _top) {
  _self->left = _left;
  _self->right = _right;
  _self->bottom = _bottom;
  _self->top = _top;
  _self->orto = 1;
  _self->updated = 1;
}

void ngine_camera_nearfar(struct ngine_camera* _self, float _near, float _far) {
  _self->near = _near;
  _self->far = _far;
  _self->updated = 1;
}
