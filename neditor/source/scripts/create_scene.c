#include "ngine.h"

#include "scene.h"
#include "sc_obj.h"
#include "entity.h"
#include "mesh.h"
#include "material.h"
#include "texture.h"

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
  
  struct ngine_mesh* mesh_suzy = ngine_mesh_import_obj("media/models/icosphere.obj");
//   ngine_texture_image(mesh_suzy->chunk->mtl->tex_color, "media/textures/mapgrid.tga");
  ngine_mesh_update(mesh_suzy);
  
  struct ngine_entity* ent_suzy = ngine_entity_create("triangle", mesh_suzy);
  struct ngine_sc_node* node_suzy = ngine_sc_node_create("suzanne", NGINE_SC_OBJ_ENTITY);
  
  node_suzy->attached_obj = (struct list*)ent_suzy;
  node_suzy->pos.z = -10;
  
  tree_add_child((struct tree*)nscene->root_object, (struct tree*)node_suzy);
  
  {// triangle
  struct ngine_mesh* mesh_tri = ngine_mesh_create(1);
    mesh_tri->num_vertices = 3;
    mesh_tri->vertices = (vec3[]){
    {0, 0.75, 0},
    {0.75, -0.75, 0},
    {-0.75, -0.75, 0},
  };
    mesh_tri->uvs = (vec2[]){
    {0.5, 0.0},
    {1.0, 1.0},
    {0.0, 1.0}
  };
  
  mesh_tri->chunk->num_indices = 3;
  mesh_tri->chunk->indices = (int32_t[]){
     0, 1, 2
  };
  
  mesh_tri->chunk->mtl = ngine_material_create();
  mesh_tri->chunk->mtl->tex_color = ngine_texture_create(0);
  ngine_texture_image(mesh_tri->chunk->mtl->tex_color, "media/textures/mapgrid.tga");
  
  ngine_mesh_update(mesh_tri);
  
  struct ngine_entity* ent_tri = ngine_entity_create("triangle", mesh_tri);
  struct ngine_sc_node* obj_tri = ngine_sc_node_create("triangle", NGINE_SC_OBJ_ENTITY);
  
  obj_tri->attached_obj = (struct list*)ent_tri;
  obj_tri->pos.z = -5;
  
  tree_add_child((struct tree*)nscene->root_object, (struct tree*)obj_tri);
  }
  
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
