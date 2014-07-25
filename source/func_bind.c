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

#include "func_bind.h"

struct ngine_func_bind* ngine_func_bind(void* _func, uint8_t _num_args, void* _args) {
  struct ngine_func_bind* new_bind = malloc(sizeof(struct ngine_func_bind*));
  
  new_bind->func = _func;
  new_bind->num_args = _num_args;
//   new_bind->args = malloc();
}

void* ngine_func_call(struct ngine_func_bind* _self) {

}
