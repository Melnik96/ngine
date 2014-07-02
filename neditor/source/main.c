#include "ngine.h"
#include "window.h"
#include "scene.h"
#include "iofile.h"
#include "viewport.h"
#include "dynlib.h"
#include "sc_obj.h"
#include "sound_mgr.h"
#include "render/render.h"

#include <libtcc.h>
#include <malloc.h>

#include <fmodex/fmod.h>

struct neditor {
  struct ngine* engine;
};

int main(int argc, char *argv[]) {
  struct neditor* neditor = malloc(sizeof(struct neditor));
  neditor->engine = ngine_create();
  struct ngine* ngine = neditor->engine;
  neditor->engine->windows = window_create("Nutty Engine Editor", 640, 480);
  neditor->engine->render = ngine_render_create();
  
  // load base assets(shaders, gui materials, sounds, scripts with logic nodes)
  // create scene(gui, scene grid)
  // create viewport
  // attach camera to viewport
  // attach viewport to window
  
  // cinterp to console(stdio) and rconsole(socket)
  
  // create scene in script 'create_scene.c'
  struct dynlib* cs = dynlib_open(neditor->engine, "create_scene");
  struct scene*(*create_scene)(void) = dynlib_getsym(cs, "create_scene");
  void(*print_win_closed)(void) = dynlib_getsym(cs, "print_win_closed");
  void(*key_pressed)(void) = dynlib_getsym(cs, "key_pressed");
  dynlib_close(cs);
  
  neditor->engine->windows->listener->on_close = print_win_closed;
  neditor->engine->windows->input_listener->on_key_pressed = key_pressed;
  
  neditor->engine->scenes = create_scene();
  
  struct ngine_sc_obj* speaker = ngine_sc_obj_create("speaker1", NGINE_SC_OBJ_SPEAKER);
  tree_add_child(&neditor->engine->scenes->root_object->link, &speaker->link);
  
  speaker->pos.x = -10.f;
  
  FMOD_SOUND* sound1 = 0;
  FMOD_System_CreateSound(neditor->engine->fmod_sound, "./media/sounds/stereo.ogg", FMOD_SOFTWARE | FMOD_3D, 0, &sound1);

  speaker_play_fmod(speaker, neditor->engine->fmod_sound, sound1, 0);
  
  while(1) {
    ngine_frame(neditor->engine, 0.1f);
  }
  ngine_shutdown(neditor->engine);
}
