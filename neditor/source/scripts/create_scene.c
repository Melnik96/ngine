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
#include "import/asmp/asmp.h"

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

// set velocity
void vel_forward(struct ngine_sc_node* _sc_node);
void vel_backward(struct ngine_sc_node* _sc_node);
void vel_left(struct ngine_sc_node* _sc_node);
void vel_right(struct ngine_sc_node* _sc_node);
void vel_none(struct ngine_sc_node* _sc_node);

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
  struct ngine_scene* nscene = ngine_scene_create("neditor", 1, 1);
  debug("scene 'neditor' created");
  
  
  struct ngine_sc_node* node_cam = ngine_sc_node_create(nscene, "camera", NGINE_SC_OBJ_CAMERA);
  node_cam->attached_obj = ngine_camera_create(45.0, 0.1, 1000.0);
  node_cam->pos.z = 0.5;
  node_cam->pos.x = 0;
  node_cam->pos.y = 0;
  tree_add_child((struct tree*)nscene->root_object, (struct tree*)node_cam);
  
  _ngine->rend_target = ngine_render_target_create(node_cam, 1440, 900);
  
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
  
//   {
    ngine_scene_add_import_assimp(nscene, "media/models/test_scene.dae");
//   }
{ 
  struct ngine_mesh* mesh_suzy = ngine_mesh_import_obj("media/models/uv_test.obj");
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
}
// {
//   struct ngine_mesh* mesh_suzy = ngine_mesh_import_obj("media/models/suzanne.obj");
//   ngine_mesh_make_coll_shape(mesh_suzy, NGINE_SHAPE_GIMPACT);
//   ngine_mesh_update(mesh_suzy);
// //   ngine_texture_image(mesh_suzy->chunk->mtl->tex_color, "media/textures/mapgrid.tga");
//   
//   struct ngine_entity* ent_suzy = ngine_entity_create("sphere", mesh_suzy);
//   struct ngine_sc_node* node_suzy = ngine_sc_node_create(nscene, "suzanne", NGINE_SC_OBJ_ENTITY);
//   
//   node_suzy->attached_obj = (struct list*)ent_suzy;
//   node_suzy->pos.x = 2.9;
//   node_suzy->pos.y = 4.0;
//   node_suzy->pos.z = -4.0;
//   kmQuaternionRotationPitchYawRoll(&node_suzy->orient, 0, 0, deg2rad(45));
//   ngine_sc_node_make_dynamic(node_suzy, &(struct ngine_phys_info){10});
//   
//   tree_add_child((struct tree*)nscene->root_object, (struct tree*)node_suzy);
// }
// {
//   struct ngine_mesh* mesh_suzy = ngine_mesh_import_obj("media/models/MENU_LEVEL.obj");
//   ngine_mesh_make_coll_shape(mesh_suzy, NGINE_SHAPE_TRIMESH);
//   ngine_mesh_update(mesh_suzy);
// //   ngine_texture_image(mesh_suzy->chunk->mtl->tex_color, "media/textures/mapgrid.tga");
//   
//   struct ngine_entity* ent_suzy = ngine_entity_create("sphere", mesh_suzy);
//   struct ngine_sc_node* node_suzy = ngine_sc_node_create(nscene, "suzanne", NGINE_SC_OBJ_ENTITY);
//   
//   node_suzy->attached_obj = (struct list*)ent_suzy;
//   node_suzy->pos.x = 2.0;
//   node_suzy->pos.y = -4.0;
//   node_suzy->pos.z = -4.0;
//   kmQuaternionRotationPitchYawRoll(&node_suzy->orient, 0, deg2rad(0), 0);
//   ngine_sc_node_make_dynamic(node_suzy, &(struct ngine_phys_info){0});
//   
//   tree_add_child((struct tree*)nscene->root_object, (struct tree*)node_suzy);
// }
{
  struct ngine_mesh* mesh_suzy = ngine_mesh_import_obj("media/models/suzanne.obj");
//   ngine_mesh_make_coll_shape(mesh_suzy, NGINE_SHAPE_BOX);
//   ngine_texture_image(mesh_suzy->chunk->mtl->tex_color, "media/textures/mapgrid.tga");
  ngine_mesh_update(mesh_suzy);
  
  struct ngine_entity* ent_suzy = ngine_entity_create("sphere", mesh_suzy);
  struct ngine_sc_node* node_suzy = ngine_sc_node_create(nscene, "suzanne", NGINE_SC_OBJ_ENTITY);
  
  node_suzy->attached_obj = (struct list*)ent_suzy;
  node_suzy->pos.x = 3.0;
  node_suzy->pos.y = -1.5;
  node_suzy->pos.z = -4.0;
  kmQuaternionRotationPitchYawRoll(&node_suzy->orient, 0, deg2rad(-45), 0);
//   ngine_sc_node_make_dynamic(node_suzy, &(struct ngine_phys_info){10});
  
  tree_add_child((struct tree*)node_cam, (struct tree*)node_suzy);
}
{
  struct ngine_mesh* mesh_suzy = ngine_mesh_import_obj("media/models/suzanne.obj");
  ngine_mesh_make_coll_shape(mesh_suzy, NGINE_SHAPE_GIMPACT);
  ngine_mesh_update(mesh_suzy);
  mesh_suzy->chunk->mtl = ngine_material_create();
  mesh_suzy->chunk->mtl->tex_color = ngine_texture_create(0);
  ngine_texture_image(mesh_suzy->chunk->mtl->tex_color, "media/textures/floor.tga");
  
  struct ngine_entity* ent_suzy = ngine_entity_create("sphere", mesh_suzy);
  struct ngine_sc_node* node_suzy = ngine_sc_node_create(nscene, "suzanne", NGINE_SC_OBJ_ENTITY);
  
  node_suzy->attached_obj = (struct list*)ent_suzy;
  node_suzy->pos.x = 3.0;
  node_suzy->pos.y = -1.5;
  node_suzy->pos.z = -4.0;
//   kmQuaternionRotationPitchYawRoll(&node_suzy->orient, 0, deg2rad(-45), 0);
  node_suzy->orient.w = 1;
  ngine_sc_node_make_dynamic(node_suzy, &(struct ngine_phys_info){10});
  
  tree_add_child((struct tree*)nscene->root_object, (struct tree*)node_suzy);
  
  ngine_input_bind_key(_ngine->input, GLFW_KEY_UP, 1, node_suzy, vel_forward);
  ngine_input_bind_key(_ngine->input, GLFW_KEY_DOWN, 1, node_suzy, vel_backward);
  ngine_input_bind_key(_ngine->input, GLFW_KEY_LEFT, 1, node_suzy, vel_left);
  ngine_input_bind_key(_ngine->input, GLFW_KEY_RIGHT, 1, node_suzy, vel_right);
  ngine_input_bind_key(_ngine->input, GLFW_KEY_UP, 0, node_suzy, vel_none);
  ngine_input_bind_key(_ngine->input, GLFW_KEY_DOWN, 0, node_suzy, vel_none);
  ngine_input_bind_key(_ngine->input, GLFW_KEY_LEFT, 0, node_suzy, vel_none);
  ngine_input_bind_key(_ngine->input, GLFW_KEY_RIGHT, 0, node_suzy, vel_none);
}

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

// set velocity
void vel_forward(struct ngine_sc_node* _sc_node) {
  ngine_sc_node_set_lin_vel(_sc_node, &(vec3){0,0,-15}, NGINE_TRANS_LOCAL);
}
void vel_backward(struct ngine_sc_node* _sc_node) {
  ngine_sc_node_set_lin_vel(_sc_node, &(vec3){0,0,15}, NGINE_TRANS_LOCAL);
}
void vel_left(struct ngine_sc_node* _sc_node) {
  ngine_sc_node_set_lin_vel(_sc_node, &(vec3){-15,0,0}, NGINE_TRANS_LOCAL);
}
void vel_right(struct ngine_sc_node* _sc_node) {
  ngine_sc_node_set_lin_vel(_sc_node, &(vec3){15,0,0}, NGINE_TRANS_LOCAL);
}
void vel_none(struct ngine_sc_node* _sc_node) {
  ngine_sc_node_set_lin_vel(_sc_node, &(vec3){0,0,0}, NGINE_TRANS_LOCAL);
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
  ngine_sc_node_translate(_sc_node, &(vec3){0,0,-0.5}, NGINE_TRANS_LOCAL);
}
void moveing_backward(struct ngine_sc_node* _sc_node, float _time) {
  ngine_sc_node_translate(_sc_node, &(vec3){0,0,0.5}, NGINE_TRANS_LOCAL);
}
void moveing_left(struct ngine_sc_node* _sc_node, float _time) {
  ngine_sc_node_translate(_sc_node, &(vec3){-0.5,0,0}, NGINE_TRANS_LOCAL);
}
void moveing_right(struct ngine_sc_node* _sc_node, float _time) {
  ngine_sc_node_translate(_sc_node, &(vec3){0.5,0,0}, NGINE_TRANS_LOCAL);
}

float cur_yaw = 0;
void node_rotation(struct ngine_sc_node* _sc_node, float _time) {
//   printf("time: %f\n", _time);
//   cur_yaw *= 1.01;
  cur_yaw += deg2rad(180*_time);
  if(cur_yaw >= 2*M_PI) {
    cur_yaw -= 2*M_PI;
  }
//   quat q;
  kmQuaternionRotationPitchYawRoll(
    &_sc_node->orient,
    0, cur_yaw, 0.0
  );
//   ngine_sc_node_rotate(_sc_node, &q, NGINE_TRANS_LOCAL);
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
