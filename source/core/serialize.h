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


#ifndef __SERIALIZE_H__
#define __SERIALIZE_H__

#include <stdint.h>
#include <stddef.h>

#define serialize(obj_ptr, struct_name, mod) struct_name##_##mod##_serializer(obj_ptr, NULL)
#define deserialize(buf, type, mod) type##_##mod##_deserializer(buf, 0)

struct buffer {
  char* data;
  size_t size;
};

struct sbuffer* serial_begin_write();
void 		serial_append(struct sbuffer* sbuf, size_t size); // add size
void 		serial_add_ptr(struct sbuffer* sbuf, void* _ptr);
inline void 	serial_write_int8(struct sbuffer* sbuf, int8_t _attr);
inline void 	serial_write_int16(struct sbuffer* sbuf, int16_t _attr);
inline void 	serial_write_int32(struct sbuffer* sbuf, int32_t _attr);
inline void 	serial_write_int64(struct sbuffer* sbuf, int64_t _attr);
inline void 	serial_write_ptr(struct sbuffer* sbuf, void* _attr); // netx write val
struct buffer* 	serial_end_write(struct sbuffer* sbuf);

struct dsbuffer*  serial_begin_read(void* _buf);
inline void 	serial_read_push(struct dsbuffer* dsbuf);
inline void 	serial_read_pop(struct dsbuffer* dsbuf);
inline int8_t 	serial_read_int8(struct dsbuffer* dsbuf);
inline int16_t 	serial_read_int16(struct dsbuffer* dsbuf);
inline int32_t 	serial_read_int32(struct dsbuffer* dsbuf);
inline int64_t 	serial_read_int64(struct dsbuffer* dsbuf);
// return ptr(current position) in buffer
inline void* 	serial_read_ptr(struct dsbuffer* dsbuf);
char* 		serial_end_read();
///void 		serial_read_ptroff(struct sbuffer* sbuf); // in the end


// 
// 
// 
// serializer must write sdate withiut pad
// 
// 
// 

#define sfunc_def(type, mod) 	struct buffer* type##_##mod##_serializer(struct type* s, struct sbuffer* sbuf)
#define dsfunc_def(type, mod) 	struct type* type##_##mod##_deserializer(char* buf, struct dsbuffer* _dsbuf)

#define sfunc_begin(type, mod) \
  struct buffer* type##_##mod##_serializer(struct type* s, struct sbuffer* _sbuf) { \
    struct sbuffer* sbuf = _sbuf; \
    if(!sbuf) { sbuf = serial_begin_write(); } \
    serial_append(sbuf, sizeof(struct type)); \
    serial_add_ptr(sbuf, s);

// TODO __typeof ...
#define sattr(attr, type) serial_write_##type(sbuf, s->attr);

// it also can be used with structs(without pointers)
#define sattrptr(attr, type) \
  serial_write_ptr(sbuf, s->attr); \
  serial_add_ptr(sbuf, s->attr) \
  serial_write_##type(sbuf, *s->attr);

#define sattrstruct(attr, type, mod) \
  serial_write_ptr(sbuf, s->attr); \
  type##_##mod##_serializer(s->attr, sbuf);

#define sfunc_end \
    if(!_sbuf) { return serial_end_write(sbuf); } \
  }

#define dsfunc_begin(type, mod) \
  struct type* type##_##mod##_deserializer(char* buf, struct dsbuffer* _dsbuf) { \
    struct dsbuffer* dsbuf = _dsbuf; \
    if(!dsbuf) { dsbuf = serial_begin_read(buf); } /*else { dsbuf->cur_ptr = buf; }*/ \
    struct type* ds = calloc(1, sizeof(struct type));

#define dsattr(attr, type) \
  ds->attr = serial_read_##type(dsbuf);

#define dsattrptr(attr, type) \
  ds->attr = serial_read_ptr(dsbuf); \
//   s->attr = seral_read_##type(dsbuf);

#define dsattrstruct(attr, type, mod) \
  void* ptr = serial_read_ptr(dsbuf); \
  serial_read_push(dsbuf); \
  ds->attr = type##_##mod##_deserializer(ptr, dsbuf); \
  serial_read_pop(dsbuf);

#define dsfunc_end \
    return ds; \
  }

#endif /* __SERIALIZE_H__ */
