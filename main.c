#include "engine.h"
#include "scene.h"
#include "viewport.h"
#include "camera.h"
#include "entity.h"
#include "mesh.h"
#include "math.h"
#include "sc_obj.h"
#include <stdio.h>
#include <malloc.h>

#include "serialization.h"

int main() {
  struct engine* engine;
  engine = malloc(sizeof(struct engine));
  if(!neng_init(engine, "Nutty Engine Test")) {
    printf("engine init fail\n");
  }
  
  struct ptr_offset ptr_offset1[] = {
//     {engine->viewport, offsetof(struct engine, viewport), sizeof(struct viewport)},
    {engine->gl_ver, offsetof(struct engine, gl_ver), /*sizeof(*(engine->gl_ver))*/6}
  };
  
  struct dna and = {
    ENDIAN_LITTLE,
    ARCH_X86
  };
  
  void* sdata = serialize(engine, sizeof(*engine), &and, ptr_offset1, 1);
  FILE* sdata_file = fopen("./sdata", "w");
  fputs((char*)sdata, sdata_file);
  fwrite(sdata, 1, *(uint32_t*)(sdata+2), sdata_file);
  fclose(sdata_file);
  //load scene from .blend
  
  //create scene
  //  create objects
  //  set viewport and camera
  struct scene* sc = scene_create("scene0", 1);
  engine->scenes = sc;
  
  while(neng_frame(engine, .3f));
  neng_shutdown(engine);
}
