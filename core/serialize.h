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
#include <string.h>
#include <malloc.h>

#define defsfun(struct_name, mod) 		struct buffer* struct_name##_##mod##_serializer(struct struct_name* s, struct ptr_offset* _ptr_os, size_t* _po_num, struct buffer* _r_buf, void* _cur_pos);\
						struct struct_name* struct_name##_##mod##_deserializer(void* sdata,struct ptr_offset* _ptr_os, size_t* _po_num, struct ptr_offset* _ptr_os_ds, size_t* _po_last_ds, int _r_ser);

#define sfunc(struct_name, mod) 		struct buffer* struct_name##_##mod##_serializer(struct struct_name* s, struct ptr_offset* _ptr_os, size_t* _po_num, struct buffer* _r_buf, void* _cur_pos) { \
                                                  int _r_ser = 0;\
						  if(!_r_buf) {	\
						    _r_ser = 1;\
						    _r_buf = malloc(sizeof(struct buffer)); \
						    _r_buf->data = malloc(sizeof(struct struct_name)); \
						    _r_buf->size = sizeof(struct struct_name); \
						    _cur_pos = _r_buf->data;\
						    \
						    _po_num = malloc(sizeof(size_t));\
						    *_po_num = 1;	\
						    _ptr_os = malloc(sizeof(struct ptr_offset));\
						    _ptr_os->ptr = s;\
						    _ptr_os->offset = 0;\
						  } else {\
						    _ptr_os = realloc(_ptr_os, (*_po_num) * sizeof(struct ptr_offset)); \
						    _ptr_os[*_po_num].ptr = s;\
						    _ptr_os[*_po_num].offset = _cur_pos - _r_buf->data;	\
						    *_po_num += 1;\
  printf("funcs sf %i", (*_po_num));\
						    \
						    void* new_data = realloc(_r_buf->data, _r_buf->size + sizeof(struct struct_name)); \
						    _cur_pos = new_data + (_cur_pos - _r_buf->data);\
						    _r_buf->data = new_data;\
						    _r_buf->size += sizeof(struct struct_name);\
						  }

#define schar(attr)				  memcpy(_cur_pos, &s->attr, sizeof(char));				_cur_pos += sizeof(char);
#define sint16(attr)				  memcpy(_cur_pos, &s->attr, sizeof(int16_t));				_cur_pos += sizeof(int16_t);
#define sint32(attr)				  memcpy(_cur_pos, &s->attr, sizeof(int32_t));				_cur_pos += sizeof(int32_t);
#define sint64(attr)				  memcpy(_cur_pos, &s->attr, sizeof(int64_t));				_cur_pos += sizeof(int64_t);
#define sfloat(attr)				  memcpy(_cur_pos, &s->attr, sizeof(float));				_cur_pos += sizeof(float);
#define sdouble(attr)				  memcpy(_cur_pos, &s->attr, sizeof(double));				_cur_pos += sizeof(double);

#define sstruct_ptr(attr, struct_name, mod)	  *((void**)_cur_pos) = s->attr;					_cur_pos += sizeof(void*);\
                                                  if(!check_ptr_in_po(*_po_num, _ptr_os, s->attr)) {\
						    struct_name##_##mod##_serializer(s->attr, _ptr_os, _po_num, _r_buf, _cur_pos); \
						  }

#define funcs 					  if(_r_ser) {\
                                                    void* new_data = realloc(_r_buf->data, _r_buf->size + sizeof(size_t) + (*_po_num) * sizeof(struct ptr_offset)); \
						    memmove(new_data + sizeof(size_t) + (*_po_num) * sizeof(struct ptr_offset), new_data, _r_buf->size);\
                                                    *((size_t*)new_data) = *_po_num; \
						    memcpy(new_data + sizeof(size_t), _ptr_os, (*_po_num) * sizeof(struct ptr_offset)); \
						    _r_buf->data = new_data; \
						    _r_buf->size += sizeof(size_t) + (*_po_num) * sizeof(struct ptr_offset); \
						  }\
						  return _r_buf;\
						}

#define dsfunc(struct_name, mod) 		struct struct_name* struct_name##_##mod##_deserializer(void* sdata,struct ptr_offset* _ptr_os, size_t* _po_num, struct ptr_offset* _ptr_os_ds, size_t* _po_last_ds, int _r_ser) { \
						  struct struct_name* dsdata = malloc(sizeof(struct struct_name));\
						  void* lnds = sdata; \
						  if(_r_ser) {\
						    if(*((size_t*)sdata) != 0) { \
                                                      _po_num = malloc(sizeof(size_t));\
						      *_po_num = *((size_t*)lnds); \
                                                      _po_last_ds = malloc(sizeof(size_t));\
						      *_po_last_ds = 0;\
						    			\
						      _ptr_os = (lnds + sizeof(size_t));\
						      _ptr_os_ds = malloc((*_po_num) * sizeof(struct ptr_offset)); \
                                                      lnds += (sizeof(size_t) + (*_po_num)*sizeof(struct ptr_offset));	\
						    } else {		\
						      lnds += sizeof(size_t);\
						    }\
						  }

#define dschar(attr)				  dsdata->attr = *(char*)lnds;						lnds += sizeof(char);
#define dsint16(attr)				  dsdata->attr = *(int16_t*)lnds;					lnds += sizeof(int16_t);
#define dsint32(attr)				  dsdata->attr = *(int32_t*)lnds;					lnds += sizeof(int32_t);
#define dsint64(attr)				  dsdata->attr = *(int64_t*)lnds;					lnds += sizeof(int64_t);
#define dsfloat(attr)				  dsdata->attr = *(float*)lnds;						lnds += sizeof(float);
#define dsdouble(attr)				  dsdata->attr = *(double*)lnds;					lnds += sizeof(double);

#define dsstruct_ptr(attr, struct_name, mod)	  struct ptr_offset* p_##attr = NULL;\
						  if(p_##attr = check_ptr_in_po(*_po_last_ds, _ptr_os_ds, *((void**)lnds))) {\
						    dsdata->attr = p_##attr->offset;						lnds += sizeof(void*); \
						  } else if(p_##attr = check_ptr_in_po(*_po_num, _ptr_os, *((void**)lnds))) {\
						    struct struct_name* dsattr_##attr = struct_name##_##mod##_deserializer((sdata + sizeof(size_t) + (*_po_num)*sizeof(struct ptr_offset) + p_##attr->offset), _ptr_os, _po_num, _ptr_os_ds, _po_last_ds, 0); \
						    dsdata->attr = dsattr_##attr; \
						    _ptr_os_ds[*_po_last_ds].ptr = p_##attr->ptr;\
						    _ptr_os_ds[*_po_last_ds].offset = dsattr_##attr;	_po_last_ds += 1;	lnds += sizeof(void*) + sizeof(struct struct_name);\
						  }

#define funcds					  return dsdata;\
						}



/**
 * uint32 		buf_size
 * byte[buf_size] 	sdata
 * ptr_offset[num_ptrs] ptr_os
 */

struct buffer {
  size_t size;
  char*  data;
};

struct ptr_offset {
  intptr_t ptr;
  intptr_t offset;
};

struct ptr_offset* check_ptr_in_po(size_t _ptr_num, struct ptr_offset* _ptr_os, void* _ptr);

struct ngine_serialize {
  struct buffer* 	buf;
  
  uint32_t 		num_ptr_os;
  struct ptr_offset* 	ptr_os;
  
  char* 		last_offset;
};

#define sfunc_def(struct_name, mod) 		struct buffer* struct_name##_##mod##_serializer(struct struct_name* s, struct ngine_serialize* _self);\
						struct struct_name* struct_name##_##mod##_deserializer(void* sdata,struct ptr_offset* _ptr_os, size_t* _po_num, struct ptr_offset* _ptr_os_ds, size_t* _po_last_ds, int _r_ser);

#define sfunc_begin(struct_name, mod) struct buffer* struct_name##_##mod##_serializer(struct struct_name* s, struct ngine_serialize* _self) {\
  char root = 0;\
  if(_self == 0) {\
    root = 1;\
    _self = malloc(sizeof(struct ngine_serialize));\
    _self->buf = malloc(sizeof(struct buffer));\
    _self->buf->size = sizeof(uint32_t)+sizeof(struct struct_name);\
    _self->buf->data = malloc(_self->buf->size);\
    printf("data = %x\n", _self->buf->data);\
    _self->last_offset = _self->buf->data+sizeof(uint32_t);\
  } else {\
    uint32_t off = _self->last_offset - _self->buf->data;\
    _self->buf->size += sizeof(struct struct_name);\
    _self->buf->data = realloc(_self->buf->data, _self->buf->size);\
    _self->last_offset = _self->buf->data + off;\
  }\
  _self->ptr_os = realloc(_self->ptr_os, sizeof(struct ptr_offset)*(_self->num_ptr_os+1));\
  _self->ptr_os[_self->num_ptr_os].ptr = s;\
  _self->ptr_os[_self->num_ptr_os].offset = _self->last_offset - _self->buf->data + sizeof(uint32_t);\
  _self->num_ptr_os += 1;

#define sattr(attr)\
  *((__typeof(s->attr)*)_self->last_offset) = s->attr; 	_self->last_offset += sizeof(s->attr);
  
#define sstruct_ptr(attr, struct_name, mod)\
  *((void**)_self->last_offset) = s->attr;		_self->last_offset += sizeof(void*);\
  if(!check_ptr_in_po(_self->num_ptr_os, _self->ptr_os, s->attr)) {\
    struct_name##_##mod##_serializer(s->attr, _self);\
  }

#define sfunc_end \
  if(root) {\
    _self->buf->size += sizeof(struct ptr_offset) * _self->num_ptr_os;\
    _self->buf->data = realloc(_self->buf->data, _self->buf->size);\
    printf("loff = %x\n off = %x", _self->last_offset, _self->ptr_os->offset);\
    memcpy(_self->last_offset, _self->ptr_os, sizeof(struct ptr_offset) * _self->num_ptr_os);\
    *(uint32_t*)_self->buf->data = _self->buf->size;\
    return _self->buf;\
  }\
  printf("loff = %x\n", _self->last_offset);\
}

#define serialize(obj_ptr, struct_name, mod)		struct_name##_##mod##_serializer(obj_ptr, NULL)
#define deserialize(sdata_ptr, struct_name, mod)	struct_name##_##mod##_deserializer(sdata_ptr, NULL, NULL, NULL, NULL, 1)

#endif /* __SERIALIZE_H__ */