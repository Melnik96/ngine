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

struct tree* tree_get_head(struct tree* _node) {
  while(1) {
    if(_node->parent == NULL) {
      return _node;
    } else {
      _node = _node->parent;
    }
  }
}

uint32_t tree_num_parents(struct tree* _node) {
  uint32_t num = 0;
  while(1) {
    if(_node->parent == NULL) {
      return num;
    } else {
      num +=1;
      _node = _node->parent;
    }
  }
}

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

void tree_for_each2(struct tree* _node, void(*_fun)(void* _node, void* _arg), void* _arg) {
  _fun((void*)_node, _arg);
  if(_node->childs != NULL) {
    tree_for_each2(_node->childs, _fun, _arg);
  } 
  else if(_node->next != NULL) {
    tree_for_each2(_node->next, _fun, _arg);
  }
  else if(_node->parent != NULL && _node->parent->next != NULL) {
    tree_for_each2(_node->parent->next, _fun, _arg);
  }
}

void tree_for_each3(struct tree* _node, void(*_fun)(void* _node, void* _arg1, void* _arg2), void* _arg1, void* _arg2) {
  _fun((void*)_node, _arg1, _arg2);
  if(_node->childs != NULL) {
    tree_for_each3(_node->childs, _fun, _arg1, _arg2);
  } 
  else if(_node->next != NULL) {
    tree_for_each3(_node->next, _fun, _arg1, _arg2);
  }
  else if(_node->parent != NULL && _node->parent->next != NULL) {
    tree_for_each3(_node->parent->next, _fun, _arg1, _arg2);
  }
}

// #define tree_for_each(_node, _fun) \
//   while(1) {\
//     _fun((void*)_node);\
//     if(_node->childs != NULL) {\
//       _node = _node->childs;\
//       continue;\
//     } \
//     else if(_node->next != NULL) {\
//       _node = _node->next;\
//       continue;\
//     }\
//     else if(_node->parent != NULL && _node->parent->next != NULL) {\
//       _node = _node->parent->next;\
//       continue;\
//     }\
//   }

int tree_add_child(struct tree* _self, struct tree* _child) {
  if(_self->childs == 0) {
    _self->childs = _child;
    _child->parent = _self;
  } else {
    tree_add_child2(_self->childs, _child);
  }
}

int tree_add_child2(struct tree* _self, struct tree* _child) {
  if(_self->next == 0) {
    _self->next = _child;
    _child->parent = _self->parent;
  } else {
    tree_add_child2(_self->next, _child);
  }
}
