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

#include "viewport.h"

#include "engine.h"
#include "camera.h"
#include "scene.h"
#include "scene_object.h"

int neng_init(struct engine* _self, char* _win_name) {
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
//   glewInit();
  if(glewInit() != GLEW_OK) { return 0; }
  
//   _self->gl_ver = malloc(6);
//   neng_get_opengl_version(_self->gl_ver);
//   printf("OpenGL version %s\n", _self->gl_ver);
  
  return 1;
}


// An array of 3 vectors which represents 3 vertices
static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};
int neng_frame(struct engine* _self, float _elapsed) {
//   glfwMakeContextCurrent(_self->window);
  if(glfwWindowShouldClose(_self->window)) { return 0; }
  /* Render here */
  glClear(GL_COLOR_BUFFER_BIT);
  // This will identify our vertex buffer
  GLuint vertexbuffer;
// Generate 1 buffer, put the resulting identifier in vertexbuffer
  glGenBuffers(1, &vertexbuffer);

// The following commands will talk about our 'vertexbuffer' buffer
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

// Give our vertices to OpenGL.
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
  // 1rst attribute buffer : vertices
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glVertexAttribPointer(
    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
    3,                  // size
    GL_FLOAT,           // type
    GL_FALSE,           // normalized?
    0,                  // stride
    (void*)0            // array buffer offset
  );

// Draw the triangle !
  glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

  glDisableVertexAttribArray(0);

  // calc view_projection matrix
//   float vp_matrix[4][4];
//   if(!mat4_mul(vp_matrix, _self->viewport->proj_matrix, _self->viewport->camera->view_matrix)) { exit(1); }
  // for each object calc model_view_proj
//   float parents_matrix[4][4];
//   struct scene_object* cur_obj;
//   while(1) {
//     cur_obj = _self->scenes->root_object->childs;
//     
//   }
//   glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
  
  glfwSwapBuffers(_self->window);
  glfwPollEvents();
//   printf("frame\n");
  return 1;
}

int neng_shutdown(struct engine* _self) {
  glfwTerminate();
}

void neng_get_opengl_version(char* _ver) {
  if(GLEW_VERSION_4_3) { memcpy(_ver, "4.3", 4); }
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
