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

#include <malloc.h>
#include <memory.h>
#include <pthread.h>
#include <GLFW/glfw3.h>

#include "iohand/window.h"

#include "input.h"

void win_key_cb(struct ngine_input* _input, uint32_t _key, char pressed);
// void mouse_move(struct ngine_input* _input, struct ngine_window* win, double _x, double _y);

struct ngine_input* ngine_input_create(struct ngine_window* _win) {
  struct ngine_input* new_input = calloc(1, sizeof(struct ngine_input));
  new_input->window = _win;
  new_input->window->input_listener->user_data = new_input;
  new_input->window->input_listener->key_cb = win_key_cb;
//   new_input->window->input_listener->on_mouse_move = mouse_move;
  
  return new_input;
}

void ngine_input_update(struct ngine_input* _win) {
  glfwPollEvents();
}

void input_update_thr(struct ngine_input* _input) {
  while(1) {
    ngine_input_update(_input);
    usleep(1000000/100);
  }
}

void ngine_input_start(struct ngine_input* _win) {
  pthread_t render_front_thr;
  pthread_create(&render_front_thr, 0, input_update_thr, _win);
}

// TODO!!! key states array[]
void ngine_input_bind_key(struct ngine_input* _self, uint32_t* _keys, uint32_t _num_keys, void* _args, key_cb_t _key_pressed, key_cb_t _key_relassed) {
  if(_self->num_key_binds == _self->alloc_key_binds) {
    _self->key_binds = realloc(_self->key_binds, sizeof(struct ngine_input_key_binding)*(_self->num_key_binds+1));
  }
//   _self->key_binds[_self->num_key_binds].keys = _keys;
  _self->key_binds[_self->num_key_binds].keys = malloc(_num_keys*sizeof(uint32_t));
  memcpy(_self->key_binds[_self->num_key_binds].keys, _keys, _num_keys*sizeof(uint32_t));
  _self->key_binds[_self->num_key_binds].num_keys = _num_keys;
  _self->key_binds[_self->num_key_binds].args = _args;
  _self->key_binds[_self->num_key_binds].key_pressed_cb = _key_pressed;
  _self->key_binds[_self->num_key_binds].key_relased_cb = _key_relassed;
  
  _self->num_key_binds++;
  _self->alloc_key_binds++;
}

void ngine_input_unbind_key(struct ngine_input* _self, uint32_t* _key) {
  
}


// intern
void win_key_cb(struct ngine_input* _input, uint32_t _key, char pressed) {
  for(int i = 0; i != _input->num_key_binds; ++i) {
    for(int i2 = 0; i2 != _input->key_binds[i].num_keys; ++i2) {
      if(_input->key_binds[i].keys[i2] == _key) {
	if(pressed) {
	  if(_input->key_binds[i].key_pressed_cb) {
	    _input->key_binds[i].key_pressed_cb(_input->key_binds[i].args, _key);
	  }
	} else {
	  if(_input->key_binds[i].key_relased_cb) {
	    _input->key_binds[i].key_relased_cb(_input->key_binds[i].args, _key);
	  }
	}
	break;
      }
    }
  }
}
