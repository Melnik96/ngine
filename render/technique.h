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

#ifndef TECHNIQUE_H
#define TECHNIQUE_H

#include <stdint.h>

typedef void(*render_frame_func_t)(struct ngine_render_queue*);

struct ngine_tech {
  render_frame_func_t 		render_frame_cb;
  
  // requirements
  uint8_t 			gl_ver;
  uint8_t 			glsl_ver;
  uint8_t 			gl_vendor;
};

// TODO write editor of serialized data, to write technique impl structs.

#endif // TECHNIQUE_H
