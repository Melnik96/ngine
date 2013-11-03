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

#include <stdint.h>
#include <string.h>
#include <malloc.h>
#include <stdint.h>

/**
 * dna - struct of host machine info(byte endian, cpu arch)
 * 
 *                                               |                    total_size                           |
 * |dna      |total_size|base_data_size|po_count |ptr_offset           |base_data     |data_from_ptrs      |
 * |2char(2) |uint64(8) |uint64(8)     |ushort(2)|uint64(8*3*ptr_count)|base_data_size|sum(ptr_offset[n+3])|	64bit
 * |2char(2) |uint32(4) |uint32(4)     |ushort(2)|uint32(4*3*ptr_count)|base_data_size|sum(ptr_offset[n+3])|	32bit
 * 
 * some_ptr_offset[] = {
 *   ptr->aptr, 40, sizeof(ptr->aptr)
 *   ptr->bptr, 72, sizeof(ptr->bptr)
 * }
 */

struct ptr_offset {
  void* ptr;
  uint32_t offset;
  uint32_t size;
};

enum {
  ENDIAN_BIG,
  ENDIAN_LITTLE
};

enum {
  ARCH_X86,
  ARCH_X64
};

struct dna {
  char endian;
  char arch;//64bit or 32bit
};

void* serialize(void* _data, uint32_t _data_size, struct dna* _dna, struct ptr_offset* _ptr_offset, uint32_t _po_len);
void* deserialize(void* _sdata);

#endif /* __SERIALIZATION_H__ */
