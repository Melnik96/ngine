#include <ngine.h>
#include <scene.h>
#include "import/collada/daeu.h"

void create_scene() {
  struct scene* nscene = scene_create("neditor", true);
  collada_convert_scene(nscene, dae_COLLADA);
}
