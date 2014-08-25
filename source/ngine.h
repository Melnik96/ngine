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

#include "cntr/array.h"

struct ngine {
  struct ngine_window* 		windows;
  struct ngine_scene* 		scenes;
  struct array 			render_targets;
  
  struct assets_mgr* 	assets_mgr;
  struct ngine_render* 	render;
  struct ngine_input* 	input;
  struct FMOD_SYSTEM*	fmod_sound;
  
  pthread_t 		thr_render;
  pthread_t 		thr_input;//60fps
  pthread_t 		thr_physics;//30fps
  
  char 			active_render;
  uint8_t 		fixed_fps;//60fps
};

int 			ngine_init(struct ngine* _self);
struct ngine* 		ngine_create();
struct ngine* 		ngine_intense();
int 			ngine_shutdown(struct ngine* _self);
int 			ngine_frame(struct ngine* _self, float _elapsed);
void 			ngine_start(struct ngine* _self);

#endif /* __ENGINE_H__ */
