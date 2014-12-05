/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2014  <copyright holder> <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "scenegraph/sc_node.h"
#include "scenegraph/entity.h"
#include "mesh/mesh_prims.h"

#include "button.h"

struct ngine_gui_button {
  struct ngine_gui_widget widget;
  char* text;
};

struct button* button_create(struct ngine_scene* _scene, const char* _name, float _w, float _h) {
  struct button new_button;
  new_button.sc_node = ngine_sc_node_create(_scene, "button", NGINE_SC_OBJ_ENTITY);
  new_button.sc_node->attached_obj = ngine_entity_create("button_entity", ngine_mesh_create_quad(0, _w, 0, _h));
  ngine_sc_node_add_intersect_cb(new_button.sc_node);
}
