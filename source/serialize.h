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
#ifndef __SERIALIZE_H__
#define __SERIALIZE_H__

#include <stdint.h>
#include <string.h>
#include <malloc.h>

/**
 * dna - struct of host machine info(byte endian, cpu arch)
 * 
 *                                               |                    total_size                           |
 * |dna      |total_size|base_data_size|po_count |ptr_offset           |base_data     |data_from_ptrs      |
 * |2char(1) |uint64(8) |uint32(4)     |ushort(2)|uint64(8*3*ptr_count)|base_data_size|sum(ptr_offset[n+3])|	64bit
 * |2char(1) |uint32(4) |uint32(4)     |ushort(2)|uint32(4*3*ptr_count)|base_data_size|sum(ptr_offset[n+3])|	32bit
 * 
 * some_ptr_offset[] = {
 *   ptr->aptr, 40, sizeof(ptr->aptr)
 *   ptr->bptr, 72, sizeof(ptr->bptr)
 * }
 */

enum meta_offset {
  MO_DNA = 0,
  MO_TOTAL_SIZE = 2,
  MO_BDATA_SIZE = 2+sizeof(uint32_t),
  MO_PO_COUNT = 2+sizeof(uint32_t)*2,
  MO_PTR_OFFSET = 2+sizeof(uint32_t)*2+2,
  MO_BDATA_SIZE_64 = 2+sizeof(uint64_t),
  MO_PO_COUNT_64 = 2+sizeof(uint64_t)*2,
  MO_PTR_OFFSET_64 = 2+sizeof(uint64_t)*2+2
};

struct ptr_offset_32 {
//   uint32_t ptr;
  uint32_t offset;
  uint32_t sdata_offset;//fuck incapsulation
  uint32_t size;
};
struct ptr_offset_64 {
  uint64_t ptr;
  uint64_t offset;
  uint64_t sdata_offset;
  uint64_t size;
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

struct meta {
  uint32_t type_id;
  uint32_t type_size;
  //ptrs
  struct ptr_offset_32* ptrs;
};

/**
 * base C type ids
 *   not C type -- 0
 *   void*      -- 1
 *   char 	-- 2
 *   int8 	-- 3
 *   int16 	-- 4
 *   int32 	-- 5
 *   int64 	-- 6
 *   float 	-- 7
 *   double 	-- 8
 */

#define num_types 9

static struct meta* smetas[num_types];

//це не баг, це фіча
struct meta* smeta_init(uint32_t _type_id, uint32_t _type_size);

void* serialize(void* _data, uint32_t _data_size, struct dna* _dna, uint32_t _po_len);
void* deserialize(void* _sdata);

#endif /* __SERIALIZE_H__ */
