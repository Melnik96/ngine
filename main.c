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

int main() {
  struct engine* engine;
  engine = malloc(sizeof(struct engine));
  if(!neng_init(engine, "Nutty Engine Test")) {
    printf("engine init fail\n");
  }
  
  //load scene from .blend
  
  //create scene
  //  create objects
  //  set viewport and camera
  struct scene* sc = scene_create("scene0", 1);
  engine->scenes = sc;
  
  while(neng_frame(engine, .3f));
  neng_shutdown(engine);
}
