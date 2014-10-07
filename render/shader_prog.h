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

#ifndef SHADER_PROG_H
#define SHADER_PROG_H

#include <stdint.h>

enum {
  NGINE_ATTR_VERTEX = 0,
  NGINE_ATTR_UV     = 1,
  NGINE_ATTR_NORMAL = 2,
//   GLSA_
};

enum {
  NGINE_UNIFORM_MVP  = 0,
  NGINE_UNIFORM_MODEL,
  NGINE_UNIFORM_VIEW,
  NGINE_UNIFORM_PROJ,
  NGINE_UNIFORM_TIME,
  NGINE_UNIFORM_TEX,
  NGINE_UNIFORM_LIGHT_DIFUSE,
  NGINE_UNIFORM_LIGHT_POS,
  NGINE_UNIFORM_RANDMAP,
  NGINE_UNIFORM_GDEPTH,
  NGINE_UNIFORM_GTEX0,
  NGINE_UNIFORM_GTEX1,
  NGINE_UNIFORM_GTEX2,
  NGINE_UNIFORM_GTEX3,
  NGINE_UNIFORM_GTEX4,
  NGINE_UNIFORM_GTEX5,
  NGINE_UNIFORM_GTEX6,
  NGINE_UNIFORM_GTEX7,
  NGINE_UNIFORMS_NUM
};

struct ngine_shdr_prog {
  char* name;
  uint32_t id;
  
  uint32_t vert_shad;
  uint32_t frag_shad;
  uint32_t tess_ctrl_shad;
  uint32_t tess_eval_shad;
  uint32_t geom_shad;
  uint32_t compute_shad;
  
  int32_t uniform_locs[NGINE_UNIFORMS_NUM];// -1 uniform not present in shader program
};

struct ngine_shdr_prog* ngine_shdr_prog_create(const char* _name);
int	 		ngine_shdr_prog_delete(struct ngine_shdr_prog* _self);
void 			ngine_shdr_prog_binary(struct ngine_shdr_prog* _self, void* _bin, uint32_t _size);// setup shader prog from binary
// void 			ngine_shdr_prog_source(struct ngine_shdr_prog* _self, uint32_t _type, const char* _source);
int	 		ngine_shdr_prog_compile(struct ngine_shdr_prog* _self, const char* _source, uint32_t _type);
void 			ngine_shdr_prog_bind_attr(struct ngine_shdr_prog* _self, uint32_t _index, const char* _name);
int32_t 		ngine_shdr_prog_get_unf_loc(struct ngine_shdr_prog* _self, const char* _name);
int 			ngine_shdr_prog_link(struct ngine_shdr_prog* _self);
struct buffer* 		ngine_shdr_prog_get_binary(struct ngine_shdr_prog* _self);

// TODO shader preprocessor

#endif // SHADER_PROG_H
