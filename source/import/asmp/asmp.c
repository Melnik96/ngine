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

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#include <kazmath/kazmath.h>
#include <kazmath/mat4.h>

#include "log.h"
#include "scene.h"

#include "asmp.h"
#include "sc_obj.h"
#include "light.h"
#include "entity.h"
#include "mesh.h"

// intern
void for_each_ainode(struct aiScene* sc, struct aiNode* ai_node, struct ngine_sc_node* sc_node);

void ngine_scene_add_import_assimp(struct ngine_scene* _self, const char* _file) {
  struct aiScene* sc = aiImportFile(_file, 
				    aiProcessPreset_TargetRealtime_MaxQuality |
				    aiProcess_Triangulate |
				    aiProcess_ImproveCacheLocality
  );
  if(sc == NULL) {
    error("import asmp failed: %s", aiGetErrorString());
  }
  
  debug("num cameras %i", sc->mNumCameras);
  for(uint32_t i = 0; i != sc->mNumCameras; ++i) {
    struct ngine_sc_node* node_cam = ngine_sc_node_create(_self, "camera", NGINE_SC_OBJ_CAMERA);
    node_cam->name = sc->mCameras[i]->mName.data;
    node_cam->attached_obj = ngine_camera_create(sc->mCameras[i]->mHorizontalFOV, sc->mCameras[i]->mClipPlaneNear, sc->mCameras[i]->mClipPlaneFar);
    kmQuaternionLookRotation(&node_cam->orient, &sc->mCameras[i]->mLookAt, &sc->mCameras[i]->mUp);
    node_cam->pos.x = sc->mCameras[i]->mPosition.x;
    node_cam->pos.y = sc->mCameras[i]->mPosition.y;
    node_cam->pos.z = sc->mCameras[i]->mPosition.z;
    tree_add_child((struct tree*)_self->root_object, (struct tree*)node_cam);
  }
  
  debug("num lights %i", sc->mNumLights);
  for(uint32_t i = 0; i != sc->mNumLights; ++i) {
    struct ngine_sc_node* node_light = ngine_sc_node_create(_self, "light", NGINE_SC_OBJ_LIGHT);
    struct ngine_light* light = calloc(1, sizeof(struct ngine_light));
    node_light->attached_obj = light;
    
    if(sc->mLights[i]->mType == aiLightSource_POINT) {
      light->type = NGINE_LIGHT_POINT;
    } else if(sc->mLights[i]->mType == aiLightSource_SPOT) {
      light->type = NGINE_LIGHT_SPOT;
    }
    
//     light->ambient = sc->mLights[i]->mColorAmbient;
//     light->diffuse = sc->mLights[i]->mColorDiffuse;
//     light->specular = sc->mLights[i]->mColorSpecular;
    // it not all!!
    
    node_light->pos.x = sc->mLights[i]->mPosition.x;
    node_light->pos.y = sc->mLights[i]->mPosition.y;
    node_light->pos.z = sc->mLights[i]->mPosition.z;
//     sc->mLights[i]->mDirection;
  }
  
  debug("num materials %i", sc->mNumMaterials);
  for(uint32_t i = 0; i != sc->mNumMaterials; ++i) {
    // nop
  }
  
  debug("num meshes %i", sc->mNumMeshes);
  for_each_ainode(sc, sc->mRootNode, _self->root_object);
}

// intern
void for_each_ainode(struct aiScene* sc, struct aiNode* ai_node, struct ngine_sc_node* sc_node) {
  struct ngine_mesh* mesh = calloc(1, sizeof(struct ngine_mesh));
  
  for(uint32_t i = 0; i != ai_node->mNumMeshes; ++i) {
    struct aiMesh* paiMesh = sc->mMeshes[ai_node->mMeshes[i]];
  
    mesh->vertices = realloc(mesh->vertices, (mesh->num_vertices+paiMesh->mNumVertices)*sizeof(vec3));
    memcpy(mesh->vertices/*+mesh->num_vertices*/, paiMesh->mVertices, paiMesh->mNumVertices*sizeof(vec3));
    
    // dopilit nada
    if(paiMesh->mTextureCoords[0]) {
      mesh->uvs = malloc(paiMesh->mNumVertices*sizeof(vec2));
      for(uint32_t i = 0; i != paiMesh->mNumVertices; ++i) {
	mesh->uvs[i].x = paiMesh->mTextureCoords[0][i].x;
	mesh->uvs[i].y = paiMesh->mTextureCoords[0][i].y;
      }
    }
    
    mesh->num_chunks += 1;
    mesh->chunk = realloc(mesh->chunk, mesh->num_chunks*sizeof(*(mesh->chunk)));
    memset(mesh->chunk, 0, mesh->num_chunks*sizeof(*(mesh->chunk)));
  
    uint32_t c_i = mesh->num_chunks - 1;
    mesh->chunk[c_i].num_indices = 3*paiMesh->mNumFaces;
    debug("num faces: %i", mesh->chunk[c_i].num_indices);
    mesh->chunk[c_i].indices = calloc(1, mesh->chunk[c_i].num_indices*sizeof(uint32_t));
  
    for (unsigned int i = 0 ; i < paiMesh->mNumFaces; ++i) {
      struct aiFace* face = &paiMesh->mFaces[i];
    
      mesh->chunk[c_i].indices[i*3] = face->mIndices[0] + mesh->num_vertices;
      mesh->chunk[c_i].indices[i*3+1] = face->mIndices[1] + mesh->num_vertices;
      mesh->chunk[c_i].indices[i*3+2] = face->mIndices[2] + mesh->num_vertices;
    }
    
    // material
    
    mesh->num_vertices += paiMesh->mNumVertices;
  }
  
  
  debug("mesh num verts: %i", mesh->num_vertices);
  struct ngine_sc_node* new_node = sc_node;
  if(ai_node->mNumMeshes != 0) {
    ngine_mesh_update(mesh);
  // create entity
    // add to node
    struct ngine_entity* new_ent = ngine_entity_create("imp_entity", mesh);
    new_node = ngine_sc_node_create(sc_node->scene, "node_imp", NGINE_SC_OBJ_ENTITY);
  
    new_node->attached_obj = new_ent;
    new_ent->mesh = mesh;
//     kmMat4Transpose(&ai_node->mTransformation, &ai_node->mTransformation);
    new_node->pos.x = ai_node->mTransformation.a4;
    new_node->pos.y = ai_node->mTransformation.b4;
    new_node->pos.z = ai_node->mTransformation.c4;
    
    mat3 rot_mat, n_mat;
    kmMat4ExtractRotation(&rot_mat, &ai_node->mTransformation);
    kmMat3Transpose(&n_mat, &rot_mat);
    kmQuaternionRotationMatrix(&new_node->orient, &n_mat);
    
    tree_add_child(sc_node, new_node);
    debug("sc_node added");
  }
  
  for(unsigned int n = 0; n != ai_node->mNumChildren; ++n) {
    for_each_ainode(sc, ai_node->mChildren[n], new_node);
  }
}
