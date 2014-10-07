/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2014  <copyright holder> <email>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * 
 */

#ifndef SC_NODE_PHYS_H
#define SC_NODE_PHYS_H

#include "scenegraph/sc_node.h"

struct ngine_sc_node_phys {
  struct ngine_sc_node 	base_sc_node;
  float 		mass;
};

void 			ngine_sc_node_make_dynamic(struct ngine_sc_node* _self, struct ngine_phys_info* _phys);
void 			ngine_sc_node_set_lin_vel(struct ngine_sc_node* _self, vec3* _vel, int _relative);
// void 			ngine_sc_node_phys_activate(struct ngine_sc_node* _self, char _active);

#endif // SC_NODE_PHYS_H
