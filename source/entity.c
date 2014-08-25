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

#include <GL/glew.h>
#include <GL/gl.h>
#include <malloc.h>
#include <string.h>

#include "mesh.h"
#include "ngine.h"
#include "scene.h"
#include "shader_prog.h"

#include "entity.h"

//cool gameplay http://www.youtube.com/watch?v=4gte8ket3jk
int ngine_entity_init(struct ngine_entity* _ent, char* _name, struct ngine_mesh* _mesh) {
// //   _ent->name = NULL;
// //   _ent->mesh = NULL;
// //   _ent->material = NULL;
  strcpy(_ent->name, _name);
// //   _ent->name = _name;
  _ent->mesh = _mesh;
}

struct ngine_entity* ngine_entity_create(char* _name, struct ngine_mesh* _mesh) {
  struct ngine_entity* new_ent = calloc(1, sizeof(struct ngine_entity));
  ngine_entity_init(new_ent, _name, _mesh);
  
  return new_ent;
}
