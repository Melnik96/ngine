#include <ngine.h>
#include <scene.h>
#include <import/obj.h>

void create_scene() {
  scene_create("benchmark", true);
  obj_load_mesh();
}
