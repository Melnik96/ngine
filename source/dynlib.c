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

#include "ngine.h"
#include "log.h"
#include "iofile.h"
#include "mempool.h"

#include <unistd.h>
#include <string.h>
// #include <str>
#include <stdio.h>
#include <dlfcn.h>

#include <libtcc.h>

#include "dynlib.h"

static struct mempool* dynlib_pool;

// char* nsprintf(const char *format, ...) {
//   char* ns = malloc(1024);//TODO FIX IT
//   sprintf(ns, format, va_arg);
// }

struct dynlib* dynlib_open(struct ngine* _ngine, char* _name) {
  struct dynlib* module;
  module = malloc(sizeof(struct dynlib));
  
  strcpy(module->name, _name);
  
// #ifdef LINUX
  char* full_path_so = malloc(46);
  char* full_path_c = malloc(46);
  sprintf(full_path_so, "scripts/%s.so", _name);
  sprintf(full_path_c, "../source/scripts/%s.c", _name);
  
  if(module->intense = dlopen(full_path_so, RTLD_LAZY)) {
    module->type = DT_SOLIB;
    debug(".so lib loaded");
  } else {
    char* script_source = file_rdbufp(full_path_c);
    if(script_source) {
      module->type = DT_CSRIPT;
      module->intense = tcc_new();
      
      tcc_add_sysinclude_path(module->intense, "/usr/include");
      tcc_add_sysinclude_path(module->intense, "/usr/local/include/");
      tcc_add_sysinclude_path(module->intense, "/usr/lib64/tcc/include/");
      tcc_add_include_path(module->intense, "../../source/");
      
      tcc_add_library_path(module->intense, "/usr/lib/");
      tcc_add_library_path(module->intense, "/usr/lib64/");
      tcc_add_library(module->intense, "../../bin/lib/x86/libngine.so");
      tcc_add_library(module->intense, "/usr/lib/x86/libfmodex.so");
      
      tcc_compile_string(module->intense, script_source);
//     tcc_add_symbol(module->intense, "ngine_intense", ngine_intense);
//     tcc_add_symbol(module->intense, "neditor_intense", &neditor_intense);
#if chache_scripts
      tcc_output_file(module->intense, full_path_so);
#endif
      tcc_relocate(module->intense, TCC_RELOCATE_AUTO);
      
      debug("cscript loaded");
    } else {
      warning("script %s %s", _name, "not found");
      return NULL;
      free(module);
    }
  }
// #endif
  return module;
}
int dynlib_close(struct dynlib* _module) {
// #ifdef LINUX
  if(_module->type == DT_CSRIPT) {
    tcc_delete(_module->intense);
  } else {
    dlclose(_module->intense);
  }
// #endif
  free(_module);
}
void* dynlib_getsym(struct dynlib* _module, char* _symname) {
// #ifdef LINUX
  if(_module->type == DT_CSRIPT) {
    return tcc_get_symbol(_module->intense, _symname);
  } else {
    return dlsym(_module->intense, _symname);
  }
// #endif
}
