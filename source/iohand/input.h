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

#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>

#include "cntr/array.h"

struct ngine_input_mouse_move_callback {
  void* args;
  void(*callback)(void* args, double, double);
};

struct ngine_input_key_callback {
  uint32_t key;
  char pressed;
  void* args;
  void(*callback)(void* args);
};

struct ngine_input {
  struct ngine_window* 			window;
  
  struct ngine_input_mouse_move_callback* mouse_move_callback;
  
  uint32_t 				alloc_key_callbacks;
  uint32_t 				num_key_callbacks;
  struct ngine_input_key_callback* 	key_callbacks;
};

struct ngine_input* 	ngine_input_create(struct ngine_window* _win);
void 			ngine_input_bind_key(struct ngine_input* _self, uint32_t _key, char _pressed, void* _args, void(*_callback)(void*));
void 			ngine_input_unbind_key(struct ngine_input* _self, uint32_t _key, char _pressed);
void 			ngine_input_bind_mouse_btn(struct ngine_input* _self, uint32_t _btn, char _pressed, void* _args, void(*_callback)(void*));
void 			ngine_input_unbind_mouse_btn(struct ngine_input* _self, uint32_t _btn, char _pressed);
void 			ngine_input_bind_mouse_move(struct ngine_input* _self, void* _args, void(*_callback)(void*, double, double));
void 			ngine_input_unbind_mouse_move(struct ngine_input* _self);
// void 			ngine_input_push_key_bind(struct ngine_input* _self, uint32_t _key, char _pressed, void* _args, void(*_callback)(void*));
// void 			ngine_input_pop_key_bind(struct ngine_input* _self, uint32_t _key, char _pressed);

#endif // INPUT_H
