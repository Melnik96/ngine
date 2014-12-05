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

#include <malloc.h>
#include <pthread.h>

#include "core/timer.h"
#include "RBI_api.h"
#include "scenegraph/scene.h"
#include "physics/scene_phys.h"

#include "scene_phys.h"

void ngine_scene_dynamics_create(struct ngine_scene* _self, vec3* _gravity) {
  if(_self->mods == NULL) {
    _self->mods = realloc(_self->mods, ngine_scene_mods_num*sizeof(void*));
  }
  struct ngine_scene_mod_phys* _self_mod = _self->mods[struct_mod_id(ngine_scene, phys)] = calloc(1, sizeof(struct ngine_scene_mod_phys));
  
  if(_gravity) {
    _self_mod->dyn_world = RB_dworld_new(_gravity);
  } else {
    _self_mod->dyn_world = RB_dworld_new(&(vec3){0,-9.80665,0});
  }
}

void ngine_scene_dynamics_step(struct ngine_scene* _self, float _elapsed) {
  obj_get_mod(_self_mod, _self, ngine_scene, phys);
  
  RB_dworld_step_simulation(_self_mod->dyn_world, _elapsed, 5, 0.01);
}

void* physics_thr_handler(struct ngine_scene* _scene) {
  struct ngine_timer* tim = ngine_timer_create();
  ngine_timer_start(tim);
  
  while(1) {
    float diff = ngine_timer_elapsed(tim);
    ngine_scene_dynamics_step(_scene, diff);
    #ifndef NDEBUG
//       printf("fps %f elapsed time %f\n", 1.f/diff, diff);
    #endif
    usleep(1000000/60); // TODO fps control mechanism
  }
  
  ngine_timer_delete(tim);
}

void ngine_scene_dynamics_start(struct ngine_scene* _self) {
  pthread_t render_back_thr;
  pthread_create(&render_back_thr, 0, physics_thr_handler, _self);
}
