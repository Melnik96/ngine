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

int neng_frame(struct engine* _self, float _elapsed) {
//   glfwMakeContextCurrent(_self->window);
  if(glfwWindowShouldClose(_self->window)) { return 0; }
  
  /* Render here */
//   struct scene* cur_scene;
//   struct sc_obj* cur_obj;
//   struct sc_obj* root_obj;
//   array_for_each(cur_scene, _self->scenes) {
//     root_obj = cur_scene->root_object;
//     array_for_each(cur_obj, &root_obj->childs) {
//       if(cur_obj->updated) {
// 	//update matrix
//       }
//       if(cur_obj->childs.size != 0) {
// 	array_for_each(cur_obj, &cur_obj->childs) {
// 	  if(cur_obj->updated) {
// 	    //update matrix
// 	  }
// 	}
// 	cur_obj = cur_obj->parent;
//       }
//     }
//   }
  
  glfwSwapBuffers(_self->window);
  glfwPollEvents();
//   printf("frame\n");
  return 1;
}

int neng_shutdown(struct engine* _self) {
  glfwTerminate();
}

void neng_get_opengl_version(char* _ver) {
  /*if(GLEW_VERSION_4_4) { memcpy(_ver, "4.4", 4); }
  else */if(GLEW_VERSION_4_3) { memcpy(_ver, "4.3", 4); }
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
