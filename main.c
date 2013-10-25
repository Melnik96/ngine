// #include <stdlib.h>
// #include <SDL/SDL.h>
// #include <SDL/SDL_video.h>
// // #define GL3_PROTOTYPES 1
// #include <GL/glext.h>
// #include <malloc.h>
// // #include <linux/mod>
// 
// #include "scene_object.h"
// #include "mempool.h"
// 
// struct game {
//   //workers
//   pthread_t render;
//   pthread_t physics;
// //   pthread_t input;
// //   pthread_t sound;
//   pthread_t event_caller;//for game logic
//   
//   function event_buf[32];
//   
//   //server fd for clients
//   int fd;
// };
// 
// void event_caller_fun() {
//   while(1) {
//     event_buff[i]();
//   }
// }
// 
// int game_create_pools(struct game* _self) {
//   uint32_t size = sizeof(struct scene_object);
//   mempool_init(_self->scene_object_pool,
// 	       malloc(size*64),
// 	       size*64,
// 	       size);
//   size = sizeof(_self->entity_pool);
//   mempool_init(_self->entity_pool,
// 	       malloc(size*64),
// 	       size*64,
// 	       size);
//   size = sizeof(_self->mesh_pool);
//   mempool_init(_self->mesh_pool,
// 	       malloc(size*64),
// 	       size*64,
// 	       size);
//   size = sizeof(_self->dynlib_pool);
//   mempool_init(_self->dynlib_pool,
// 	       malloc(size*64),
// 	       size*64,
// 	       size);
//   size = sizeof(_self->camera_pool);
//   mempool_init(_self->camera_pool,
// 	       malloc(size*64),
// 	       size*64,
// 	       size);
// }
// 
// int game_create_window(struct game* _self) {
//   SDL_Window *mainwindow; /* Our window handle */
//     SDL_GLContext maincontext; /* Our opengl context handle */
//  
//     if (SDL_Init(SDL_INIT_VIDEO) < 0) /* Initialize SDL's Video subsystem */
//         sdldie("Unable to initialize SDL"); /* Or die on error */
// 
//     SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
//     SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
//  
//     /* Turn on double buffering with a 24bit Z buffer.
//      * You may need to change this to 16 or 32 for your system */
//     SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
//     SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
//  
//     /* Create our window centered at 512x512 resolution */
//     mainwindow = SDL_CreateWindow("Nutty Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
//         512, 512, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
//     if (!mainwindow) /* Die if creation failed */
//         sdldie("Unable to create window");
//  
//     checkSDLError(__LINE__);
//     /* Create our opengl context and attach it to our window */
//     maincontext = SDL_GL_CreateContext(mainwindow);
//     checkSDLError(__LINE__);
//     /* This makes our buffer swap syncronized with the monitor's vertical refresh */
//     SDL_GL_SetSwapInterval(1);
// }
// 
// int main(int argc, char **argv) {
//   struct game* game;
//   game = malloc(sizeof(struct game));
//   if(!game_create_pools(game)) { exit(1); }
//   if(!game_create_window(game)) { exit(1); }
//   
//     //create scene
//  
//     
//     
//     
//     
//     /* Swap our back buffer to the front */
//     SDL_GL_SwapWindow(mainwindow);
//     /* Wait 2 seconds */
//     SDL_Delay(2000);
//     SDL_Quit();
// }
// 
// int frame(float _elapsed) {
//   if(_scene.changed) {
//     while(1) {
//       if(_scene.root_object.changed) {
// 	//update GPU buffer
//       }//modify gpu buffer
//     }
//   }
//   step_anim(_elapsed);
// }

#include "engine.h"
#include <stdio.h>

int main() {
  struct engine* engine;
  if(!engine_init(engine, "Nutty Engine Test")) {
    printf("engine init fail\n");
  }
  while(engine_frame(engine, .3f));
}
