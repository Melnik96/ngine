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

#include "../window.h"

#include "input.h"
#include "ngine.h"

void key_pressed(struct ngine_input* _input, uint32_t _key);
void key_relased(struct ngine_input* _input, uint32_t _key);
void mouse_move(struct ngine_input* _input, double _x, double _y);

struct ngine_input* ngine_input_create(struct ngine_window* _win) {
  struct ngine_input* new_input = calloc(1, sizeof(struct ngine_input));
  new_input->window = _win;
  new_input->window->input_listener->on_key_pressed = key_pressed;
  new_input->window->input_listener->on_key_relased = key_relased;
  new_input->window->input_listener->on_mouse_move = mouse_move;
  new_input->window->input_listener->user_data = new_input;
  return new_input;
}

// TODO!!! key states array[]
void ngine_input_bind_key(struct ngine_input* _self, uint32_t _key, char _pressed, void* _args, void(*_callback)(void*)) {
  if(_self->num_key_callbacks == _self->alloc_key_callbacks) {
    _self->key_callbacks = realloc(_self->key_callbacks, sizeof(struct ngine_input_key_callback)*(_self->num_key_callbacks+1));
  }
  _self->key_callbacks[_self->num_key_callbacks].key = _key;
  _self->key_callbacks[_self->num_key_callbacks].pressed = _pressed;
  _self->key_callbacks[_self->num_key_callbacks].args = _args;
  _self->key_callbacks[_self->num_key_callbacks].callback = _callback;
  
  _self->num_key_callbacks++;
  _self->alloc_key_callbacks++;
}

void ngine_input_unbind_key(struct ngine_input* _self, uint32_t _key, char _pressed) {
  
}

void ngine_input_bind_mouse_move(struct ngine_input* _self, void* _args, void(*_callback)(void*, double, double)) {
  if(!_self->mouse_move_callback) {
    _self->mouse_move_callback = malloc(sizeof(struct ngine_input_mouse_move_callback));
  }
  _self->mouse_move_callback->args = _args;
  _self->mouse_move_callback->callback = _callback;
}


// intern
void key_pressed(struct ngine_input* _input, uint32_t _key) {
  struct ngine_input_key_callback* pos;
  for(pos = _input->key_callbacks; pos < &_input->key_callbacks[_input->num_key_callbacks]; pos++) {
    if(pos->key == _key && pos->pressed == 1) {
      pos->callback(pos->args);
      break;
    }
  }
}
void key_relased(struct ngine_input* _input, uint32_t _key) {
  struct ngine_input_key_callback* pos;
  for(pos = _input->key_callbacks; pos < &_input->key_callbacks[_input->num_key_callbacks]; ++pos) {
    if(pos->key == _key && pos->pressed == 0) {
      pos->callback(pos->args);
    }
  }
}
void mouse_move(struct ngine_input* _input, double _x, double _y) {
  if(_input->mouse_move_callback) {
    _input->mouse_move_callback->callback(_input->mouse_move_callback->args, _x, _y);
  }
}
