#include "ngine.h"

#include "render_target.h"

#include "scene.h"
#include "sc_obj.h"
#include "entity.h"
#include "camera.h"
#include "mesh.h"
#include "material.h"
#include "texture.h"

// #include "import/collada/daeu.h"
#include "import/obj/obj.h"

#include "sound_mgr.h"
#include <fmodex/fmod.h>

#include "log.h"
#include "node.h"
#include "iohand/input.h"
#include <window.h>

#include <stdlib.h>
#include <math.h>
#include <kazmath/vec3.h>
#include <kazmath/quaternion.h>
#include <kazmath/mat4.h>
#include <assert.h>
#include <GLFW/glfw3.h>

#define deg2rad(x) (float)(((x) * M_PI / 180.0f))
#define rad2deg(x) (float)(((x) * 180.0f / M_PI))

void cam_rot(struct ngine_window* win, struct ngine_sc_node* _node, double _x, double _y);
void move_forward(struct ngine_sc_node* _sc_node);
void move_backward(struct ngine_sc_node* _sc_node);
void move_left(struct ngine_sc_node* _sc_node);
void move_right(struct ngine_sc_node* _sc_node);
void move_none(struct ngine_sc_node* _sc_node);

// fov
void foving_inc(struct ngine_sc_node* _sc_node, float _time);
void foving_dec(struct ngine_sc_node* _sc_node, float _time);
void fov_inc(struct ngine_sc_node* _sc_node);
void fov_dec(struct ngine_sc_node* _sc_node);
void fov_none(struct ngine_sc_node* _sc_node);

void moveing_forward(struct ngine_sc_node* _sc_node, float _time);
void moveing_backward(struct ngine_sc_node* _sc_node, float _time);
void moveing_left(struct ngine_sc_node* _sc_node, float _time);
void moveing_right(struct ngine_sc_node* _sc_node, float _time);

void node_rotation(struct ngine_sc_node* _sc_node, float _time);

struct ngine_scene* create_scene(struct ngine* _ngine) {
  struct ngine_scene* nscene = ngine_scene_create("neditor", 0, 1);
  debug("scene 'neditor' created");
  
  struct ngine_sc_node* node_cam = ngine_sc_node_create(nscene, "camera", NGINE_SC_OBJ_CAMERA);
  node_cam->attached_obj = ngine_camera_create(90.0, 0.1, 100.0);
  node_cam->pos.z = 0.5;
  node_cam->pos.x = 0;
  node_cam->pos.y = 0;
  tree_add_child((struct tree*)nscene->root_object, (struct tree*)node_cam);
  
  _ngine->rend_target = ngine_render_target_create(node_cam, 640, 480);
  
  ngine_input_bind_mouse_move(_ngine->input, node_cam, cam_rot);
  ngine_input_bind_key(_ngine->input, GLFW_KEY_W, 1, node_cam, move_forward);
  ngine_input_bind_key(_ngine->input, GLFW_KEY_S, 1, node_cam, move_backward);
  ngine_input_bind_key(_ngine->input, GLFW_KEY_A, 1, node_cam, move_left);
  ngine_input_bind_key(_ngine->input, GLFW_KEY_D, 1, node_cam, move_right);
  ngine_input_bind_key(_ngine->input, GLFW_KEY_W, 0, node_cam, move_none);
  ngine_input_bind_key(_ngine->input, GLFW_KEY_S, 0, node_cam, move_none);
  ngine_input_bind_key(_ngine->input, GLFW_KEY_A, 0, node_cam, move_none);
  ngine_input_bind_key(_ngine->input, GLFW_KEY_D, 0, node_cam, move_none);
  
  // fov
  ngine_input_bind_key(_ngine->input, GLFW_KEY_N, 1, node_cam, fov_inc);
  ngine_input_bind_key(_ngine->input, GLFW_KEY_M, 1, node_cam, fov_dec);
  ngine_input_bind_key(_ngine->input, GLFW_KEY_N, 0, node_cam, fov_none);
  ngine_input_bind_key(_ngine->input, GLFW_KEY_M, 0, node_cam, fov_none);
  
{ 
  struct ngine_mesh* mesh_suzy = ngine_mesh_import_obj("media/models/cube.obj");
//   ngine_texture_image(mesh_suzy->chunk->mtl->tex_color, "media/textures/mapgrid.tga");
  mesh_suzy->chunk->mtl = ngine_material_create();
  mesh_suzy->chunk->mtl->tex_color = ngine_texture_create(0);
  ngine_texture_image(mesh_suzy->chunk->mtl->tex_color, "media/textures/mapgrid.tga");
  ngine_mesh_update(mesh_suzy);
  
  struct ngine_entity* ent_suzy = ngine_entity_create("sphere", mesh_suzy);
  struct ngine_sc_node* node_suzy = ngine_sc_node_create(nscene, "suzanne", NGINE_SC_OBJ_ENTITY);
  
  node_suzy->attached_obj = (struct list*)ent_suzy;
  node_suzy->pos.x = -2.0;
  node_suzy->pos.y = -0.0;
  node_suzy->pos.z = -4.0;
  kmQuaternionRotationPitchYawRoll(&node_suzy->orient, 0, deg2rad(0), 0);
//   node_suzy->orient = (quat){0, 0, 1, 0.9};
  
  tree_add_child((struct tree*)nscene->root_object, (struct tree*)node_suzy);
  
  node_suzy->listener->on_update = node_rotation;

{
  struct ngine_mesh* mesh_suzy2 = ngine_mesh_import_obj("media/models/suzanne.obj");
//   ngine_texture_image(mesh_suzy2->chunk->mtl->tex_color, "media/textures/mapgrid.tga");
  mesh_suzy2->chunk->mtl = ngine_material_create();
  mesh_suzy2->chunk->mtl->tex_color = ngine_texture_create(0);
  ngine_texture_image(mesh_suzy2->chunk->mtl->tex_color, "media/textures/mapgrid.tga");
  ngine_mesh_update(mesh_suzy2);
  
  struct ngine_entity* ent_suzy2 = ngine_entity_create("sphere", mesh_suzy2);
  struct ngine_sc_node* node_suzy2 = ngine_sc_node_create(nscene, "suzanne", NGINE_SC_OBJ_ENTITY);
  
  node_suzy2->attached_obj = (struct list*)ent_suzy2;
  node_suzy2->pos.x = -2.0;
  node_suzy2->pos.y = -2.0;
  node_suzy2->pos.z = -2.0;
  kmQuaternionRotationPitchYawRoll(&node_suzy2->orient, 0, deg2rad(0), 0);
//   node_suzy->orient = (quat){0, 0, 1, 0.9};
  
  tree_add_child((struct tree*)node_suzy, (struct tree*)node_suzy2);
  
  node_suzy2->listener->on_update = node_rotation;
}{
  struct ngine_mesh* mesh_suzy2 = ngine_mesh_import_obj("media/models/suzanne.obj");
//   ngine_texture_image(mesh_suzy2->chunk->mtl->tex_color, "media/textures/mapgrid.tga");
  mesh_suzy2->chunk->mtl = ngine_material_create();
  mesh_suzy2->chunk->mtl->tex_color = ngine_texture_create(0);
  ngine_texture_image(mesh_suzy2->chunk->mtl->tex_color, "media/textures/mapgrid.tga");
  ngine_mesh_update(mesh_suzy2);
  
  struct ngine_entity* ent_suzy2 = ngine_entity_create("sphere", mesh_suzy2);
  struct ngine_sc_node* node_suzy2 = ngine_sc_node_create(nscene, "suzanne", NGINE_SC_OBJ_ENTITY);
  
  node_suzy2->attached_obj = (struct list*)ent_suzy2;
  node_suzy2->pos.x = -0.0;
  node_suzy2->pos.y = -2.0;
  node_suzy2->pos.z = 2.0;
  kmQuaternionRotationPitchYawRoll(&node_suzy2->orient, 0, deg2rad(0), 0);
//   node_suzy->orient = (quat){0, 0, 1, 0.9};
  
  tree_add_child((struct tree*)node_suzy, (struct tree*)node_suzy2);
  
  node_suzy2->listener->on_update = node_rotation;
}{
  struct ngine_mesh* mesh_suzy2 = ngine_mesh_import_obj("media/models/suzanne.obj");
//   ngine_texture_image(mesh_suzy2->chunk->mtl->tex_color, "media/textures/mapgrid.tga");
  mesh_suzy2->chunk->mtl = ngine_material_create();
  mesh_suzy2->chunk->mtl->tex_color = ngine_texture_create(0);
  ngine_texture_image(mesh_suzy2->chunk->mtl->tex_color, "media/textures/mapgrid.tga");
  ngine_mesh_update(mesh_suzy2);
  
  struct ngine_entity* ent_suzy2 = ngine_entity_create("sphere", mesh_suzy2);
  struct ngine_sc_node* node_suzy2 = ngine_sc_node_create(nscene, "suzanne", NGINE_SC_OBJ_ENTITY);
  
  node_suzy2->attached_obj = (struct list*)ent_suzy2;
  node_suzy2->pos.x = 2.0;
  node_suzy2->pos.y = -2.0;
  node_suzy2->pos.z = -2.0;
  kmQuaternionRotationPitchYawRoll(&node_suzy2->orient, 0, deg2rad(0), 0);
//   node_suzy->orient = (quat){0, 0, 1, 0.9};
  
  tree_add_child((struct tree*)node_suzy, (struct tree*)node_suzy2);
  
  node_suzy2->listener->on_update = node_rotation;
}
}
// {
//   struct ngine_mesh* mesh_suzy = ngine_mesh_import_obj("media/models/suzanne.obj");
// //   ngine_texture_image(mesh_suzy->chunk->mtl->tex_color, "media/textures/mapgrid.tga");
//   ngine_mesh_update(mesh_suzy);
//   
//   struct ngine_entity* ent_suzy = ngine_entity_create("sphere", mesh_suzy);
//   struct ngine_sc_node* node_suzy = ngine_sc_node_create(nscene, "suzanne", NGINE_SC_OBJ_ENTITY);
//   
//   node_suzy->attached_obj = (struct list*)ent_suzy;
//   node_suzy->pos.x = 2.0;
//   node_suzy->pos.y = 0.0;
//   node_suzy->pos.z = -4.0;
//   kmQuaternionRotationPitchYawRoll(&node_suzy->orient, 0, deg2rad(0), 0);
// //   node_suzy->orient = (quat){0, 0, 1, 0.9};
//   
//   tree_add_child((struct tree*)nscene->root_object, (struct tree*)node_suzy);
// }

//   ngine_input_bind_key(_ngine->input, GLFW_KEY_F11, 1, &1, ngine_window_fullscrean);
  ngine_input_bind_key(_ngine->input, GLFW_KEY_ESCAPE, 1, 0, exit);

  return nscene;
}

void print_win_closed() {
  debug("event: window closed");
//   ngine_shutdown();
  exit(0);
}

// float lx=0, ly=0;
float cx=0, cy=0;
void cam_rot(struct ngine_window* win, struct ngine_sc_node* _node, double _x, double _y) {
  cx += deg2rad(_x*-0.1 - (640/2)*-0.1);
  cy += deg2rad(_y*-0.1 - (480/2)*-0.1);
  
  kmQuaternionRotationPitchYawRoll(&_node->orient, cy, cx, 0.);
  
//   printf("last x: %f y: %f\n", _x, _y);
  
  glfwSetCursorPos(win->win, 640/2, 480/2);
}

// key_callback
void move_forward(struct ngine_sc_node* _sc_node) {
  _sc_node->listener->on_update = moveing_forward;
}
void move_backward(struct ngine_sc_node* _sc_node) {
  _sc_node->listener->on_update = moveing_backward;
}
void move_left(struct ngine_sc_node* _sc_node) {
  _sc_node->listener->on_update = moveing_left;
}
void move_right(struct ngine_sc_node* _sc_node) {
  _sc_node->listener->on_update = moveing_right;
}
void move_none(struct ngine_sc_node* _sc_node) {
  _sc_node->listener->on_update = NULL;
}
// sc_node->on_update
void moveing_forward(struct ngine_sc_node* _sc_node, float _time) {
  _sc_node->pos.z -= 0.05;
}
void moveing_backward(struct ngine_sc_node* _sc_node, float _time) {
  _sc_node->pos.z += 0.05;
}
void moveing_left(struct ngine_sc_node* _sc_node, float _time) {
  _sc_node->pos.x -= 0.05;
}
void moveing_right(struct ngine_sc_node* _sc_node, float _time) {
  _sc_node->pos.x += 0.05;
}

float cur_yaw = 0;
void node_rotation(struct ngine_sc_node* _sc_node, float _time) {
//   printf("time: %f\n", _time);
//   cur_yaw *= 1.01;
  cur_yaw += deg2rad(15*0.1);
  if(cur_yaw >= 2*M_PI) {
    cur_yaw -= 2*M_PI;
  }
  kmQuaternionRotationPitchYawRoll(
    &_sc_node->orient,
    0, cur_yaw, 0.0
  );
}

void fov_inc(struct ngine_sc_node* _sc_node) {
  _sc_node->listener->on_update = foving_inc;
}
void fov_dec(struct ngine_sc_node* _sc_node) {
  _sc_node->listener->on_update = foving_dec;
}
void fov_none(struct ngine_sc_node* _sc_node) {
  _sc_node->listener->on_update = NULL;
}
void foving_inc(struct ngine_sc_node* _sc_node, float _time) {
  ((struct ngine_camera*)_sc_node->attached_obj)->fov += _time*100;
  printf("fov: %f\n", ((struct ngine_camera*)_sc_node->attached_obj)->fov);
}
void foving_dec(struct ngine_sc_node* _sc_node, float _time) {
  ((struct ngine_camera*)_sc_node->attached_obj)->fov -= _time*100;
  printf("fov: %f\n", ((struct ngine_camera*)_sc_node->attached_obj)->fov);
}
