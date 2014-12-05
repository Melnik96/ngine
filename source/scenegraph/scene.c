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

#include <string.h>
#include <malloc.h>
#include <pthread.h>

#include "core/timer.h"
#include "sc_node.h"

#include "scene.h"

def_modable_struct(ngine_scene);

struct ngine_scene {
  char* 			name;
  struct ngine_sc_node* 	root_object;
  
  uint32_t 			num_sc_node_update_handlers;
  sc_node_update_handler_t* 	sc_node_update_handlers;
  
  uint32_t num_mods;
  void** mods;
};

void update_obj_handler(struct ngine_sc_node* _obj, float* _time_elapsed);

struct ngine_scene* ngine_scene_create(char* _name, char _auto_create_root_obj) {
  struct ngine_scene* new_scene = calloc(1, sizeof(struct ngine_scene));
  new_scene->name = _name;
  
  if(_auto_create_root_obj) {
    new_scene->root_object = ngine_sc_node_create(new_scene, "root_object", NGINE_SC_OBJ_NULL);
  } else {
    new_scene->root_object = NULL;
  }
//   struct {
//     void(*on_update)(struct ngine_sc_node* _sc_node, float _time_elapsed);
//     void(*on_colide)();
//   };
  
  return new_scene;
}

void ngine_scene_delete(struct ngine_scene* _self) {
  free(_self->name);
  free(_self->sc_node_update_handlers);
  tree_for_each(_self->root_object, ngine_sc_node_delete);
  free(_self);
}

void ngine_scene_update(struct ngine_scene* _self, float _elapsed) {
  tree_for_each2(_self->root_object, update_obj_handler, &_elapsed);
}

void* scenegraph_thr_handler(struct ngine_scene* _scene) {
  struct ngine_timer* tim = ngine_timer_create();
  ngine_timer_start(tim);
    
  while(1) {
    float diff = ngine_timer_elapsed(tim);
    ngine_scene_update(_scene, diff);
    usleep(1000000/100); // TODO fps control mechanism
  }
  
  ngine_timer_delete(tim);
}

void ngine_scene_start(struct ngine_scene* _self) {
  pthread_t scenegraph_thr;
  pthread_create(&scenegraph_thr, 0, scenegraph_thr_handler, _self);
}

void ngine_scene_add_update_handler(struct ngine_scene* _self, sc_node_update_handler_t _handler) {
  _self->sc_node_update_handlers = realloc(_self->sc_node_update_handlers, sizeof(sc_node_update_handler_t));
  _self->sc_node_update_handlers[_self->num_sc_node_update_handlers] = _handler;
  _self->num_sc_node_update_handlers += 1;
}

#include "physics/scene_phys.h"
#include "physics/sc_node_phys.h"
#include "physics/RBI_api.h"
void update_obj_handler(struct ngine_sc_node* _obj, float* _time_elapsed) {
  if(_obj->num_mods) {
    obj_get_mod(_self_mod, _obj, ngine_sc_node, phys);
    RB_body_get_position(_self_mod->rigid_body, _obj->pos.val);
    printf("x: %f y: %f z: %f\n", _obj->pos.x, _obj->pos.y, _obj->pos.z);
    RB_body_get_orientation(_self_mod->rigid_body, _obj->orient.val);
    printf("x: %f y: %f z: %f w: %f\n", _obj->orient.x, _obj->orient.y, _obj->orient.z, _obj->orient.w);
  } 
  
  for(uint32_t i = 0; i != _obj->num_update_cbs; ++i) {
    _obj->update_cbs[i](_obj, *_time_elapsed);
  }
    
  // call costom update hendlers
  for(uint32_t i = 0; i != _obj->scene->num_sc_node_update_handlers; ++i) {
    _obj->scene->sc_node_update_handlers[i](_obj);
  }
  
//   for(uint32_t i = 0; i != _obj->num_intersect_cbs; ++i) {
//     _obj->intesect_cbs[i].intersect_cb(_obj, *_time_elapsed);
//   }
  
  ngine_sc_node_upd_mat(_obj);
}

#include <kazmath/mat4.h>

void ngine_sc_node_upd_mat(struct ngine_sc_node* _self) {
  mat4 tmp_mat, tmp_mat2;

//   kmMat4Identity(&_self->matrix);
  
//   kmMat4Scaling(tmp_mat, _self->scale, _self->scale, _self->scale);
//   kmMat4Multiply(&_self->matrix, &_self->matrix, tmp_mat);
  
  kmMat4RotationQuaternion(&tmp_mat, &_self->orient);
//   kmMat4Multiply(&_self->matrix, &tmp_mat, &_self->matrix);
  
  kmMat4Translation(&tmp_mat2, _self->pos.x, _self->pos.y, _self->pos.z);
  kmMat4Multiply(&tmp_mat, &tmp_mat2, &tmp_mat);
  
  if(_self->link.parent != NULL) {
    kmMat4Multiply(&tmp_mat, &((struct ngine_sc_node*)_self->link.parent)->matrix, &tmp_mat);
  } // all parents must be updated already
  
  _self->matrix = tmp_mat;
}
