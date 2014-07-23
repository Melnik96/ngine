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

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>

struct ngine_framebuffer {
  uint32_t 		id;
  uint32_t 		num_draw_texs;
  struct ngine_texture* draw_texs;
  struct ngine_texture* depth_tex;
};

struct ngine_framebuffer* 	ngine_framebuffer_create(char _create_depth, uint32_t _num_texs, int _intern_format, uint32_t _format, uint32_t _type, uint32_t _w, uint32_t _h);
void 				ngine_framebuffer_bind_draw(struct ngine_framebuffer* _self);
void 				ngine_framebuffer_bind_read(struct ngine_framebuffer* _self, struct ngine_shdr_prog* _shdr);

#endif // FRAMEBUFFER_H
