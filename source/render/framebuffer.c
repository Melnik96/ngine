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

#include "texture.h"
#include "shader_prog.h"

#include "framebuffer.h"

struct ngine_framebuffer* ngine_framebuffer_create(char _create_depth, uint32_t _num_texs, int _intern_format, uint32_t _format, uint32_t _type, uint32_t _w, uint32_t _h) {
  struct ngine_framebuffer* new_fbuf = calloc(1, sizeof(struct ngine_framebuffer));
  
  glGenFramebuffers(1, &new_fbuf->id);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, new_fbuf->id);

  if(_create_depth) {
    new_fbuf->depth_tex = ngine_texture_create(0);
    ngine_texture_empty(new_fbuf->depth_tex, GL_NEAREST, GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT, _w, _h);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, new_fbuf->depth_tex->id, 0);
  }
  
  new_fbuf->num_draw_texs = _num_texs;
  new_fbuf->draw_texs = calloc(_num_texs, sizeof(struct ngine_texture));
  
  uint32_t draw_bufs[_num_texs]; 
  
  for(uint32_t i = 0 ; i != _num_texs ; ++i) {
    ngine_texture_init(&new_fbuf->draw_texs[i], 0);
    ngine_texture_empty(&new_fbuf->draw_texs[i], GL_NEAREST, _intern_format, _format, _type, _w, _h);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, new_fbuf->draw_texs[i].id, 0);
    draw_bufs[i] = GL_COLOR_ATTACHMENT0 + i;
  }
  
  glDrawBuffers(_num_texs, draw_bufs);

  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
  
  GLenum fb_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if(fb_status != GL_FRAMEBUFFER_COMPLETE) {
    error("FB error, status: 0x%x\n", fb_status);
    return 0;
  }
  
  return new_fbuf;
}

void ngine_framebuffer_bind_draw(struct ngine_framebuffer* _self) {
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _self->id);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ngine_framebuffer_bind_read(struct ngine_framebuffer* _self, struct ngine_shdr_prog* _shdr) {
  glBindFramebuffer(GL_READ_FRAMEBUFFER, _self->id);
  for(uint32_t i = 0 ; i != _self->num_draw_texs; ++i) {
    glActiveTexture(GL_TEXTURE0 + _self->draw_texs[i].id);
    glBindTexture(GL_TEXTURE_2D, _self->draw_texs[i].id);
    glUniform1i(_shdr->uniform_locs[NGINE_UNIFORM_GTEX0+i], _self->draw_texs[i].id);
  }
}

