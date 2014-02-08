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

enum gl_shader_types {
  GLST_VERTEX = 0,
  GLST_GEOMETRY = 1,
  GLST_FRAGMENT = 2
};

enum gl_shader_attribs {
  GLSA_VERTEX = 0,
  GLSA_UV = 1,
  GLSA_NORMAL = 3
//   GLSA_
};

enum gl_shader_uniforms {
  GLSU_MVP = 0
};

struct shader_source {
  char* vertex;
  char* geometry;
  char* fragment;
};

struct shader_param {
  char     name[32];
  uint32_t id;
};

struct shader_prog {
  char 			name[32];
  uint32_t 		id;
  struct shader_param* 	uniforms;
  struct shader_param* 	attribs;
};

int 			shader_prog_init(struct shader_prog* _prog, const char* _name, struct shader_source* _sources);
struct shader_prog* 	shader_prog_create(const char* _name, struct shader_source* _sources);
int	 		shader_prog_delete(struct shader_prog* _prog);
int 			shader_prog_param(struct shader_prog* _prog, const char* _par_name);
int 			shader_prog_params(struct shader_prog* _prog, const char** _params);

#endif // SHADER_PROG_H
