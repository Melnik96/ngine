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

#include "serialization.h"

void* serialize(void* _data, uint32_t _data_size, struct dna* _dna, void* _ptr_offset, uint32_t _po_len) {
  void* sdata;
  void* end_used;
  
  
#if __x86_64__
  uint64_t po_size = _po_len * sizeof(struct ptr_offset_64);
#elif __i386__
  printf("#elseif __i386__\n");
  uint32_t total_size;
  uint32_t ptrs_data_size = 0;
  
  for(uint8_t i = 0; i < _po_len; i+=1) {
    ptrs_data_size += ((struct ptr_offset_32*)_ptr_offset)[i].size;
  }
  
  uint32_t po_size = _po_len * sizeof(struct ptr_offset_32);
  total_size = MO_PTR_OFFSET+po_size+_data_size+ptrs_data_size;
  
  sdata = malloc(total_size);
  
  end_used = sdata;
  
  memcpy(end_used, _dna, sizeof(struct dna));
  end_used += sizeof(struct dna);
  memcpy(end_used, &total_size, sizeof(uint32_t));
  end_used += sizeof(uint32_t);//4 bytes
  memcpy(end_used, &_data_size, sizeof(uint32_t));
  end_used += sizeof(uint32_t);
  memcpy(end_used, &_po_len, sizeof(uint16_t));
  end_used += sizeof(uint16_t);//2 bytes
  memcpy(end_used, _ptr_offset, po_size);
  end_used += po_size;
  memcpy(end_used, _data, _data_size);
  end_used += _data_size;
  
  uint32_t cur_ptr_size;
  for(uint8_t i = 0; i < _po_len; i+=1) {
    cur_ptr_size = ((struct ptr_offset_32*)_ptr_offset)[i].size;
    memcpy(end_used, (void*)(((struct ptr_offset_32*)_ptr_offset)[i].ptr), cur_ptr_size);
    end_used += cur_ptr_size;
  }
#else 
// #  error unsupported arch
#endif
  
  return sdata;
}

void* deserialize(void* _sdata) {
  void* data;
  
  uint32_t base_data_size;
  uint32_t po_len;
  
  struct dna* dna_data = ((struct dna*)_sdata/*+MO_DNA*/);
  po_len = *((uint16_t*)(_sdata+MO_PO_COUNT));
  
  if(((struct dna*)_sdata)->arch == ARCH_X64) {
    struct ptr_offset_64* ptr_offset;
    
    base_data_size = *((uint64_t*)_sdata+MO_BDATA_SIZE_64);
    ptr_offset = ((struct ptr_offset_64*)_sdata+MO_PTR_OFFSET_64);
    data = (void*)(_sdata+MO_PTR_OFFSET_64+po_len*sizeof(struct ptr_offset_64));
  
    for(uint8_t i = 0; i < po_len; i+=1) {
      void* ptr_sdata = (void*)(data+base_data_size+(uint64_t)(ptr_offset[i].sdata_offset));
      memcpy((void*)(data+ptr_offset[i].offset), &ptr_sdata, sizeof(uint64_t));
    }
  } else {
    struct ptr_offset_32* ptr_offset;
    
    base_data_size = *((uint32_t*)_sdata+MO_BDATA_SIZE);
    ptr_offset = ((struct ptr_offset_32*)_sdata+MO_PTR_OFFSET);
    data = (void*)(_sdata+MO_PTR_OFFSET+po_len*sizeof(struct ptr_offset_32));
   
    for(uint8_t i = 0; i < po_len; i+=1) {
      void* ptr_sdata = (void*)(data+base_data_size+(uint32_t)(ptr_offset[i].sdata_offset));
      memcpy((void*)(data+ptr_offset[i].offset), &ptr_sdata, sizeof(uint32_t));
    }
  }
  
  return data;
};
