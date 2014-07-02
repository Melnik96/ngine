#include <libtcc.h>
#include <malloc.h>
#include <string.h>

void cinterp_run() {
  char* buf = calloc(2048 + 128);
  char* code_stack = calloc(2048);
  TCCState* tcc = tcc_new();
  
  char* cmd = calloc(64);
  
  printf("cinterp\n");
  while(1) {
    memset(cmd, 0, 64);
    memset(buf, 0, 2048 + 128);
    
    printf(">>> "); scanf("%s\n", cmd);
    strcat(code_stack, cmd);
    
    strcat(buf, "#include \"/home/melnik/projects/ngine-master/source/ngine.h\"");
    strcat(buf, "void cmd() {\n");
    strcat(buf,    code_stack);
    strcat(buf, "}\n");
    
    tcc_compile_string(tcc, buf);
    
    tcc_relocate(tcc, TCC_RELOCATE_AUTO);
    
    line_fun = tcc_get_symbol(tcc, "line_fun");
    line_fun();
  }
}
