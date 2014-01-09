#include "serialize.h"
#include "cntr/list.h"
#include "dynstr.h"

#include "tool.h"
#include "sfuncs.h"

int main() {
  struct list tool_list;
  
  struct tool blender;
  struct tool cmake;
  struct tool gcc;
  
  blender.name = strp("Blender");
  blender.type = strp("3d modeling");
  blender.size = 2424;
  
  cmake.name = strp("cmake");
  cmake.type = strp("building");
  cmake.size = 512;
  
  blender.name = strp("gcc");
  blender.type = strp("compiler");
  blender.size = 12480;
  
  list_init(&tool_list);
  list_insert(&tool_list, &blender.link);
  list_insert(&tool_list, &cmake.link);
  list_insert(&tool_list, &gcc.link);
  
  struct buffer* buf = serialize(&tool_list, tool,);
  
  int f = fopen("./sdata", "w");
  fwrite(buf->data, buf->size, 1, f);
  fclose(f);
}
