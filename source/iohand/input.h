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

#include "core/array.h"

typedef void(*key_cb_t)(void* _args, int _key);

struct ngine_input_key_binding {
  uint32_t 	num_keys;
  uint32_t* 	keys;
  void* 	args;
  key_cb_t 	key_pressed_cb;
  key_cb_t 	key_relased_cb;
};

struct ngine_input {
  struct ngine_window* 			window;
  
  struct ngine_input_mouse_move_callback* mouse_move_cb;
  
  uint32_t 				alloc_key_binds;
  uint32_t 				num_key_binds;
  struct ngine_input_key_binding* 	key_binds;
};

struct ngine_input* 	ngine_input_create(struct ngine_window* _win);
void 			ngine_input_delete(struct ngine_input* _win);
void 			ngine_input_update(struct ngine_input* _win);
void 			ngine_input_start(struct ngine_input* _win);
// push pop LILO calls concept
void 			ngine_input_bind_key(struct ngine_input* _self, uint32_t* _keys, uint32_t _num_keys, void* _args, key_cb_t _key_pressed, key_cb_t _key_relassed);
void 			ngine_input_unbind_key(struct ngine_input* _self, uint32_t* _keys);

void 			ngine_input_bind_mouse_btn(struct ngine_input* _self, uint32_t _btn, char _pressed, void* _args, void(*_callback)(void*));
void 			ngine_input_unbind_mouse_btn(struct ngine_input* _self, uint32_t _btn, char _pressed);
void 			ngine_input_bind_mouse_move(struct ngine_input* _self, void* _args, void(*_callback)(struct ngine_window*, void*, double, double));
void 			ngine_input_unbind_mouse_move(struct ngine_input* _self);

#endif // INPUT_H
