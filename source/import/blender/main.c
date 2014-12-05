#include "blenloader/BLO_readfile.h"
#include "blenkernel/BKE_main.h"
#include "makesdna/DNA_scene_types.h"
#include "makesdna/DNA_listBase.h"
#include "makesdna/DNA_node_types.h"
#include "makesdna/DNA_object_types.h"

// #include "sc_obj.h"

#include "blen_scene.h"

int main() {
//   struct sc_obj* cur_obj = malloc(sizeof(struct sc_obj));
  BlendFileData* blen = BLO_read_from_file("path", 0);
  struct Object* b_cur_obj = (struct Object*)(blen->main->object.first);
  
//   cur_obj->pos.x = b_cur_obj->loc[0];
//   cur_obj->pos.y = b_cur_obj->loc[1];
//   cur_obj->pos.z = b_cur_obj->loc[2];
//   
//   cur_obj->orient.w = b_cur_obj->quat[0];
//   cur_obj->orient.x = b_cur_obj->quat[1];
//   cur_obj->orient.y = b_cur_obj->quat[2];
//   cur_obj->orient.z = b_cur_obj->quat[3];
}