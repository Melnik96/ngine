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

#include <memory.h>
#include <pthread.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <kazmath/mat4.h>

#include "render_target.h"
#include "sc_node.h"
#include "scene.h"
#include <entity.h>

#include "core/log.h"
#include "core/timer.h"
#include "technique.h"
#include "techs/gl44_tech.h"

#include "render.h"

// internal
void gl_debug_cb(GLenum source,
                                           GLenum type,
                                           GLuint id,
                                           GLenum severity,
                                           GLsizei length,
                                           const GLchar* message,
                                           void* userParam);

struct ngine_render_front* ngine_render_front_create() {
  struct ngine_render_front* new_render = malloc(sizeof(struct ngine_render_front));
  return new_render;
}

void ngine_render_front_delete(struct ngine_render_front* _self) {
  free(_self);
}

void* render_front_thr_handler(struct ngine_render_front* _rndr_front) {
  while(1) {
    ngine_render_front_update(_rndr_front);
    usleep(1000000/60);
  }
}

void ngine_render_front_start(struct ngine_render_front* _self) {
  pthread_t render_front_thr;
  pthread_create(&render_front_thr, 0, render_front_thr_handler, _self);
}

void ngine_render_queue_update(struct ngine_sc_node* _sc_node, struct ngine_render_queue* _queue) {
  if(_sc_node->type == NGINE_SC_OBJ_ENTITY) {
    // TODO frustum culling
    ngine_render_queue_add_entity(_queue, ((struct ngine_entity*)_sc_node->attached_obj)->mesh, &_sc_node->matrix);
  }
} // TODO it must be handlers for 3d scene or 2d gui with diffrent graph systems

void ngine_render_front_update(struct ngine_render_front* _self) {
  struct ngine_render_queue* cur_queue = NULL;
  
  for(uint32_t i = 0; i != _self->back_render->num_queues; ++i) {
    cur_queue = &_self->back_render->render_queue[i];
    tree_for_each2(cur_queue->render_target->camera->scene->root_object, ngine_render_queue_update, cur_queue);
//     ngine_render_queue_done(cur_queue);
    cur_queue->done = 1;
//     printf("frontend ngine_render_front_update\n");
  }
}

void ngine_render_front_set_backend(struct ngine_render_front* _self, struct ngine_render_back* _rndr_back) {
  _self->back_render = _rndr_back;
}

struct ngine_render_queue* ngine_render_front_add_target(struct ngine_render_front* _self, struct ngine_render_target* _target, struct ngine_tech* _rndr_tech) {
  struct ngine_render_queue* new_queue = calloc(1, sizeof(struct ngine_render_queue));
  
  new_queue->render_target = _target;
  new_queue->tech = _rndr_tech;
  
  _self->back_render->num_queues = 1;
  _self->back_render->render_queue = new_queue;
  
  return new_queue;
}

void ngine_render_queue_add_entity(struct ngine_render_queue* _self, struct ngine_mesh* _mesh, mat4* _model) {
  if(_self->num_entities == _self->alloc_entities) {
    _self->entities = realloc(_self->entities, sizeof(struct ngine_render_entity)*(_self->num_entities+1));
  }
  
  kmMat4 tmp_mat;
  
  kmMat4Multiply(&tmp_mat, &_self->render_target->view_mat, _model);
  kmMat4Multiply(&_self->entities[_self->num_entities].mvp_mat, &_self->render_target->proj_mat, &tmp_mat);
  
  _self->entities[_self->num_entities].mesh = _mesh;
  
  _self->num_entities++;
  _self->alloc_entities++;
}

void ngine_render_queue_done(struct ngine_render_queue* _self) {
  _self->done = 1;
}

// void ngine_render_queue_add_item(struct ngine_render_queue* _self, uint32_t _type, struct ngine_render_item* _item) {
//   if(_type == NGINE_SC_OBJ_ENTITY) {
//     if(_self->num_entities == _self->alloc_entities) {
//       _self->entities = realloc(_self->entities, sizeof(struct ngine_render_item)*(_self->num_entities+1));
//     }
//     _self->entities[_self->num_entities] = *_item;
//     _self->num_entities++;
//     _self->alloc_entities++;
//   } else if(_type == NGINE_SC_OBJ_LIGHT) {
//     if(_self->num_lights == _self->alloc_lights) {
//       _self->lights = realloc(_self->lights, sizeof(struct ngine_render_item)*(_self->num_lights+1));
//     }
//     _self->lights[_self->num_lights] = *_item;
//     _self->num_lights++;
//     _self->alloc_lights++;
//   }
// }


// backend
struct ngine_render_back* ngine_render_back_create(struct GLFWwindow* _win) {
  struct ngine_render_back* new_render = calloc(1, sizeof(struct ngine_render_back));
  
  // make context current. But also this engine need to be used as display server throught wayland so...
  glfwMakeContextCurrent(_win);
  new_render->render_window = _win;
  
//   glewExperimental=1;
  uint32_t err = 0;
  if((err = glewInit()) != GLEW_OK) {
    error("glew_init failled: %s", glewGetErrorString(err));
  }
  
  new_render->gl_vendor_string = glGetString(GL_VENDOR);
  new_render->gl_version_string = glGetString(GL_VERSION);
  new_render->gl_renderer_string = glGetString(GL_RENDERER);
  new_render->gl_extensions_string = glGetString(GL_EXTENSIONS);
  
  int max_gl_draw_bufs = 0;
  glGetIntegerv(GL_MAX_DRAW_BUFFERS, &max_gl_draw_bufs);
  
  debug("\n  OpenGL Info:\n"
	"    vendor: %s\n"
	"    renderer: %s\n"
	"    version: %s\n"
	"    max draw buffers: %i", new_render->gl_vendor_string, new_render->gl_renderer_string, new_render->gl_version_string, max_gl_draw_bufs);
  
  int tmp_gl_ver1 = 0, tmp_gl_ver2 = 0;
//   glGetIntegerv(GL_MAJOR_VERSION, &tmp_gl_ver1);
//   glGetIntegerv(GL_MINOR_VERSION, &tmp_gl_ver2);
  sscanf(new_render->gl_version_string, "%i.%i", &tmp_gl_ver1, &tmp_gl_ver2);
  new_render->gl_ver = tmp_gl_ver1*10 + tmp_gl_ver2;
  
  
  //check minimum needed extensions
  if(new_render->gl_ver <= 30 && !GLEW_ARB_vertex_array_object) {
    error("render: VAO not supported");
  }
  
#ifdef DEBUG
  if(GLEW_KHR_debug) {
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(gl_debug_cb, new_render);
    debug("render: gl debug message callback set");
  } else if(GLEW_ARB_debug_output) {
    debug("render: gl debug message callback not set");
  } else if(GLEW_AMD_debug_output) {
//     glDebugMessageCallbackAMD();
    debug("render: gl debug message callback not set");
  }
#endif
  
  // sutup techniqueue
  /*if(new_render->gl_ver >= 44) {
    debug("render: technique 'gl44'");
    new_render->tech = ngine_create_tech_gl44();
  }*//* else if(new_render->gl_ver >= 30) {
    debug("render: technique 'gl30'");
    new_render->tech = ngine_create_tech_gl30();
  } else if(new_render->gl_ver >= 21) {
    debug("render: technique 'gl21_low'");
    new_render->tech = ngine_create_tech_gl21_low();
  }*//* else {
    error("render: all render techniques not supported on this device");
  }*/
  
  return new_render;
}

void ngine_render_back_delete(struct ngine_render_back* _self) {
  free(_self);
}

void ngine_render_context_current(struct ngine_render_back* _self) {
  glfwMakeContextCurrent(_self->render_window);
}

void* render_back_thr_handler(struct ngine_render_back* _rndr_back) {
  struct ngine_timer* tim = ngine_timer_create();
  ngine_timer_start(tim);
  
//   ngine_render_context_current(_rndr_back);
  glfwMakeContextCurrent(_rndr_back->render_window);
  
  while(1) {
    float diff = ngine_timer_elapsed(tim);
    ngine_render_back_frame(_rndr_back, diff);
//     #ifdef DEBUG
      printf("fps %f elapsed time %f\n", 1.f/diff, diff);
//     #endif
    usleep(1000000/60);
  }
  
  ngine_timer_delete(tim);
}

void ngine_render_back_start(struct ngine_render_back* _self) {
  pthread_t render_back_thr;
  
  glfwMakeContextCurrent(0);
  pthread_create(&render_back_thr, 0, render_back_thr_handler, _self);
}

void ngine_render_back_frame(struct ngine_render_back* _self, double _elapsed) {
  struct ngine_render_queue* 	cur_queue = NULL;
  
//   glClearColor(0,0,0,1);
  
  for(uint32_t i = 0; i != _self->num_queues; ++i) {				// queue
    cur_queue = &_self->render_queue[i];
    
    if(cur_queue->done) {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      
      printf("backend cur_queue->done\n");
      cur_queue->tech->render_frame_cb(cur_queue /*, _elapsed*/);
    
      cur_queue->done = 0;
    
      cur_queue->num_entities = 0;
      cur_queue->num_lights = 0;
      
      glfwSwapBuffers(_self->render_window);// costil
    }
  }
  
// #ifndef NDEBUG
  uint32_t err = 0;
  if((err = glGetError()) != GL_NO_ERROR) {
    error("OpenGL error: %s", glewGetErrorString(err));
  }
// #endif
}


// intern
void gl_debug_cb(GLenum source,
                                           GLenum type,
                                           GLuint id,
                                           GLenum severity,
                                           GLsizei length,
                                           const GLchar* message,
                                           void* userParam) {

    debug("%s", message);
//     debug("type: ");
// //     switch (type) {
// //     case GL_DEBUG_TYPE_ERROR:
// //         cout << "ERROR";
// //         break;
// //     case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
// //         cout << "DEPRECATED_BEHAVIOR";
// //         break;
// //     case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
// //         cout << "UNDEFINED_BEHAVIOR";
// //         break;
// //     case GL_DEBUG_TYPE_PORTABILITY:
// //         cout << "PORTABILITY";
// //         break;
// //     case GL_DEBUG_TYPE_PERFORMANCE:
// //         cout << "PERFORMANCE";
// //         break;
// //     case GL_DEBUG_TYPE_OTHER:
// //         cout << "OTHER";
// //         break;
// //     }
// //     cout << endl;
//  
// //     cout << "id: "<    cout << "severity: ";
// //     switch (severity){
// //     case GL_DEBUG_SEVERITY_LOW:
// //         cout << "LOW";
// //         break;
// //     case GL_DEBUG_SEVERITY_MEDIUM:
// //         cout << "MEDIUM";
// //         break;
// //     case GL_DEBUG_SEVERITY_HIGH:
// //         cout << "HIGH";
// //         break;
// //     }
// //     cout << endl;
//     printf("---------------------opengl-callback-end--------------\n");
}