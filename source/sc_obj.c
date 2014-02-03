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
#include <math.h>

#include "engine.h"

#include "sc_obj.h"

# define M_PI		3.14159265358979323846	/* pi */

#define deg2rad(x) (float)(((x) * M_PI / 180.0f))
#define rad2deg(x) (float)(((x) * 180.0f / M_PI))

struct sc_obj* sc_obj_create(struct engine* _eng, char* _name, char* _type) {
  struct sc_obj* new_obj = malloc(sizeof(struct sc_obj));
  memset(new_obj, 0, sizeof(struct sc_obj));
  strcpy(new_obj->name, _name);
  strcpy(new_obj->type, _type);
  new_obj->engine = _eng;
  new_obj->updated = 1;
  
  return new_obj;
}
