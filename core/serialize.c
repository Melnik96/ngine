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
#include <memory.h>

#include "serialize.h"

// struct ptr_offset* check_ptr_in_po(size_t _ptr_num, struct ptr_offset* _ptr_os, void* _ptr) {
//   for(size_t i = 0; i < _ptr_num; ++i) {
//     printf("check_ptr_in_po %x,  %x\n", _ptr_os[i].ptr, _ptr);
//     if(_ptr_os[i].ptr == _ptr) { return &_ptr_os[i]; }
//   }
//   return 0;
// }

struct sbuffer {
  char* 	cur_ptr;
  size_t 	cur_offset;
  
  void** 	ptrs;
  uint32_t* 	offsets;
  uint8_t 	num_ptrs;
  
  struct buffer* buf;
};

struct sbuffer* serial_begin_write() {
  struct sbuffer* sbuf = calloc(1, sizeof(struct sbuffer));
  sbuf->buf = calloc(1, sizeof(struct buffer));
  
  // write 4 offset bytes
  serial_append(sbuf, sizeof(int32_t)+sizeof(int8_t));
  serial_write_int32(sbuf, 0);
  serial_write_int8(sbuf, 0);
  
  return sbuf;
}

void serial_append(struct sbuffer* sbuf, size_t size) {
  uint32_t real_size = sbuf->cur_ptr - sbuf->buf->data;
  sbuf->buf->data = realloc(sbuf->buf->data, real_size + size);
  sbuf->cur_ptr = sbuf->buf->data + real_size;
  
  sbuf->buf->size = real_size + size;
}

void serial_add_ptr(struct sbuffer* sbuf, void* _ptr) {
  sbuf->ptrs = realloc(sbuf->ptrs, sizeof(void*)*(sbuf->num_ptrs+1));
  sbuf->offsets = realloc(sbuf->ptrs, sizeof(uint32_t)*(sbuf->num_ptrs+1));
  sbuf->ptrs[sbuf->num_ptrs] = _ptr;
  sbuf->offsets[sbuf->num_ptrs] = sbuf->cur_ptr - sbuf->buf->data;
  
  sbuf->num_ptrs += 1;
}

void serial_write_ptr(struct sbuffer* sbuf, void* _attr) {
  *((uint8_t*)sbuf->cur_ptr) = sbuf->num_ptrs;
  sbuf->cur_ptr += sizeof(int8_t);
}

void serial_write_int8(struct sbuffer* sbuf, int8_t _attr) {
  *((int8_t*)sbuf->cur_ptr) = _attr;
  sbuf->cur_ptr += sizeof(int8_t);
}

void serial_write_int32(struct sbuffer* sbuf, int32_t _attr) {
  *((int32_t*)sbuf->cur_ptr) = _attr;
  sbuf->cur_ptr += sizeof(int32_t);
}

void serial_write_int64(struct sbuffer* sbuf, int64_t _attr) {
  *((int64_t*)sbuf->cur_ptr) = _attr;
  sbuf->cur_ptr += sizeof(int64_t);
}

struct buffer* serial_end_write(struct sbuffer* sbuf) {
  struct buffer* buf = sbuf->buf;
  
  size_t ptros_size = sizeof(uint32_t)*sbuf->num_ptrs;
  
  serial_append(sbuf, ptros_size);
  memcpy(sbuf->cur_ptr, sbuf->ptrs, ptros_size);
  
  *((uint32_t*)buf->data) = sbuf->cur_ptr - buf->data;
  *((uint8_t*)(buf->data+sizeof(int32_t))) = sbuf->num_ptrs;
  
  free(sbuf);
//   free(sbuf->ptrs);
  
  return buf;
}

struct dsbuffer {
  char* buf;
  
  char* back_cur_ptr;
  char* cur_ptr;
  size_t cur_offset;
  
  uint8_t num_ptrs;
  uint32_t* offsets;
};

struct dsbuffer* serial_begin_read(void* _buf) {
  struct dsbuffer* dsbuf = calloc(1, sizeof(struct dsbuffer));
  dsbuf->buf = _buf;
  
  dsbuf->offsets = dsbuf->buf + *((uint32_t*)dsbuf->buf);
  dsbuf->num_ptrs = *((uint8_t*)(dsbuf->buf+sizeof(int32_t)));
  
  dsbuf->cur_ptr = _buf + sizeof(int32_t) + sizeof(int8_t);
  
  return dsbuf;
}

void serial_read_push(struct dsbuffer* dsbuf) {
  dsbuf->back_cur_ptr = dsbuf->cur_ptr;
}

void serial_read_pop(struct dsbuffer* dsbuf) {
  dsbuf->cur_ptr = dsbuf->back_cur_ptr;
}

void* serial_read_ptr(struct dsbuffer* dsbuf) {
  uint8_t offset_id = *((uint8_t*)dsbuf->cur_ptr);
  void* val = dsbuf->buf + dsbuf->offsets[offset_id];
  dsbuf->cur_ptr += sizeof(int8_t);
  return val;
}

int8_t serial_read_int8(struct dsbuffer* dsbuf) {
  int8_t val = *((int8_t*)dsbuf->cur_ptr);
  dsbuf->cur_ptr += sizeof(int8_t);
  return val;
}

int16_t serial_read_int16(struct dsbuffer* dsbuf) {
  int16_t val = *((int16_t*)dsbuf->cur_ptr);
  dsbuf->cur_ptr += sizeof(int16_t);
  return val;
}

int32_t serial_read_int32(struct dsbuffer* dsbuf) {
  int32_t val = *((int32_t*)dsbuf->cur_ptr);
  dsbuf->cur_ptr += sizeof(int32_t);
  return val;
}

int64_t serial_read_int64(struct dsbuffer* dsbuf) {
  int64_t val = *((int64_t*)dsbuf->cur_ptr);
  dsbuf->cur_ptr += sizeof(int64_t);
  return val;
}

char* serial_end_read(struct dsbuffer* dsbuf) {
  return dsbuf->buf;
}
