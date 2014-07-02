/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2014  <copyright holder> <email>
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

#ifndef CINTERP_H
#define CINTERP_H

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <malloc.h>

#include <libtcc.h>

#include "ngine.h"
#include "iofile.h"

struct cinterp {
//   struct string name;
  void* global;
};
  TCCState* tcc;

void tcc_error_cb(void *opaque, const char *msg) {
  printf("%s\n", msg);
}



// struct engine* get_ngine_intense() {
//   return ngine;
// }

void(*line_fun)(void);

struct cinterp* cinterp_create();
int cinterp_init(struct cinterp* _self);

int cinterp_run(void* _ptr_fun) {
//   char* source = file_rdbufp(argv[1]);
  char* script_includes = 	"#include \"/home/melnik/projects/ngine-master/source/ngine.h\"";
  const char* script_main_start = 	"void line_fun() {\n";
  char* script_main_body = 	"";
  const char* script_main_end = 	"\n}\n";
  char* source = malloc(1024);
  uint32_t source_len = 1024;
  char line[1024];
  
  clock_t last_clock;
  
//   printf("cinterp test version\n");
    tcc = tcc_new();
    tcc_set_error_func(tcc, NULL, tcc_error_cb);
    tcc_set_output_type(tcc, TCC_OUTPUT_MEMORY);
    tcc_add_include_path(tcc, "/home/melnik/projects/ngine-master/source/");
    
    int i = 0;
  while(1) {
    last_clock = clock();
    memset(source, 0, 1024);
    
    strcat(source, script_includes);
    
    printf("cinterp>>> ");
    gets(line);
//     if(memcmp(line, "#include", 9) == 0) {
//       source = (char*)realloc(source, source_len + strlen(line));
//       strcat(source, line);
//     } else {
      strcat(source, script_main_start);
      strcat(source, line);
      strcat(source, script_main_end);
      tcc_compile_string(tcc, source);
      tcc_add_symbol(tcc, "ngine_intense", _ptr_fun);
      if(i == 0) {
	tcc_relocate(tcc, TCC_RELOCATE_AUTO);
	i = 1;
      } else {
	tcc_relocate(tcc, NULL);
      }
      
      line_fun = tcc_get_symbol(tcc, "line_fun");
      line_fun();
//     }
    last_clock = clock() - last_clock;
    printf("\nclicks: %d (%f sec)\n", last_clock, ((float)last_clock)/CLOCKS_PER_SEC);
  }
  tcc_delete(tcc);
}

#endif // CINTERP_H
