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

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "array.h"
#include "tree.h"

#include "math/matrix.h"

#include "viewport.h"
#include "engine.h"
#include "camera.h"
#include "scene.h"
#include "sc_obj.h"
#include "entity.h"
#include "mesh.h"


int neng_init(struct engine* _self, char* _win_name) {
  memset(_self, 0, sizeof(struct engine));
  //init GL
  // Initialise GLFW
  if(!glfwInit())
    return -1;
  /* Create a windowed mode window and its OpenGL context */
//   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  _self->window = glfwCreateWindow(640, 480, _win_name, NULL, NULL);
  if(!_self->window) {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(_self->window);
  
  glewExperimental = GL_TRUE;
  if(glewInit() != GLEW_OK) { return 0; }
  
  _self->gl_ver = malloc(6);
  neng_get_opengl_version(_self->gl_ver);
  printf("OpenGL version %s\n", _self->gl_ver);
  
  return 1;
}

mat4* vp_matrix;
int neng_frame(struct engine* _self, float _elapsed) {
  if(glfwWindowShouldClose(_self->window)) { return 0; }
  
  /* Render here */
  /**
   * mul view(camera)_matrix and proj(viewport)_matrix = view_proj_mat
   * for each obj mul model_matrix and view_proj_mat = model_view_proj_mat;
   * 	render one obj
   */
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  mat4_mul_of(vp_matrix, _self->viewport->proj_matrix, _self->viewport->camera->model_matrix);
  
  tree_for_each(_self->scenes->root_object, update_obj_handler);
  
  glfwSwapBuffers(_self->window);
  glfwPollEvents();
//   printf("frame\n");
  return 1;
}

int neng_shutdown(struct engine* _self) {
  glfwTerminate();
}

#ifndef GLEW_VERSION_4_4
#define GLEW_VERSION_4_4 0
#endif
void neng_get_opengl_version(char* _ver) {
  if(GLEW_VERSION_4_4) { memcpy(_ver, "4.4", 4); }
  else if(GLEW_VERSION_4_3) { memcpy(_ver, "4.3", 4); }
  else if(GLEW_VERSION_4_2) { memcpy(_ver, "4.2", 4); }
  else if(GLEW_VERSION_4_1) { memcpy(_ver, "4.1", 4); }
  else if(GLEW_VERSION_4_0) { memcpy(_ver, "4.0", 4); }
  else if(GLEW_VERSION_3_3) { memcpy(_ver, "3.3", 4); }
  else if(GLEW_VERSION_3_2) { memcpy(_ver, "3.2", 4); }
  else if(GLEW_VERSION_3_1) { memcpy(_ver, "3.1", 4); }
  else if(GLEW_VERSION_3_0) { memcpy(_ver, "3.0", 4); }
  else if(GLEW_VERSION_2_1) { memcpy(_ver, "2.1", 4); }
  else if(GLEW_VERSION_2_0) { memcpy(_ver, "2.0", 4); }
  else if(GLEW_VERSION_1_5) { memcpy(_ver, "1.5", 4); }
  else if(GLEW_VERSION_1_4) { memcpy(_ver, "1.4", 4); }
  else if(GLEW_VERSION_1_3) { memcpy(_ver, "1.3", 4); }
  else if(GLEW_VERSION_1_2_1) { memcpy(_ver, "1.2.1", 6); }
  else if(GLEW_VERSION_1_2) { memcpy(_ver, "1.2", 4); }
  else if(GLEW_VERSION_1_1) { memcpy(_ver, "1.1", 4); }
  else { memcpy(_ver, "0.0", 4); }
}

//intern
void update_obj_handler(void* _node) {
  struct sc_obj* _node = _node;
  
  if(_node->engine->viewport->camera->updated) {}
  
  if(_node->updated) {
    if(memcmp(_node->type, "entity", 6) && sc_obj_check_visible(_node, cur_cam)) {
      //http://www.flipcode.com/archives/Frustum_Culling.shtml
      //http://blog.makingartstudios.com/?p=155
      //update model_view_proj_mat
      mat4* mvp_matrix;
      mat4_mul_of(mvp_matrix, &_node->model_matrix, vp_matrix);//need mul parent model_matrix
      struct sc_obj* tmp_node;
      mat4* parent_matrix;
      for(;tmp_node != NULL; tmp_node = tmp_node->parent) {
	mat4_mul_of(mvp_matrix, mvp_matrix, tmp_node->model_matrix);
      }
      //draw
      draw(((struct entity*)_node->typed_obj), mvp_matrix);//need frustum optimization
    }
    else if(memcmp(_node->type, "camera", 6)) {
      
    }
    else if(memcmp(_node->type, "light", 6)) {}
  }
}

void draw(struct entity* _entity, mat4* _mvp_mat) {
  _entity->meshes->;
}
