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

#include "serialize.h"

struct ptr_offset* check_ptr_in_po(size_t _ptr_num, struct ptr_offset* _ptr_os, void* _ptr) {
  for(size_t i = 0; i < _ptr_num; ++i) {
    if(_ptr_os[i].ptr == _ptr) { return &_ptr_os[i]; }
  }
  return 0;
}

void* find_ptr_in_array(size_t _num_ptrs, void** _ptrs, void* _ptr) {
  for(size_t i = 0; i < _num_ptrs; ++i) {
    if(_ptrs[i] == _ptr) { return _ptr; }
  }
  return NULL;
}
