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


struct engine {
  struct GLFWwindow* window;
  struct viewport* viewport;
  char* gl_ver;
//   uint8_t num_scenes;
//   struct scene* scenes;
  struct array* scenes;
};

int neng_init(struct engine* _self, char* _win_name);
int neng_shutdown(struct engine* _self);
int neng_frame(struct engine* _self, float _elapsed);

void neng_get_opengl_version(char* _ver);

int neng_load_shader(char* );

int neng_deserialize_blend(struct sc_obj* _top_obj, void* _blend);

#endif /* __ENGINE_H__ */
