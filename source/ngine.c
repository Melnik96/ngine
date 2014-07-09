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

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <fmodex/fmod.h>

#include <kazmath/mat4.h>
#include <kazmath/vec3.h>

#include "ngine.h"
#include "window.h"
#include "log.h"
#include "viewport.h"
#include "sc_obj.h"
#include "scene.h"
#include "entity.h"
#include "sound_mgr.h"
#include "material.h"
#include "shader_prog.h"
#include "render/render.h"
#include "render_target.h"
#include "camera.h"
#include "physics/rigidbody/RBI_api.h"

#include <kazmath/kazmath.h>

//intern
void update_obj_handler(struct ngine_sc_node* _obj, float* _time_elapsed, struct ngine* _ngine);

int ngine_init(struct ngine* _self) {
  debug("ngine init");
  
  if(!glfwInit()) {
    return -1;
  }
  
  // render create
//   _self->render = ngine_render_create();
  
  // init FMOD sound system
  FMOD_System_Create(&_self->fmod_sound);
  FMOD_System_Init(_self->fmod_sound, 32, FMOD_INIT_NORMAL, NULL);
  
  // init base shaders
//   ngine_assets_mgr_get_file(ngine, NGINE_SHADER_ASSET, "base.vert.glsl");
//   ngine_shdr_prog_create();
//   ngine_shdr_source();
//   ngine_shdr_prog_bind_attr();
//   ngine_shdr_prog_link();
  
  return 1;
}

struct ngine* ngine_create() {
  struct ngine* new_ngine = calloc(1, sizeof(struct ngine));
  if(ngine_init(new_ngine)) {
    return new_ngine;
  } else {
    return NULL;
  }
}

int ngine_shutdown(struct ngine* _self) {
  FMOD_System_Close(_self->fmod_sound);
}

int ngine_frame(struct ngine* _self, float _elapsed) {
  glfwPollEvents();
  //for each render target
//   for(int i = 0; ; ++i) {
/*    if(&_self->windows[i] != NULL && 
       &_self->windows[i] != NULL &&
       _self->windows[i].viewport != NULL &&
       _self->windows[i].viewport->camera != NULL)*/ 
//     {
//       struct ngine_sc_node* root_sc_obj = tree_get_head(_self->windows[i].viewport->camera);
      tree_for_each3(_self->scenes->root_object, update_obj_handler, &_elapsed, _self);
      
      if(_self->scenes->dyn_world) {
	RB_dworld_step_simulation(_self->scenes->dyn_world, _elapsed, 1, 0.5);
      }
      ngine_render_frame(_self->render, 0);
      
      glfwSwapBuffers(_self->windows->win);
//       glfwPollEvents();
//     } /*else {
//       break;
//     }*/
//   }
  FMOD_System_Update(_self->fmod_sound);
}

//intern
int sc_obj_check_visible(aabb* _aabb, vec3* _proj_mat) {
//   vec3 projected[8];
//   
//   for(uint8_t i = 0; i != 8; ++i) {
//     vec3_mat4_mul_of(&projected[i], &_aabb->val[i], _proj_mat);
//     if(projected[i].x > 1.f || projected[i].x < -1.f ||
//        projected[i].y > 1.f || projected[i].y < -1.f ||
//        projected[i].z > 1.f || projected[i].z < -1.f) { return 0; } else { return 1; }
//   }
  return 1;
}

void update_obj_handler(struct ngine_sc_node* _obj, float* _time_elapsed, struct ngine* _ngine) {
  // pipeline
  // - get array of active lights
  // - get visible sc_objs(entities)
  // - for each sc_obj
  // -   get lights for sc_obj
  // -   set gl_render_data
  // -   gl_draw
  
  if(_obj->listener->on_update) {
    _obj->listener->on_update(_obj, *_time_elapsed);
  }
  
//   if(1/*_obj->translated*/) {
//     if(_obj->dynamic) {
//       RB_body_set_loc_rot();
//     } else {
//       ngine_sc_node_upd_mat(_obj);
//     }
//   }
  
  if(_obj->dynamic) {
    RB_body_get_transform_matrix(_obj->rigid_body, &_obj->matrix.m);
  } else {
    ngine_sc_node_upd_mat(_obj);
  }
  
  if(_obj->type == NGINE_SC_OBJ_ENTITY/* && sc_obj_check_visible(_obj, _viewport->camera)*/) {
//     debug("procces entity obj");
    /*else if(_obj->phys_active) { 
    RB_get_transform_matrix();
    }*/
    
      struct ngine_camera* __cam = ((struct ngine_camera*)_ngine->rend_target->camera->attached_obj);
      kmMat4PerspectiveProjection(&_ngine->rend_target->mat_proj, __cam->fov, (float)_ngine->rend_target->width/(float)_ngine->rend_target->height, __cam->near, __cam->far);
      
    kmMat4* mvp = calloc(1, sizeof(kmMat4));
      mat4 tmp_mat;
      kmMat4Inverse(&tmp_mat, &_ngine->rend_target->camera->matrix);
      kmMat4Multiply(&tmp_mat, &tmp_mat, &_obj->matrix);
      kmMat4Multiply(mvp, &_ngine->rend_target->mat_proj, &tmp_mat);

      struct ngine_render_op* rop = calloc(1, sizeof(struct ngine_render_op));
      rop->entity = _obj;
      rop->mvp_mat = mvp;
//       rop->// render target
      ngine_render_queue_add_op(_ngine->render->render_queue, rop);
  }
  else if(_obj->type == NGINE_SC_OBJ_SPEAKER) {
//     debug("procces snd_speaker obj");
    FMOD_Channel_Set3DAttributes(_obj->attached_obj, &_obj->pos, &(vec3){0,0,0});//TODO fix velocity
  }
  else if(_obj->type == NGINE_SC_OBJ_CAMERA) {
    ngine_sc_node_upd_mat(_obj);
  }
}
