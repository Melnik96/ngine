#include "engine.h"
#include "scene.h"
#include "viewport.h"
#include "camera.h"
#include "entity.h"
#include "material.h"
#include "mesh.h"
#include "math.h"
#include "sc_obj.h"
#include <stdio.h>
#include <malloc.h>

#include "serialize.h"
#include <cntr/tree.h>

int main() {
  struct engine* engine0;
  engine0 = malloc(sizeof(struct engine));
  if(!neng_init(engine0, "Nutty Engine Test")) {
    printf("engine init fail\n");
  }
  
//   struct ptr_offset_32 ptr_offset1[] = {
// //     {engine->viewport, offsetof(struct engine, viewport), sizeof(struct viewport)},
//     {engine0->gl_ver, offsetof(struct engine, gl_ver), 0, /*sizeof(*(engine->gl_ver))*/6}
//   };
//   
//   struct dna and = {
//     ENDIAN_LITTLE,
//     ARCH_X86
//   };
//   
//   void* sdata = serialize(engine0, sizeof(*engine0), &and, ptr_offset1, 1);
//   FILE* sdata_file = fopen("./sdata", "w");
//   fputs((char*)sdata, sdata_file);
//   fwrite(sdata, 1, *(uint32_t*)(sdata+2), sdata_file);
//   fclose(sdata_file);
//   //deserialize
//   struct engine* engine_des;
//   engine_des = deserialize(sdata);
//   printf("deserialized data struct: engine      gl_ver = %s\n", engine_des->gl_ver);
  
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
  vec3 vert[4];vert[0].val;
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
  mh.num_vertices = 12;
  uint16_t indices[] = 
    { 0, 3, 1,
      1, 3, 2,
      2, 3, 0,
      0, 2, 1 };
  mh.indices = indices;
  mh.vertices = vert;
  
  struct entity ent;
  memset(&ent, 0, sizeof(ent));
  entity_init(engine0, &ent, "model_ent", &mh, &mat);
  
  model->typed_objs = &ent;
  model->listener = 0;
  model->pos.z = -2.f;
  sc_obj_update_matrix(model);
  
  //add camera
  struct sc_obj* cam = sc_obj_create(engine0, "cam0", "camera");
  tree_add_child(&sc->root_object->link, &cam->link);
  mat4_identity(&cam->model_matrix);
  
  engine0->viewport = malloc(sizeof(struct viewport));
  engine0->viewport->camera = cam;
  mat_perspective(30.0f, 1.0f, 0.01f, 1000.f,  &engine0->viewport->proj_matrix);
  
  engine0->active_render = 1;
  
  while(neng_frame(engine0, .3f));
  neng_shutdown(engine0);
}
