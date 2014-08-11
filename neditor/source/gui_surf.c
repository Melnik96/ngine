#include <kazmath/mat4.h>

#include "render_target.h"
#include "scene.h"
#include "sc_obj.h"
#include "camera.h"
#include "entity.h"

#include "mesh_prims.h"

#include "gui_surf.h"

struct neditor_gui* neditor_guisurf_create() {
  struct neditor_gui* new_gui = malloc(sizeof(struct neditor_gui));
  struct ngine_camera* gui_cam = ngine_camera_create();
  struct ngine_sc_node* gui_cam_node = ngine_sc_node_create(new_gui->sc, "gui_camera", NGINE_SC_OBJ_CAMERA);
  new_gui->rt = ngine_render_target_create(gui_cam_node, 1024, 600);
  new_gui->sc = ngine_scene_create("neditor gui", 0, 1);
  new_gui->rt->;
  
  // create gui
  struct ngine_mesh* btn0_mesh = ngine_mesh_create_quad(0, 100, 0, 25);
  struct ngine_entity* btn0_ent = ngine_entity_create("button", btn0_mesh);
  struct ngine_sc_node* btn0_node = ngine_sc_node_create(new_gui->sc, "button: blabla", NGINE_SC_OBJ_ENTITY);
}
