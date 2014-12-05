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

/* inclusion guard */
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "math/matrix.h"

struct ngine_camera* 	ngine_camera_create();
void 			ngine_camera_delete();

void 			ngine_camera_persp(struct ngine_camera* _self, float _fov);
void 			ngine_camera_orto(struct ngine_camera* _self, float _left, float _right, float _bottom, float _top);
void 			ngine_camera_nearfar(struct ngine_camera* _self, float _near, float _far);

float 			ngine_camera_get_fov(struct ngine_camera* _self);
float 			ngine_camera_get_left(struct ngine_camera* _self);
float 			ngine_camera_get_right(struct ngine_camera* _self);
float 			ngine_camera_get_button(struct ngine_camera* _self);
float 			ngine_camera_get_top(struct ngine_camera* _self);
float 			ngine_camera_get_near(struct ngine_camera* _self);
float 			ngine_camera_get_far(struct ngine_camera* _self);

#endif /* __CAMERA_H__ */
