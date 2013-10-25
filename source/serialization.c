// /*
//  * <one line to give the program's name and a brief idea of what it does.>
//  * Copyright (C) 2013  <copyright holder> <email>
//  *
//  * This program is free software: you can redistribute it and/or modify
//  * it under the terms of the GNU General Public License as published by
//  * the Free Software Foundation, either version 3 of the License, or
//  * (at your option) any later version.
//  *
//  * This program is distributed in the hope that it will be useful,
//  * but WITHOUT ANY WARRANTY; without even the implied warranty of
//  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  * GNU General Public License for more details.
//  *
//  * You should have received a copy of the GNU General Public License
//  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
//  *
//  */
// 
// #include "serialization.h"
// 
// void* serialize(void* _data, uint32_t _data_size, uint32_t* _ptr_offset, uint32_t _po_len) {
//   void* sdata;
//   void* end_used;
//   
//   uint32_t total_size;
//   uint32_t po_size = _po_len *32;
//   uint32_t uint_size = sizeof(uint32_t);
//   uint32_t ptrs_data_size;
//   
//   for(uint8_t i = 0; i<= _po_len; i+=3) {//gcc вроді оптимізує
//     ptrs_data_size += _ptr_offset[i];
//   }
//   
//   total_size = uint_size*3+po_size+_data_size+ptrs_data_size;
//   
//   sdata = malloc(total_size);
//   
//   end_used = sdata;
//   
//   memcpy(end_used, &total_size, uint_size);//sdata = _ptr_count
//   end_used += uint_size;
//   memcpy(end_used, &_po_len, uint_size);//sdata = _ptr_count
//   end_used += uint_size;
//   memcpy(end_used, _ptr_offset, po_size);
//   end_used += po_size;
//   memcpy(end_used, &_data_size, uint_size);//sdata = _ptr_count
//   end_used += uint_size;
//   memcpy((void*)end_used, _data, _data_size);
//   end_used += _data_size;
//   
//   uint32_t tmp_ptr_size;
//   for(uint8_t i = 0; i<= _po_len; i+=3) {
//     tmp_ptr_size = sizeof(_ptr_offset[i]);
//     memcpy(end_used, (void*)_ptr_offset[i-2], tmp_ptr_size);
//     end_used += tmp_ptr_size;
//   }
//   return sdata;
// }
// 
// void* deserialize(void* _sdata) {
//   void* data;
//   
//   uint32_t base_data_size;
//   
//   uint32_t total_size;
//   uint32_t uint_size = sizeof(uint32_t);
//   
//   uint32_t po_len;
//   uint32_t po_size;
//   void* ptr_offset;
//   
//   total_size = *((uint32_t*)_sdata);//unused here
//   po_len = *((uint32_t*)_sdata+uint_size);
//   ptr_offset = ((uint32_t*)_sdata+uint_size*2);
//   po_size = po_len*32;
//   base_data_size = *((uint32_t*)_sdata+uint_size*2+po_size);
//   
//   data = (void*)(((uint32_t)_sdata)+uint_size*3+po_size);
//   
//   for(uint8_t i = 0; i<=po_len+3; i+=3) {
//     void* p = (void*)((uint32_t)data+base_data_size+ptr_offset[i+2]);
//     (void*)((uint32_t)data+ptr_offset[i+1]) = p;
//   }
//   
//   return data;
// };
