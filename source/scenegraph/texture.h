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

#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdint.h>

struct ngine_texture {
  char* name;// NULL == "unamed"
  uint16_t id;
  uint16_t width;
  uint16_t height;
  uint16_t cspace;// GL_RGBA
};

struct ngine_texture* 	ngine_texture_create(const char* _name);
void 			ngine_texture_init(struct ngine_texture* _self, const char* _name);
void 			ngine_texture_delete(struct ngine_texture* _self);
void 			ngine_texture_image(struct ngine_texture* _self, const char* _img_name);
void 			ngine_texture_empty(struct ngine_texture* _self, uint32_t _filter, int32_t _intern_format, uint32_t _format, uint32_t _type, uint32_t _w, uint32_t _h);
void 			ngine_texture_target(struct ngine_sc_node* _camera);

#endif // TEXTURE_H
