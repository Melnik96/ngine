#include "ngine.h"

#include "scene.h"
#include "sc_obj.h"
#include "entity.h"
#include "mesh.h"

// #include "import/collada/daeu.h"
#include "import/obj/obj.h"

#include "sound_mgr.h"
#include <fmodex/fmod.h>

#include "log.h"

#include <stdlib.h>

struct scene* create_scene() {
  struct scene* nscene = scene_create("neditor", 1);
  debug("scene 'neditor' created");
//   collada_convert_scene(nscene, dae_COLLADA);
//   struct ngine_mesh* mesh_suzy = ngine_mesh_import_obj("media/models/suzanne.obj");
//   struct entity* ent_suzy = ngine_entity_create("suzanne", mesh_suzy);
//   
//   struct ngine_sc_obj* obj_suzy = ngine_sc_obj_create("suzanne", NGINE_SC_OBJ_ENTITY);
//   
//   obj_suzy->typed_objs = (struct list*)ent_suzy;
//   obj_suzy->pos.z = -10;
//   
  
  struct ngine_mesh* mesh_suzy = ngine_mesh_create(1);
  mesh_suzy->num_vertices = 4;
  mesh_suzy->vertices = (vec3[]){
    {-1, -1, 0},
    {1, -1, 1},
    {1, -1, 0},
    {0, 1, 0}
  };
  
  mesh_suzy->chunk->num_indices = 12;
  mesh_suzy->chunk->indices = (int32_t[]){
     0, 3, 1,
     1, 3, 2,
     2, 3, 0,
     0, 2, 1
  };
  
  ngine_mesh_update(mesh_suzy);
  
  struct ngine_entity* ent_suzy = ngine_entity_create("triangle", mesh_suzy);
  struct ngine_sc_obj* obj_suzy = ngine_sc_obj_create("triangle", NGINE_SC_OBJ_ENTITY);
  
  obj_suzy->typed_objs = (struct list*)ent_suzy;
  obj_suzy->pos.z = -10;
  
  tree_add_child((struct tree*)nscene->root_object, (struct tree*)obj_suzy);
  
  return nscene;
}

void print_win_closed() {
  debug("event: window closed");
//   ngine_shutdown();
  exit(0);
}

void key_pressed(int _key) {
  debug("event: key_pressed %i", _key);
//   printf("ngine_intense: %x\n", ngine_intense());
  if(_key == 256) {//ESC
    exit(0);
  } else if(_key == 49) {
//     FMOD_SOUND* sound1 = 0;
//     FMOD_System_CreateSound(ngine_intense()->fmod_sound, "./media/sounds/stereo.ogg", FMOD_SOFTWARE | FMOD_3D, 0, &sound1);
// 
//     speaker_play_fmod(ngine_intense()->scenes->root_object->link.childs, ngine_intense()->fmod_sound, sound1, 0);
  }
}
