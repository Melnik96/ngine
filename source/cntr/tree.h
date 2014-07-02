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

/* inclusion guard */
#ifndef __TREE_H__
#define __TREE_H__

#include <stdlib.h>
#include <stdint.h>

struct tree {
  struct tree* parent;
  struct tree* next;
  struct tree* childs;
};

struct tree* 	tree_get_head(struct tree* _node);
uint32_t        tree_num_parents(struct tree* _node);
void 		tree_for_each(struct tree* _node, void(*_fun)(void* _node));
void 		tree_for_each2(struct tree* _node, void(*_fun)(void* _node, void* _arg), void* _arg);
void 		tree_for_each3(struct tree* _node, void(*_fun)(void* _node, void* _arg1, void* _arg2), void* _arg1, void* _arg2);
int 		tree_add_child(struct tree* _self, struct tree* _child);

#endif /* __TREE_H__ */
