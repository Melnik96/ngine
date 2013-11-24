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

#include "serialize.h"

int main() {
  struct engine* engine0;
  engine0 = malloc(sizeof(struct engine));
  if(!neng_init(engine0, "Nutty Engine Test")) {
    printf("engine init fail\n");
  }
  
  struct ptr_offset_32 ptr_offset1[] = {
//     {engine->viewport, offsetof(struct engine, viewport), sizeof(struct viewport)},
    {engine0->gl_ver, offsetof(struct engine, gl_ver), 0, /*sizeof(*(engine->gl_ver))*/6}
  };
  
  struct dna and = {
    ENDIAN_LITTLE,
    ARCH_X86
  };
  
  void* sdata = serialize(engine0, sizeof(*engine0), &and, ptr_offset1, 1);
  FILE* sdata_file = fopen("./sdata", "w");
  fputs((char*)sdata, sdata_file);
  fwrite(sdata, 1, *(uint32_t*)(sdata+2), sdata_file);
  fclose(sdata_file);
  //deserialize
  struct engine* engine_des;
  engine_des = deserialize(sdata);
  printf("deserialized data struct: engine      gl_ver = %s\n", engine_des->gl_ver);
  
  //load scene from .blend
  
  //create scene
  //  create objects
  //  set viewport and camera
  struct scene* sc = scene_create("scene0", 1);
  engine0->scenes = sc;
  
  while(neng_frame(engine0, .3f));
  neng_shutdown(engine0);
}
