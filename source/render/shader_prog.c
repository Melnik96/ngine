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

#include <malloc.h>
#include <string.h>
#include <GL/glew.h>

#include "core/log.h"

#include "shader_prog.h"

struct ngine_shdr_prog* ngine_shdr_prog_create(const char* _name) {
  debug("create shader program '%s'", _name);
  
  struct ngine_shdr_prog* new_shdr_prog = calloc(1, sizeof(struct ngine_shdr_prog));
  
  new_shdr_prog->name = _name;
  new_shdr_prog->id = glCreateProgram();
  
  return new_shdr_prog;
}
int ngine_shdr_prog_delete(struct ngine_shdr_prog* _self) {
  glDeleteProgram(_self->id);
  free(_self);
}

void ngine_shdr_prog_binary(struct ngine_shdr_prog* _self, void* _bin, uint32_t _size) {
  
}

int ngine_shdr_prog_compile(struct ngine_shdr_prog* _self, const char* _source, uint32_t _type) {
  uint32_t shdr_id = glCreateShader(_type);
  
  glShaderSource(shdr_id, 1, &_source, 0);
  glCompileShader(shdr_id);
  glAttachShader(_self->id, shdr_id);
  
  int result = 0;
  
  glGetShaderiv(shdr_id, GL_COMPILE_STATUS, &result);
  
  if(!result) {
    int length = 0;
    char* err_log = NULL;
    
    glGetShaderiv(shdr_id, GL_INFO_LOG_LENGTH, &length);
    
    if(length > 0) {
      err_log = malloc(length);
      int written = 0;
      glGetShaderInfoLog(shdr_id, length, &written, err_log);
    }
    
    error("shader program '%s' compiling shader error:\n  %s", _self->name, err_log);
    
    free(err_log);
    
    glDeleteShader(shdr_id);
  }
  
  return result;
}

int ngine_shdr_prog_link(struct ngine_shdr_prog* _self) {
  debug("link shader program '%s'", _self->name);
  
  glLinkProgram(_self->id);
  
  int linked = 0;
  
  glGetProgramiv(_self->id, GL_LINK_STATUS, &linked);

  if(!linked) {
    int length = 0;
    char* err_log = NULL;
    
    glGetProgramiv(_self->id, GL_INFO_LOG_LENGTH, &length);
    
    if(length > 0) {
      err_log = malloc(length);
      int written = 0;
      glGetProgramInfoLog(_self->id, length, &written, err_log);
    }

    error("linking shader program '%s' error:\n  %s", _self->name, err_log);

    free(err_log);

    glDeleteProgram(_self->id);
  }
  
  return linked;
}

void ngine_shdr_prog_bind_attr(struct ngine_shdr_prog* _self, uint32_t _index, const char* _name) {
  glBindAttribLocation(_self->id, _index, _name);
}

int32_t ngine_shdr_prog_get_unf_loc(struct ngine_shdr_prog* _self, const char* _name) {
  int32_t u_loc = glGetUniformLocation(_self->id, _name);
  if(u_loc == -1) {
    error("shader program: get uniform '%s' failled", _name);
  }
  return u_loc;
}

// struct buffer* ngine_shdr_prog_get_binary(struct ngine_shdr_prog* _self) {
//   
// }
