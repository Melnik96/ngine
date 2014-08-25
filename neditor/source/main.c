#include <malloc.h>

#include "ngine.h"
#include "window.h"
#include "iohand/input.h"
#include "render/render.h"

#include "gui_surf.h"
#include "default_scene.h"
#include "neditor.h"

const int width = 1024;
const int height = 768;

int main(int argc, char *argv[]) {
  struct neditor* neditor = malloc(sizeof(struct neditor));
  neditor->engine = ngine_create();
  
  struct ngine* ngine = neditor->engine;
  
  ngine->windows = ngine_window_create("Nutty Engine Editor", 0, width, height);
  ngine->input = ngine_input_create(ngine->windows);
  ngine->render = ngine_render_create();
  
  neditor_default_scene_create();
  neditor_guisurf_create(width, height);
  
  ngine_start(ngine);
  ngine_shutdown(ngine);
}
