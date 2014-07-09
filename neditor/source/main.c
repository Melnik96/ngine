#include "ngine.h"
#include "window.h"
#include "scene.h"
#include "iofile.h"
#include "viewport.h"
#include "dynlib.h"
#include "sc_obj.h"
#include "sound_mgr.h"
#include "iohand/input.h"
#include "render/render.h"
#include <camera.h>

#include <malloc.h>
#include <time.h>

#include <fmodex/fmod.h>

#include <kazmath/kazmath.h>

#include "neditor.h"

int main(int argc, char *argv[]) {
  struct neditor* neditor = malloc(sizeof(struct neditor));
  neditor->engine = ngine_create();
  struct ngine* ngine = neditor->engine;
  neditor->engine->windows = ngine_window_create("Nutty Engine Editor", 640, 480);
  neditor->engine->input = ngine_input_create(neditor->engine->windows);
  neditor->engine->render = ngine_render_create();
  
  // load base assets(shaders, gui materials, sounds, scripts with logic nodes)
  // create scene(gui, scene grid)
  // create viewport
  // attach camera to viewport
  // attach viewport to window
  
  // cinterp to console(stdio) and rconsole(socket)
  
  // create scene in script 'create_scene.c'
  struct dynlib* cs = dynlib_open(neditor->engine, "create_scene");
  struct scene*(*create_scene)(struct ngine*) = dynlib_getsym(cs, "create_scene");
  void(*print_win_closed)(void) = dynlib_getsym(cs, "print_win_closed");
//   dynlib_close(cs);
  
  
  neditor->engine->scenes = create_scene(neditor->engine);
  
  struct ngine_sc_node* speaker = ngine_sc_node_create(neditor->engine->scenes, "speaker1", NGINE_SC_OBJ_SPEAKER);
  tree_add_child(&neditor->engine->scenes->root_object->link, &speaker->link);
  
  speaker->pos.x = -10.f;
  
  FMOD_SOUND* sound1 = 0;
  FMOD_System_CreateSound(neditor->engine->fmod_sound, "./media/sounds/stereo.ogg", FMOD_SOFTWARE | FMOD_3D, 0, &sound1);
  speaker_play_fmod(speaker, neditor->engine->fmod_sound, sound1, 0);
  

  clock_t diff = clock();
  while(1) {
    diff = clock() - diff;
    float sec = ((float)diff)/CLOCKS_PER_SEC*1000;
    ngine_frame(neditor->engine, sec);
//     printf("fps %f\n", 1/sec);
    diff = clock();
  }
  ngine_shutdown(neditor->engine);
}
