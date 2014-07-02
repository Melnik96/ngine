#include <stdio.h>
#include <malloc.h>

#include "awol/awol.h"

#include "mesh.h"
#include "material.h"
#include "math/vector.h"

#include "obj.h"

struct ngine_mesh* ngine_mesh_import_obj(const char* _file_name) {
//   struct awol_model* obj = awol_create_model(_file_name);
//   
//   struct ngine_mesh* mesh = calloc(1, sizeof(struct ngine_mesh));
//   
//   mesh->vertices = obj->vertices;
//   mesh->uvs = obj->textures;
// //   mesh->normals = obj->normals;
// 
//   
//   // materials
//   struct ngine_material* mat = calloc(obj->max_mtl, sizeof(struct ngine_material));
//   for(int i = 0; i != obj->max_mtl; ++i) {
//     mat[i].difuse_color = *(vec3*)obj->mtl[i]->Kd;
//     mat[i].specular_color = *(vec3*)obj->mtl[i]->Ks;
//     mat[i].ambient_color = *(vec3*)obj->mtl[i]->Ka;
//     mat[i].emissive_color = *(vec3*)obj->mtl[i]->Ke;
//   }
//   
//   // chunks
//   mesh->num_chunks = obj->max_chunk;
//   mesh->chunk = calloc(obj->max_chunk, sizeof(struct ngine_chunk));
//   
//   for(int i = 0; i != obj->max_chunk; ++i) {
//     mesh->chunk[i].mtl = &(mat[i]);
//     
//     mesh->chunk[i].num_indices = obj->chunk[i]->max_tri/2;
//     mesh->chunk[i].v_indices = malloc(mesh->chunks[i].num_indices * sizeof(int32_t));
// //     mesh->chunks[i].uv_indices = malloc(mesh->chunks[i].num_indices * sizeof(int32_t));
//     
//     for(int i1 = 0; i1 != obj->chunk[i]->max_tri; i1+=2) {
//       mesh->chunks[i].v_indices[i1] = obj->chunk[i]->tri_index[i1];// +1+2
// //       mesh->chunks[i].uv_indices[i1] = obj->chunk[i]->tri_index[i1+1];// +1+2
//     }
//   }

}
