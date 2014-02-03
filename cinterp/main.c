#include <libtcc.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "engine.h"
#include "iofile.h"

#include "cinterp.h"

struct engine* get_ngine_intense() {
  return 32;
}


int main(int argc, char *argv[]) {
  cinterp_run(0);
}