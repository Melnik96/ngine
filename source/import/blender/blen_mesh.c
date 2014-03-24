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

#include <malloc.h>

#include "makesdna/DNA_mesh_types.h"
#include "makesdna/DNA_meshdata_types.h"
#include "blenkernel/BKE_DerivedMesh.h"

#include "mesh.h"

#include "blen_mesh.h"

struct mesh* blen_mesh_convert(struct Mesh* _blen_mesh) {
  struct mesh* new_mesh = malloc(sizeof(struct mesh));
  
  new_mesh->num_vertices = _blen_mesh->totvert;
  new_mesh->num_indices = _blen_mesh->totface*3;// TODO new_mesh->num_faces
  
  for(int i = 0; i != _blen_mesh->totvert; ++i) {
    new_mesh->vertices[i] = _blen_mesh->mvert[i].co;
  }
  
  for(int i = 0;; i += 6) {
    new_mesh->indices[i] = _blen_mesh->mface->v1;
    new_mesh->indices[i+1] = _blen_mesh->mface->v2;
    new_mesh->indices[i+2] = _blen_mesh->mface->v3;
    
    new_mesh->indices[i+3] = _blen_mesh->mface->v1;
    new_mesh->indices[i+4] = _blen_mesh->mface->v3;
    new_mesh->indices[i+5] = _blen_mesh->mface->v4;
  }
  
  // UV
//   for(int i = 0;; ++i) {
//     new_mesh->uv[i] = _blen_mesh->mtface[i].uv[0];
//   }

  return new_mesh;
}
