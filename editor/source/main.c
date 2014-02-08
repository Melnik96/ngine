#include "engine.h"
#include "scene.h"
#include "viewport.h"
#include "camera.h"
#include "entity.h"
#include "material.h"
#include "mesh.h"
#include "math.h"
#include "sc_obj.h"
#include "math/vector.h"

#include <kazmath/mat4.h>

#include <stdio.h>
#include <malloc.h>
#include <signal.h>
#include <unistd.h>
#include <memory.h>

#include "serialize.h"
#include "cntr/tree.h"
#include "net.h"
#include "log.h"
#include "../cinterp/cinterp.h"

struct engine* get_ngine_intense(void* _ptr) {
  return _ptr;
}

int main(int argc, char *argv[]) {
//   signal(SIGINT, neng_shutdown);
//   signal(SIGTERM, cleanup);
  
  struct engine* engine0;
  engine0 = malloc(sizeof(struct engine));
  if(!ngine_init(engine0, "Nutty Engine Test")) {
    printf("engine init fail\n");
  }
  
  pthread_t thr_rcons;
  if(pthread_create(&thr_rcons, NULL, rconsole_init, NULL) < 0) {
      warning("could not create thread: rconsole");
  }
  pthread_t thr_cinterp;
  if(pthread_create(&thr_cinterp, NULL, cinterp_run, get_ngine_intense) < 0) {
      warning("could not create thread: cinterp");
  }
  debug("continue executing main thread");
  
  //load scene from .blend
  
  //create scene
  //  create objects
  //  set viewport and camera
  struct scene* sc = scene_create(engine0, "scene0", 1);
  engine0->scenes = sc;
  engine0->num_scenes += 1;
  sc->cur_shader = engine0->shaders;
  
//   sc->root_object = sc_obj_create("scene0_root_obj", "null");
  struct sc_obj* model = sc_obj_create(engine0, "tringle", "entity");
  tree_add_child(&sc->root_object->link, &model->link);
  
  struct material mat;
  vec3 vert[4];
  vert[0].x = -1.;
  vert[0].y = -1.;
  vert[0].z = 0;
  
  vert[1].x = 1.;
  vert[1].y = -1.;
  vert[1].z = 1;
  
  vert[2].x = 1.;
  vert[2].y = -1.;
  vert[2].z = 0;
  
  vert[3].x = 0;
  vert[3].y = 1.;
  vert[3].z = 0;
  
  struct mesh mh;
  memset(&mh, 0, sizeof(mh));
  mh.num_indices = 12;
  mh.num_vertices = 4;
  uint32_t indices[] = 
    { 0, 3, 1,
      1, 3, 2,
      2, 3, 0,
      0, 2, 1 };
  mh.indices = indices;
  mh.vertices = vert;
  
  printf("indices sizeof %i\n", sizeof(uint32_t));
  printf("vertices sizeof %i\n", sizeof(vec3));
  
  struct entity ent;
  memset(&ent, 0, sizeof(ent));
  entity_init(engine0, &ent, "model_ent", &mh, &mat);
  
  model->typed_objs = &ent;
  model->pos.z = -20.f;
  model->orient = (vec4){0.f, 0.f, 0.2f, deg2rad(50)};
  model->scale = 1.f;
//   sc_obj_update_matrix(model);
  
  //add camera
  struct sc_obj* cam = sc_obj_create(engine0, "cam0", "camera");
  tree_add_child(&sc->root_object->link, &cam->link);
  cam->pos = (vec3){0};
  cam->orient = (vec4){0.f, 0.f, 0.f, 1.f};
  
//   mat4_identity(&cam->model_matrix);
  
  engine0->viewport = malloc(sizeof(struct viewport));
  engine0->viewport->camera = cam;
  kmMat4PerspectiveProjection(&engine0->viewport->proj_matrix, 30.f, /*aspect*/1.20f, 1.f, 1000.f);
  
  if(argc > 1/* && strncmp(argv[1], "-norender", 5)*/) {
    engine0->active_render = 0;
  } else {
    engine0->active_render = 1;
  }
  
  while(ngine_frame(engine0, .3f));
  ngine_shutdown(engine0);
}
