#include <libtcc.h>

#include "ngine.h"
#include <iofile.h>
#include <viewport.h>

struct neditor {
  struct engine* engine;
};

int main(int argc, char *argv[]) {
  struct neditor* neditor = malloc(sizeof(struct neditor));
  neditor->engine = ngine_create();
  ngine_create_window("Nutty Engine Editor", 640, 480);
  
  // load base assets(shaders, gui materials, sounds, scripts with logic nodes)
  // create scene(gui, scene grid)
  // create viewport
  // attach camera to viewport
  // attach viewport to window
  
  // cinterp to console(stdio) and rconsole(socket)
  
  // create scene in script 'create_scene.c'
  TCCState* script_sc = tcc_new();
  tcc_compile_string(script_sc, file_rdbufp("./scripts/create_scene.c"));
  tcc_add_symbol(script_sc, "ngine_intense", &ngine_intense);
  tcc_add_symbol(script_sc, "neditor_intense", &neditor_intense);
  tcc_relocate(script_sc, TCC_RELOCATE_AUTO);
  void(*create_scene)(void) = tcc_get_symbol(script_sc, "create_scene");
  tcc_delete(script_sc);
  
  create_scene();
  
  neditor->engine->windows[0].viewport->;
  
  while(1) {
    ngine_frame(neditor->engine);
  }
  ngine_shutdown(neditor->engine);
}
