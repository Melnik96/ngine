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
#include "scene.h"
#include "viewport.h"
#include "camera.h"
#include "entity.h"
#include "mesh.h"
#include "math.h"
#include "sc_obj.h"
#include <stdio.h>
#include <malloc.h>

#include <GL/gl.h>

vec4 Vertices[] =
{
    { { 0.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } },
    // Top
    { { -0.2f, 0.8f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
    { { 0.2f, 0.8f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
    { { 0.0f, 0.8f, 0.0f, 1.0f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
    { { 0.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
    // Bottom
    { { -0.2f, -0.8f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
    { { 0.2f, -0.8f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
    { { 0.0f, -0.8f, 0.0f, 1.0f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
    { { 0.0f, -1.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
    // Left
    { { -0.8f, -0.2f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
    { { -0.8f, 0.2f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
    { { -0.8f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
    { { -1.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
    // Right
    { { 0.8f, -0.2f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
    { { 0.8f, 0.2f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
    { { 0.8f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
    { { 1.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } }
};
unsigned char Indices[] = {
    // Top
    0, 1, 3,
    0, 3, 2,
    3, 1, 4,
    3, 4, 2,
    // Bottom
    0, 5, 7,
    0, 7, 6,
    7, 5, 8,
    7, 8, 6,
    // Left
    0, 9, 11,
    0, 11, 10,
    11, 9, 12,
    11, 12, 10,
    // Right
    0, 13, 15,
    0, 15, 14,
    15, 13, 16,
    15, 16, 14
};


int main() {
  struct engine* engine;
  engine = malloc(sizeof(struct engine));
  if(!neng_init(engine, "Nutty Engine Test")) {
    printf("engine init fail\n");
  }
  //create scene
  //  create objects
  //  set viewport and camera
  struct scene* sc = scene_create("scene0", 1);
  engine->scenes = sc;
  
  struct sc_obj* sc_cam0 = sc_obj_create("cam0", "camera");
  struct sc_obj* sc_obj0 = sc_obj_create("obj0", "entity");
  
  struct camera* cam0 = malloc(sizeof(struct camera));
  struct entity* ent0 = malloc(sizeof(struct entity));
  
  struct mesh* mesh0 = malloc(sizeof(struct mesh));
  mesh0->num_vertices = 9;
  mesh0->num_indices = 3;
  mesh0->vertices = &Vertices;
  mesh0->indices = &Indices;
  
  ent0->meshes;
  
  sc_cam0->typed_obj = cam0;
  sc_obj0->typed_obj = ent0;
  
  sc_obj_add_child(sc->root_object, sc_cam0);
  sc_obj_add_child(sc->root_object, sc_obj0);
  
  while(neng_frame(engine, .3f));
  neng_shutdown(engine);
}
