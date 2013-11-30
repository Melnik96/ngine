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

#ifndef NODE_H
#define NODE_H

#include <stdint.h>

struct node {
  char 		 type[64];
  
  struct socket* outputs;
  struct socket* inputs;
  
  int(*process)(struct node*);
};

struct socket {
  char 		name[64];
  uint8_t	num_in, num_out;
  struct node* 	node_out;
  struct node* 	node_in;
  void* 	value;
};

enum sock_type {
  ST_IN,
  ST_OUT
};

//some args can be NULL(0)
int node_create(struct node* _self, char* _type, uint8_t _num_in, uint8_t _num_out, int(*_handler)(struct node*));
struct socket* node_get_sock_by_name(struct node* _self, char* _name, enum sock_type _sctype);
#endif // NODE_H
