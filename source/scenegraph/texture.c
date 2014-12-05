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

#include <GL/glew.h>
/*
#include "assets_mgr.h"
#include "iofile.h"
#include "import/targa/tga.h"

#include "texture.h"
#include "ngine.h"

struct ngine_texture* ngine_texture_create(const char* _name) {
  struct ngine_texture* new_tex = calloc(1, sizeof(struct ngine_texture));
  ngine_texture_init(new_tex, _name);
  
  return new_tex;
}

void ngine_texture_init(struct ngine_texture* _self, const char* _name) {
  _self->name = _name;
  
  glGenTextures(1, &_self->id);
}

void ngine_texture_empty(struct ngine_texture* _self, uint32_t _filter, int32_t _intern_format, uint32_t _format, uint32_t _type, uint32_t _w, uint32_t _h) {
  glBindTexture(GL_TEXTURE_2D, _self->id);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _filter);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _filter);
  
  if(_w != 0 && _h != 0) {
    glTexImage2D(GL_TEXTURE_2D, 0, _intern_format, _w, _h, 0, _format, _type, NULL);
  }
}

void ngine_texture_image(struct ngine_texture* _self, const char* _img_name) {
//   ngine_assets_mgr_get_file(, NGINE_IMAGE_ASSET);
  printf("load texture '%s' ", _img_name);
  tga_header tga_header;
  uint32_t img_data_off = 0;
  void* img_data = 0;
  char* tga_buf = file_rdbufp(_img_name);
  
  tga_read(tga_buf, &tga_header, &img_data_off);
  img_data = &tga_buf[img_data_off];
  
  // create and enable a texture in GL
//   glGenTextures(1, &_self->id);
  glBindTexture(GL_TEXTURE_2D, _self->id);
  printf("%i\n", _self->id);

  // set filtering types - coming up after the break!
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  // copy loaded texture in hardware
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, tga_header.width, tga_header.height, 0, GL_RGB,
	       GL_UNSIGNED_BYTE, img_data);
  free(tga_buf);
  
//   ngine_intense()->num_textures += 1;

//   // map texture into shader variable
//   glUseProgram(shaderProgHandle);
//   int texLocation = glGetUniformLocation(shaderProgHandle, "tex");
}*/
