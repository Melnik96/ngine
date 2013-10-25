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
#ifndef __SERIALIZATION_H__
#define __SERIALIZATION_H__

#include <string.h>
#include <malloc.h>
#include <stdint.h>

/**
 * |total_size|po_count|ptr_offset|base_data_size|base_data|data_from_ptrs|
 * some_ptr_offset[] = {
 *   ptr->aptr, 40, sizeof(ptr->aptr)
 *   ptr->bptr, 72, sizeof(ptr->bptr)
 * }
 */

struct sdna {
  uint32_t total_size;
  uint32_t po_len;
  uint32_t base_data_size;
  uint32_t* ptr_offset;
  void* base_data;
  void* data_from_ptrs;
};

void* serialize(void* _data, uint32_t _data_size, uint32_t* _ptr_offset, uint32_t _po_len);
void* deserialize(void* _sdata);

#endif /* __SERIALIZATION_H__ */
