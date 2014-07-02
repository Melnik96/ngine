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

#include "assets_mgr.h"

#include "texture.h"

struct ngine_texture* ngine_texture_create(const char* _name) {
//   ngine_assets_mgr_get_file(, NGINE_IMAGE_ASSET);
  
  // create and enable a texture in GL
  glActiveTexture(GL_TEXTURE0);
  GLuint textureId;
  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);

  // set filtering types - coming up after the break!
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  // copy loaded texture in hardware
//   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, imageData->w, imageData->h, 0, GL_RGB,
// 	       GL_UNSIGNED_BYTE, imageData->data);
//   free(imageData->data);

//   // map texture into shader variable
//   glUseProgram(shaderProgHandle);
//   int texLocation = glGetUniformLocation(shaderProgHandle, "tex");
}
