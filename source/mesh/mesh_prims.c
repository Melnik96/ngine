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

// #include "mesh.h"
// 
// #include "mesh_prims.h"
// 
// struct ngine_mesh* ngine_mesh_create_quad(float l, float r, float b, float t) {
//   struct ngine_mesh* quad_mesh = ngine_mesh_create(1);
//   quad_mesh->num_vertices = 4;
//   quad_mesh->vertices = (vec3[]){
//     {l, b, 0},
//     {l, t, 0},
//     {r, t, 0},
//     {r, b, 0}
//   };
//   quad_mesh->chunk->num_indices = 6;
//   quad_mesh->chunk->indices = (uint32_t[]){0,2,1, 0,3,2};
//   
//   quad_mesh->plane_size = (vec2){r-l, t-b};
//   
//   ngine_mesh_update(quad_mesh);
//   
//   return quad_mesh;
// }
