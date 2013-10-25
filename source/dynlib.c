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

static struct mempool* dynlib_pool;

dynlib* dynlib_open(char* _name) {
  struct dynlib* module;
  module = mempool_alloc(dynlib_pool);
  module->intense = dlopen(_name, RTLD_LAZY);
  module->type = so_module;
  module->name= _name;
}
int dynlib_close(dynlib* _module) {

}
void* dynlib_getsym(dynlib* _module, char* _symname) {

}

