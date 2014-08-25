#include <kazmath/mat4.h>

#include "render_target.h"
#include "scene.h"
#include "sc_node.h"
#include "camera.h"
#include "entity.h"

#include "mesh_prims.h"

#include "cntr/list.h"
#include <ngine.h>
#include <window.h>
#include "iohand/input.h"

#include "gui/bltile.h"

#include "gui_surf.h"

void on_activate() { printf("button active\n"); }
void on_deactivate() { printf("button deactive\n"); }

struct neditor_gui* neditor_guisurf_create(int _w, int _h) {
  struct neditor_gui* new_gui = malloc(sizeof(struct neditor_gui));
  
  new_gui->sc = ngine_scene_create("neditor gui", 0, 1);
  
  struct ngine_camera* gui_cam = ngine_camera_create();
  ngine_camera_orto(gui_cam, 0, _w, 0, _h);
  ngine_camera_nearfar(gui_cam, -1, 100.0);
  
  struct ngine_sc_node* gui_cam_node = ngine_sc_node_create(new_gui->sc, "gui_camera", NGINE_SC_OBJ_CAMERA);
  gui_cam_node->attached_obj = gui_cam;
  tree_add_child(new_gui->sc->root_object, gui_cam_node);
  
  new_gui->rt = ngine_render_target_create(gui_cam_node, 1024, 600);
  new_gui->rt->fbuf = ngine_intense()->windows->fbuf;
  
  ngine_gui_bltile_create(new_gui->sc);
  
  // create gui
  struct ngine_mesh* btn0_mesh = ngine_mesh_create_quad(0, 100, 0, 25);
  struct ngine_entity* btn0_ent = ngine_entity_create("button", btn0_mesh);
  struct ngine_sc_node* btn0_node = ngine_sc_node_create(new_gui->sc, "button: blabla", NGINE_SC_OBJ_ENTITY);
  btn0_node->attached_obj = btn0_ent;
  tree_add_child(new_gui->sc->root_object, btn0_node);
  
  ngine_sc_node_translate(btn0_node, &(vec3){25, 25, -1}, NGINE_TRANS_LOCAL);
  
  btn0_node->listener->on_active = on_activate;
  btn0_node->listener->on_deactive = on_deactivate;
  
//   ngine_input_bind_mouse_move(ngine_intense()->input, btn0_node, gui_cursor_move);
  
  return new_gui;
}
