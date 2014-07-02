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

#include "node.h"

int node_create(struct node* _self, char* _type, uint8_t _num_in, uint8_t _num_out, int(*_handler)(struct node*)) {
  if(_self == 0) { return 0; }
  
  if(_type!=0) { strcpy(_self->type, _type); }
  if(_num_in!=0) { _self->inputs = malloc(_num_in*sizeof(struct socket)); }
  if(_num_out!=0) { _self->outputs = malloc(_num_in*sizeof(struct socket)); }
  if(_handler!=0) { _self->process = _handler; }
  return 1;
}
struct socket* node_get_sock_by_name(struct node* _self, char* _name, enum sock_type _sctype) {
//   struct socket* cur_sock;
//   while(1) {
//     _self->inputs->
//     if(_self->inputs->name == _name) {
//       return cur_sock;
//     }
//   }
}

void node_process(struct node* _self, void* _args) {
  if(_args) {
    _self->process(_args);
  } else {
    _self->process(_self->inputs->value);
  }
}
