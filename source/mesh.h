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
#ifndef __MESH_H__
#define __MESH_H__

#include <stdint.h>
#include "math/vector.h"

struct mesh {
  uint16_t num_indices;
  uint32_t num_vertices;
  uint16_t* indices;
  uint16_t* normals;
  vec3* tangent;
  vec3* vertices;
  vec3* colors;
  vec2* uv;
  aabb aabb;
  //TODO add half-edged
};

#endif /* __MESH_H__ */
