#include <libtcc.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "engine.h"
#include "iofile.h"

struct cinterp {
//   struct string name;
  void* global;
};
  TCCState* tcc;

void tcc_error_cb(void *opaque, const char *msg) {
  printf("%s\n", msg);
}

const char* main_start = "void line_fun() {\n";
const char* main_end = "\n}\n";

struct engine* get_ngine_intense() {
  return 32;
}

void(*line_fun)(void);

struct cinterp* cinterp_create();
int cinterp_init(struct cinterp* _self);

int main(int argc, char *argv[]) {
//   char* source = file_rdbufp(argv[1]);
  char source[1024];
  char line[1024];
  
  
  
//   if(tcc_compile_string(tcc, source) == -1) { printf("error\n"); }
//   tcc_run(tcc, 0, 0);
  
  printf("cinterp test version\n");
  while(1) {
    tcc = tcc_new();
    tcc_set_error_func(tcc, NULL, tcc_error_cb);
    tcc_set_output_type(tcc, TCC_OUTPUT_MEMORY);
    
    
    memset(source, 0, 1024);
    printf(">>>");
    gets(line);
    strcat(source, main_start);
    strcat(source, line);
    strcat(source, main_end);
    tcc_compile_string(tcc, source);
    
    tcc_add_symbol(tcc, "get_ngine_intense", get_ngine_intense);
    void* asd = malloc(1024);
    tcc_relocate(tcc, asd);
    line_fun = tcc_get_symbol(tcc, "line_fun");
    
    line_fun();
    
//     tcc_run(tcc, 0, 0);
//     printf("\n");
    tcc_delete(tcc);
  }
}