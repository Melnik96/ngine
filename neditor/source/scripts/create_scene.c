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

void cam_rot(struct ngine_sc_node* _node, double _x, double _y);
void move_forward(struct ngine_sc_node* _sc_node);
void move_backward(struct ngine_sc_node* _sc_node);
void move_left(struct ngine_sc_node* _sc_node);
void move_right(struct ngine_sc_node* _sc_node);
void move_none(struct ngine_sc_node* _sc_node);

void moveing_forward(struct ngine_sc_node* _sc_node, float _time);
void moveing_backward(struct ngine_sc_node* _sc_node, float _time);
void moveing_left(struct ngine_sc_node* _sc_node, float _time);
void moveing_right(struct ngine_sc_node* _sc_node, float _time);

void node_rotation(struct ngine_sc_node* _sc_node, float _time);

struct scene* create_scene(struct ngine* _ngine) {
  struct scene* nscene = scene_create("neditor", 1);
  debug("scene 'neditor' created");
  
  struct ngine_sc_node* node_cam = ngine_sc_node_create("camera", NGINE_SC_OBJ_CAMERA);
  node_cam->attached_obj = ngine_camera_create(90.0, 0.1, 100.0);
  node_cam->pos.z = 0.5;
  node_cam->pos.x = 0;
  node_cam->pos.y = 0;
  tree_add_child((struct tree*)nscene->root_object, (struct tree*)node_cam);
  
  _ngine->rend_target = ngine_render_target_create(node_cam, 640, 480);
  
  ngine_input_bind_mouse_move(_ngine->input, node_cam, cam_rot);
  
{ 
  struct ngine_mesh* mesh_suzy = ngine_mesh_import_obj("media/models/cube.obj");
//   ngine_texture_image(mesh_suzy->chunk->mtl->tex_color, "media/textures/mapgrid.tga");
  mesh_suzy->chunk->mtl = ngine_material_create();
  mesh_suzy->chunk->mtl->tex_color = ngine_texture_create(0);
  ngine_texture_image(mesh_suzy->chunk->mtl->tex_color, "media/textures/mapgrid.tga");
  ngine_mesh_update(mesh_suzy);
  
  struct ngine_entity* ent_suzy = ngine_entity_create("sphere", mesh_suzy);
  struct ngine_sc_node* node_suzy = ngine_sc_node_create("suzanne", NGINE_SC_OBJ_ENTITY);
  
  node_suzy->attached_obj = (struct list*)ent_suzy;
  node_suzy->pos.x = -0.5;
  node_suzy->pos.y = -0.0;
  node_suzy->pos.z = -2.5;
  kmQuaternionRotationPitchYawRoll(&node_suzy->orient, 0, deg2rad(0), 0);
//   node_suzy->orient = (quat){0, 0, 1, 0.9};
  
  tree_add_child((struct tree*)nscene->root_object, (struct tree*)node_suzy);
  
  node_suzy->listener->on_update = node_rotation;
}
{
  struct ngine_mesh* mesh_suzy = ngine_mesh_import_obj("media/models/suzanne.obj");
//   ngine_texture_image(mesh_suzy->chunk->mtl->tex_color, "media/textures/mapgrid.tga");
  ngine_mesh_update(mesh_suzy);
  
  struct ngine_entity* ent_suzy = ngine_entity_create("sphere", mesh_suzy);
  struct ngine_sc_node* node_suzy = ngine_sc_node_create("suzanne", NGINE_SC_OBJ_ENTITY);
  
  node_suzy->attached_obj = (struct list*)ent_suzy;
  node_suzy->pos.x = 0.5;
  node_suzy->pos.y = -0.0;
  node_suzy->pos.z = -2.5;
  kmQuaternionRotationPitchYawRoll(&node_suzy->orient, 0, deg2rad(0), 0);
//   node_suzy->orient = (quat){0, 0, 1, 0.9};
  
  tree_add_child((struct tree*)nscene->root_object, (struct tree*)node_suzy);
  
  ngine_input_bind_key(_ngine->input, GLFW_KEY_W, 1, node_suzy, move_forward);
  ngine_input_bind_key(_ngine->input, GLFW_KEY_S, 1, node_suzy, move_backward);
  ngine_input_bind_key(_ngine->input, GLFW_KEY_A, 1, node_suzy, move_left);
  ngine_input_bind_key(_ngine->input, GLFW_KEY_D, 1, node_suzy, move_right);
  ngine_input_bind_key(_ngine->input, GLFW_KEY_W, 0, node_suzy, move_none);
  ngine_input_bind_key(_ngine->input, GLFW_KEY_S, 0, node_suzy, move_none);
  ngine_input_bind_key(_ngine->input, GLFW_KEY_A, 0, node_suzy, move_none);
  ngine_input_bind_key(_ngine->input, GLFW_KEY_D, 0, node_suzy, move_none);
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

int a = 1;
double last_x = 0;
double last_y = 0;
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
void cam_rot(struct ngine_sc_node* _node, double _x, double _y) {
  // Initial position : on +Z
vec3 position = (vec3){ 0, 0, 1 }; 
// Initial horizontal angle : toward -Z

float mouseSpeed = 0.005f;
  
	// Get mouse position
	double xpos = _x, ypos = _y;
// 	glfwGetCursorPos(window, &xpos, &ypos);

// 	// Reset mouse position for next frame
// 	glfwSetCursorPos(window, 640/2, 480/2);

	if(a == 1) {
	  last_x = _x/100;
	  last_y = _y/100;
	  a = 0;
	}
	// Compute new orientation
	horizontalAngle += /*mouseSpeed * */last_x - xpos/100;
	verticalAngle   += /*mouseSpeed * */last_y - ypos/100;
	last_x = _x/100;
	last_y = _y/100;

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	vec3 direction = (vec3){
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	};

	// Right vector
	vec3 right = (vec3){
		sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	};

	// Up vector
	vec3 up;
	kmVec3Cross(&up, &right, &direction);

	vec3* centr = malloc(sizeof(vec3));
	kmVec3Add(centr, &position,&direction);
	mat4 vmat;
	kmMat4LookAt(&vmat, &position, centr, &up);
	kmQuaternionRotationMatrix(&_node->orient, &vmat);
	
	printf("last x: %f y: %f\n", horizontalAngle, verticalAngle);
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

void node_rotation(struct ngine_sc_node* _sc_node, float _time) {
  float cur_yaw = 1*(float)asin(-2 * (_sc_node->orient.x * _sc_node->orient.z - _sc_node->orient.w * _sc_node->orient.y));
//   printf("cur_yaw: %f\n", cur_yaw);
//   printf("time: %f\n", _time);
//   cur_yaw *= 1.01;
  cur_yaw += deg2rad(100 * _time);
  if(cur_yaw >= 2*M_PI) {
    printf("cur_yaw -= 2*M_PI");
    cur_yaw -= 2*M_PI;
  }
  kmQuaternionRotationPitchYawRoll(
    &_sc_node->orient,
    0, cur_yaw, 0.9
  );
}
