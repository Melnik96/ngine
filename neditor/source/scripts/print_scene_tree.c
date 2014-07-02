#include <stdio.h>

#include "scene.h"
#include "sc_obj.h"

void print_scene_tree(struct scene* _scene) {
  printf("scene tree of '%s'\n", _scene->name);
  printf("|  |name                            |pos       |");
  tree_for_each(_scene->root_object, print_tree_handler);
}
// NOW TODO cinterp
void print_tree_handler(struct sc_obj* _obj) {
  uint32_t num_parents = tree_num_parents(_obj);
  for(uint32_t i = 0; i < num_parents; ++i) {
    printf("|  ");
  }
  if(_obj->link.next == NULL) {
    printf("`--");
  } else {
    printf("|--");
  }
  printf("%s                      (%f;%f;%f)\n", _obj->name, _obj->pos.x, _obj->pos.y, _obj->pos.z);
}

/* 
 * scene tree of 'some_scene'
 * |  |name                            |pos       |
 *  |--root_object                      (0;0;0)
 *  |  |--child_object                    (2;3.4;4)
 *  |  |--another_child_object            (2;3.4;4)
 *  |  |  |--child_object                    (2;3.4;4)
 *  |  |  `--child_object                    (2;3.4;4)
 *  |  `--child_object                    (2;3.4;4)
 *  |--child_object                    (2;3.4;4)
 *  `--child_object                    (2;3.4;4)
 */
