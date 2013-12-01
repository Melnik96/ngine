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

#include "tree.h"

void tree_for_each(struct tree* _node, void(*_fun)(void* _node)) {
  _fun((void*)_node);
  if(_node->childs != NULL) {
    tree_for_each(_node->childs, _fun);
  } 
  else if(_node->next != NULL) {
    tree_for_each(_node->next, _fun);
  }
  else if(_node->parent != NULL && _node->parent->next != NULL) {
      tree_for_each(_node->parent->next, _fun);
  }
}

int tree_add_child(struct tree* _self, struct tree* _child) {
  if(_self->childs == 0) {
    _self->childs = _child;
  } else {
    tree_add_child2(_self->childs, _child);
  }
}

int tree_add_child2(struct tree* _self, struct tree* _child) {
  if(_self->next == 0) {
    _self->next = _child;
  } else {
    tree_add_child(_self->next, _child);
  }
}
