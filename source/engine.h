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

/* inclusion guard */
#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <stdint.h>
#include <pthread.h>
#include "cntr/list.h"

struct job {
  struct list link;
  void*(*handler)(void*);
  void* args;
};

struct engine {
  struct GLFWwindow* window;
  struct viewport* viewport;
  uint8_t num_scenes;
  struct scene* scenes;//list
  struct shader_prog* shaders;
  
  char* gl_ver;
  int active_render;
  uint8_t fixed_fps;//60fps
  
  //threads
//   pthread_t thr_input;//60fps
  pthread_t thr_physics;//30fps
  pthread_t thr_sound;
  pthread_t* thr_workers;//one worker per free core
  pthread_mutex_t mutex_workers;
  pthread_cond_t cond_workers;
  
  struct list jobs;//list
};//TODO multiple contexts

int neng_init(struct engine* _self, char* _win_name);
int neng_shutdown(struct engine* _self);
int neng_frame(struct engine* _self, float _elapsed);

void neng_get_opengl_version(char* _ver);

int neng_load_shader(char* );

int neng_deserialize_blend(struct sc_obj* _top_obj, void* _blend);

#endif /* __ENGINE_H__ */
