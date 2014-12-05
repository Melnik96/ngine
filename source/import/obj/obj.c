#include <stdio.h>
#include <malloc.h>

#include <assimp/scene.h>
#include <assimp/cimport.h>

#include "awol/awol.h"

#include "core/log.h"
#include "mesh/mesh.h"
#include "scenegraph/material.h"
#include "math/vector.h"

#include "obj.h"

// struct ngine_mesh* ngine_mesh_import_obj(const char* _file_name) {
//   struct awol_model* obj = awol_create_model(_file_name);
//   
//   struct ngine_mesh* mesh = calloc(1, sizeof(struct ngine_mesh));
//   
//   mesh->num_vertices = obj->max_vertices;
//   mesh->vertices = obj->vertices;
//   mesh->uvs = obj->textures;
// //   mesh->normals = obj->normals;
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
//   mesh->chunk = calloc(obj->max_chunk, sizeof(*(mesh->chunk)));
//   
//   for(int i = 0; i != obj->max_chunk; ++i) {
//     mesh->uvs = malloc(obj->chunk[i]->max_tri*3*sizeof(vec2));
//   
//     mesh->chunk[i].mtl = &(mat[i]);
//     
//     mesh->chunk[i].num_indices = obj->chunk[i]->max_tri*3;
//     mesh->chunk[i].indices = malloc(mesh->chunk[i].num_indices * sizeof(int32_t));
// //     mesh->chunks[i].uv_indices = malloc(mesh->chunks[i].num_indices * sizeof(int32_t));
//     
//     for(int f = 0; f != obj->chunk[i]->max_tri*6; f+=6) {
//       mesh->chunk[i].indices[f/2] = obj->chunk[i]->tri_index[f];
//       mesh->chunk[i].indices[f/2+1] = obj->chunk[i]->tri_index[f+2];
//       mesh->chunk[i].indices[f/2+2] = obj->chunk[i]->tri_index[f+4];
//     }
//     // uvs
//   }
//   
//   return mesh;
// }

struct ngine_mesh* ngine_mesh_import_obj(const char* _file_name) {
  struct ngine_mesh* mesh = calloc(1, sizeof(struct ngine_mesh));
  
  struct aiScene* sc = aiImportFile(_file_name, 0);
  struct aiMesh* paiMesh = sc->mMeshes[0];
  
  mesh->num_vertices = paiMesh->mNumVertices;
  mesh->vertices = paiMesh->mVertices;
  mesh->uvs = malloc(paiMesh->mNumVertices*sizeof(vec2));
  for(uint32_t i = 0; i != paiMesh->mNumVertices; ++i) {
    mesh->uvs[i].x = paiMesh->mTextureCoords[0][i].x;
    mesh->uvs[i].y = paiMesh->mTextureCoords[0][i].y;
  }
//   printf("uv: %f, %f\n    %f, %f\n    %f, %f\n", mesh->uvs[0].x, mesh->uvs[0].y, mesh->uvs[1].x, mesh->uvs[1].y, mesh->uvs[2].x, mesh->uvs[2].y);
  
  mesh->num_chunks = 1;
  mesh->chunk = calloc(1, sizeof(*(mesh->chunk)));
  
  mesh->chunk->num_indices = 3*paiMesh->mNumFaces;
//   debug("num faces: %i", mesh->chunk->num_indices);
  mesh->chunk->indices = calloc(1, mesh->chunk->num_indices*sizeof(uint32_t));
  
  for (unsigned int i = 0 ; i < paiMesh->mNumFaces; ++i) {
    struct aiFace* face = &paiMesh->mFaces[i];
    
    mesh->chunk->indices[i*3] = face->mIndices[0];
    mesh->chunk->indices[i*3+1] = face->mIndices[1];
    mesh->chunk->indices[i*3+2] = face->mIndices[2];
  }
  
  mesh->hw_buf_need_update = 1;
  
  
  return mesh;
}
