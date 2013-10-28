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

#include "math.h"

struct camera {
//   mat4 view_matrix;//матрица позиции наблюдения//матриця позиції береться з sc_obj->model_matrix
  mat4 proj_matrix;
};

// int camera_look_at(struct camera* _self, struct scene_object* _target);

#endif /* __CAMERA_H__ */
