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

#include "technique.h"

struct ngine_tech* ngine_tech_create() {
  struct ngine_tech* new_tech = calloc(1, sizeof(struct ngine_tech));
  
  //   new_tech->gl_vendor = GL_VENDOR_NONE;
  new_tech->gl_ver = 30;
  new_tech->glsl_ver = 130;
  
  new_tech->deferred = 1;
  new_tech->ssao = 1;
  
  new_tech->num_render_passes = 3;
  
  new_tech->render_passes = calloc(3, sizeof(struct ngine_render_pass));
}

void ngine_tech_delete(struct ngine_tech* _self) {

}

void ngine_tech_add_pass(struct ngine_tech* _self, struct ngine_render_pass* _pass) {

}
