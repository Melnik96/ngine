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

#include "dynlib.h"

#include "mempool.h"

#include <dlfcn.h>
#include <string.h>

static struct mempool* dynlib_pool;

struct dynlib* dynlib_open(char* _name) {
  struct dynlib* module;
  module = malloc(sizeof(struct dynlib));
// #ifdef LINUX
  module->intense = dlopen(_name, RTLD_LAZY);
// #endif
  strcpy(module->name, _name);
}
int dynlib_close(struct dynlib* _module) {
// #ifdef LINUX
  dlclose(_module->intense);
// #endif
  free(_module->intense);
  free(_module->name);
  free(_module);
}
void* dynlib_getsym(struct dynlib* _module, char* _symname) {
// #ifdef LINUX
  return dlsym(_module->intense, _symname);
// #endif
}
