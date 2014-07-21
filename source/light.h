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

#ifndef LIGHT_H
#define LIGHT_H

#include "math/vector.h"

enum ngine_light_type {
  NGINE_LIGHT_POINT = 0,
  NGINE_LIGHT_SPOT
};

struct ngine_light {
  uint32_t type;
  
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  vec3 attenuation[3];

  float intensity;
};

// todo antilight -rgb

#endif // LIGHT_H
