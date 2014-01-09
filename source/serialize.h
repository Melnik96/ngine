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

struct buffer {
  size_t size;
  void*  data;
};

struct ptr_offset {
  intptr_t ptr;
  intptr_t offset;
};

struct ptr_offset* check_ptr_in_po(size_t _ptr_num, struct ptr_offset* _ptr_os, void* _ptr);
void* find_ptr_in_array(size_t _num_ptrs, void** _ptrs, void* _ptr);

#define sfunc(struct_name, mod) 		struct buffer* struct_name##_##mod##_serializer(struct struct_name* s, struct ptr_offset* _ptr_os, size_t* _po_num, int _r_ser) {\
						  struct buffer* buf = malloc(sizeof(struct buffer));\
						  buf->data = malloc(sizeof(struct struct_name));\
						  buf->size = sizeof(struct struct_name);\
						  void* lnd = buf->data;\
						  if(_po_num == NULL) { _po_num = malloc(sizeof(size_t)); *_po_num = 0; }

#define schar(attr)				  memcpy(lnd, &s->attr, sizeof(char));					lnd += sizeof(char);
#define sint16(attr)				  memcpy(lnd, &s->attr, sizeof(int16_t));				lnd += sizeof(int16_t);
#define sint32(attr)				  memcpy(lnd, &s->attr, sizeof(int32_t));				lnd += sizeof(int32_t);
#define sint64(attr)				  memcpy(lnd, &s->attr, sizeof(int64_t));				lnd += sizeof(int64_t);
#define sfloat(attr)				  memcpy(lnd, &s->attr, sizeof(float));					lnd += sizeof(float);
#define sdouble(attr)				  memcpy(lnd, &s->attr, sizeof(double));				lnd += sizeof(double);

#define svoid_ptr(attr, _size)			  void* new_sdata = realloc(buf->data, buf->size+=((_size) - sizeof(void*)));\
						  if(new_sdata != buf->data) {\
						    memmove(new_sdata, buf->data, (size_t)(lnd - buf->data));\
						    lnd = new_sdata + (lnd - buf->data);\
						    buf->data = new_sdata;\
						  }\
						  memcpy(lnd, s->attr, _size);						lnd += _size;

#define schar_ptr(attr)				  size_t attr##size = strlen(s->attr);\
						  void* new_sdata = realloc(buf->data, buf->size+=((attr##size) - sizeof(void*)))\
						  if(new_sdata != buf->data) { memmove(new_sdata, buf->data, (size_t)(lnd - buf->data)); }\
						  buf->data = new_sdata;\
						  memcpy(lnd, s->attr, attr##size);					lnd += attr##size;

#define sstruct_ptr(attr, struct_name, mod)	  *((void**)lnd) = s->attr;						lnd += sizeof(void*);\
						  if(!check_ptr_in_po(*_po_num, _ptr_os, s->attr)) {\
						    struct buffer* buf_##attr = struct_name##_##mod##_serializer(s->attr, _ptr_os, _po_num, 0);\
						    void* new_data = realloc(buf->data, buf->size + buf_##attr->size);\
						    if(buf->data != new_data) { memmove(new_data, buf->data, buf->size); }\
						    lnd = new_data + (lnd - buf->data);\
						    memcpy(lnd, buf_##attr->data, buf_##attr->size);			lnd += buf_##attr->size;\
						    buf->size += buf_##attr->size;\
						    free(buf_##attr);\
						    void* new_po = realloc(_ptr_os, (*_po_num+1) * sizeof(struct ptr_offset));\
						    if(_ptr_os != new_po) {\
						      memmove(new_po, _ptr_os, (*_po_num) * sizeof(struct ptr_offset));\
						      _ptr_os = new_po;\
						    }\
						    _ptr_os[*_po_num].ptr = (intptr_t)s->attr;\
						    _ptr_os[*_po_num].offset = lnd - buf_##attr->data;\
													  *_po_num += 1;\
						  }

#define funcs 					  if(_r_ser && _ptr_os) {\
						    void* new_data = realloc(buf->data, buf->size + sizeof(size_t) + (*_po_num) * sizeof(struct ptr_offset));\
						    memmove(new_data + sizeof(size_t) + (*_po_num) * sizeof(struct ptr_offset), buf->data, buf->size);\
						    *((size_t*)new_data) = *_po_num;\
						    memcpy(new_data + sizeof(size_t), _ptr_os, *_po_num * sizeof(struct ptr_offset));\
						    buf->data = new_data;\
						    buf->size += sizeof(size_t) + *_po_num * sizeof(struct ptr_offset);\
						  }\
						  return buf;\
						}

#define dsfunc(struct_name, mod) 		struct struct_name* struct_name##_##mod##_deserializer(void* sdata) {\
						  struct struct_name* dsdata = malloc(sizeof(struct struct_name));\
						  size_t po_num = *((size_t*)sdata);\
						  printf("afsf = %x", sdata);\
						  struct ptr_offset* ptr_os = (sdata + sizeof(size_t));\
						  size_t po_last_ds = 0;\
						  struct ptr_offset* ptr_os_ds = malloc(po_num * sizeof(struct ptr_offset));\
						  void* lnds = (sdata + sizeof(size_t) + po_num*sizeof(struct ptr_offset));

#define dschar(attr)				  dsdata->attr = *(char*)lnds;						lnds += sizeof(char);
#define dsint16(attr)				  dsdata->attr = *(int16_t*)lnds;					lnds += sizeof(int16_t);
#define dsint32(attr)				  dsdata->attr = *(int32_t*)lnds;					lnds += sizeof(int32_t);
#define dsint64(attr)				  dsdata->attr = *(int64_t*)lnds;					lnds += sizeof(int64_t);
#define dsfloat(attr)				  dsdata->attr = *(float*)lnds;						lnds += sizeof(float);
#define dsdouble(attr)				  dsdata->attr = *(double*)lnds;					lnds += sizeof(double);

#define dsvoid_ptr(attr, size)			  dsdata->attr = malloc(size);\
						  memcpy(dsdata->attr, lnds, (size));					lnds += size;

#define dschar_ptr(attr)			  size_t attr##_size = strlen((char*)lnds)+1;\
						  dsdata->attr = malloc(attr##_size);\
						  memcpy(dsdata->attr, lnds, attr##_size);				lnds += attr##_size;

#define dsstruct_ptr(attr, struct_name, mod)	  struct ptr_offset* p = NULL;\
						  if(p = check_ptr_in_po(po_last_ds, ptr_os_ds, *((void**)lnds))) {\
						    dsdata->attr = p->offset;						lnds += sizeof(void*);\
						  } else if(p = check_ptr_in_po(po_num, ptr_os, *((void**)lnds))) {\
						    struct struct_name* dsattr_##attr = struct_name##_##mod##_deserializer((sdata + p->offset));\
						    dsdata->attr = dsattr_##attr;\
						    ptr_os_ds[po_last_ds].ptr = p->ptr;\
						    ptr_os_ds[po_last_ds].offset = dsattr_##attr;	po_last_ds += 1;	lnds += sizeof(void*) + sizeof(struct struct_name);\
						  }

#define funcds					  return dsdata;\
						}


#define serialize(obj_ptr, struct_name, mod)		struct_name##_##mod##_serializer(obj_ptr, NULL, NULL, 1)

#define deserialize(sdata_ptr, struct_name, mod)	struct_name##_##mod##_deserializer(sdata_ptr)

#endif /* __SERIALIZE_H__ */
