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

#include "sc_obj.h"
#include "entity.h"
#include "mesh.h"
#include "material.h"

#include "button.h"

void button_gen(struct sc_obj* obj) {
  struct mesh* btn_mesh = malloc(sizeof(struct mesh));
  btn_mesh->vertices = {-1.f,  1.f, 0.f,
			 1.f,  1.f, 0.f,
			-1.f, -1.f, 0.f,
			 1.f, -1.f, 0.f};
  btn_mesh->indices =  {0,1,2,
			1,2,3};

  struct material* btn_material = malloc(sizeof(struct material));
  btn_material->difuse_color = {0.f, 1.f, 0.f};
  btn_material->textures = NULL;

  obj->typed_objs = entity_create("gui button", button_mesh, );
}
