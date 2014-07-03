#include <stdio.h>
#include <malloc.h>

#include "awol/awol.h"

#include "mesh.h"
#include "material.h"
#include "math/vector.h"

#include "obj.h"

struct ngine_mesh* ngine_mesh_import_obj(const char* _file_name) {
  struct awol_model* obj = awol_create_model(_file_name);
  
  struct ngine_mesh* mesh = calloc(1, sizeof(struct ngine_mesh));
  
  mesh->num_vertices = obj->max_vertices;
  mesh->vertices = obj->vertices;
//   mesh->uvs = obj->textures;
//   mesh->normals = obj->normals;

  
  // materials
  struct ngine_material* mat = calloc(obj->max_mtl, sizeof(struct ngine_material));
  for(int i = 0; i != obj->max_mtl; ++i) {
    mat[i].difuse_color = *(vec3*)obj->mtl[i]->Kd;
    mat[i].specular_color = *(vec3*)obj->mtl[i]->Ks;
    mat[i].ambient_color = *(vec3*)obj->mtl[i]->Ka;
    mat[i].emissive_color = *(vec3*)obj->mtl[i]->Ke;
  }
  
  // chunks
  mesh->num_chunks = obj->max_chunk;
  mesh->chunk = calloc(obj->max_chunk, sizeof(*(mesh->chunk)));
  
  for(int i = 0; i != obj->max_chunk; ++i) {
    mesh->uvs = malloc(obj->chunk[i]->max_tri*3*sizeof(vec2));
  
    mesh->chunk[i].mtl = &(mat[i]);
    
    mesh->chunk[i].num_indices = obj->chunk[i]->max_tri*3;
    mesh->chunk[i].indices = malloc(mesh->chunk[i].num_indices * sizeof(int32_t));
//     mesh->chunks[i].uv_indices = malloc(mesh->chunks[i].num_indices * sizeof(int32_t));
    
    for(int f = 0; f != obj->chunk[i]->max_tri*6; f+=6) {
      mesh->chunk[i].indices[f/2] = obj->chunk[i]->tri_index[f];
      mesh->chunk[i].indices[f/2+1] = obj->chunk[i]->tri_index[f+2];
      mesh->chunk[i].indices[f/2+2] = obj->chunk[i]->tri_index[f+4];
//       printf("tringle: %i, %i, %i\n", mesh->chunk[i].indices[f/2], mesh->chunk[i].indices[f/2+1], mesh->chunk[i].indices[f/2+2]);
      mesh->uvs[f/2].x = ((float*)obj->textures)[obj->chunk[i]->tri_index[f+1]];
      mesh->uvs[f/2].y = ((float*)obj->textures)[obj->chunk[i]->tri_index[f+1]+1];
      mesh->uvs[f/2+1].x = ((float*)obj->textures)[obj->chunk[i]->tri_index[f+3]];
      mesh->uvs[f/2+1].y = ((float*)obj->textures)[obj->chunk[i]->tri_index[f+3]+1];
      mesh->uvs[f/2+2].x = ((float*)obj->textures)[obj->chunk[i]->tri_index[f+5]];
      mesh->uvs[f/2+2].y = ((float*)obj->textures)[obj->chunk[i]->tri_index[f+5]+1];
//       printf("uv: %f, %f, %f\n", mesh->uvs[f/2].x, mesh->uvs[f/2].y, mesh->uvs[f/2+2]);
    }
  }
  
  return mesh;
}
