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
#ifndef __DYNLIB_H__
#define __DYNLIB_H__

#include <stdint.h>

//need support .so and .py modules

enum dynlib_type {
  so_module = (1<<1),
  py_module = (1<<2)
};

struct dynlib {
  char name[32];
  void* intense;
  uint8_t type;
};

struct dynlib* dynlib_open(char* _name);
int dynlib_close(struct dynlib* _module);
void* dynlib_getsym(struct dynlib* _module, char* _symname);

#endif /* __DYNLIB_H__ */
