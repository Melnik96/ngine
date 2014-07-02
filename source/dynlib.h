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


#ifndef __DYNLIB_H__
#define __DYNLIB_H__

#include <stdint.h>

enum dynlib_type {
  DT_CSRIPT,
  DT_SOLIB,
};

struct dynlib {
  char name[32];
  void* intense;
  uint8_t type;
};

struct dynlib* 	dynlib_open(struct ngine* _ngine, char* _name);
int 		dynlib_close(struct dynlib* _module);
void* 		dynlib_getsym(struct dynlib* _module, char* _symname);
void* 		dynlib_addsym(struct dynlib* _module, char* _symname, void* _sym);

#endif /* __DYNLIB_H__ */
