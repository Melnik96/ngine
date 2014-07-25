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

#include <math.h>

#include "math/vector.h"

#include "light.h"

float calc_plight_rad(vec3 _color, float _intensity);

struct ngine_light* ngine_light_create(uint32_t _type) {
  struct ngine_light* new_light = calloc(1, sizeof(struct ngine_light));
  
  new_light->type = _type;
  new_light->ambient = (vec3){11.,11.,11.};
  
  new_light->need_update = 1;
  
  return new_light;
}

void ngine_light_delete(struct ngine_light* _self) {

}

inline void ngine_light_update(struct ngine_light* _self) {
  if(_self->need_update) {
    if(_self->type == NGINE_LIGHT_POINT) {
      _self->radius = 1.0/*calc_plight_rad(_self->diffuse, _intensity)*/;
    }
  }
}

float calc_plight_rad(vec3 _color, float _intensity) {
    float MaxChannel = fmax(fmax(_color.x, _color.y), _color.z);
    float c = MaxChannel * _intensity;
    return (8.0f * sqrt(c) + 1.0f);
}