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

#include "ngine.h"
#include "iohand/input.h"
#include "cntr/tree.h"
#include "scene.h"
#include "sc_node.h"
#include "entity.h"
#include "mesh.h"

#include "bltile.h"

void bltile_on_mouse_move(struct ngine_window*, struct ngine_gui_bltile* _bltile, double _x, double _y);
void bltile_on_key_pressed(struct ngine_gui_bltile* _bltile, int _key);
void bltile_on_key_relased(struct ngine_gui_bltile* _bltile, int _key);


struct ngine_gui_bltile* ngine_gui_bltile_create(struct ngine_scene* _scene) {
  struct ngine_gui_bltile* new_bltile = calloc(1, sizeof(struct ngine_gui_bltile));
  
  new_bltile->scene = _scene;
  
  struct ngine_input_key_listener* bltile_key_listener = malloc(sizeof(struct ngine_input_key_listener)); {
    bltile_key_listener->args = new_bltile;
    bltile_key_listener->on_key_pressed = bltile_on_key_pressed;
    bltile_key_listener->on_key_relased = bltile_on_key_relased;
  };
  
  ngine_input_bind_key_listener(ngine_intense()->input, bltile_key_listener);
  ngine_input_bind_mouse_move(ngine_intense()->input, new_bltile, bltile_on_mouse_move);
  
  
  // set per scene update(frame) handler
  
  return new_bltile;
}


struct obj_on_cursor_arg {
  struct ngine_gui_bltile* bltile;
  float _x;
  float _y;
};
void check_obj_on_cursor(struct ngine_sc_node* _sc_node, struct obj_on_cursor_arg* _args) {
  struct ngine_gui_bltile* bltile = _args->bltile;
  float x = _args->_x;
  float y = _args->_y;
  
  if(_sc_node->type == NGINE_SC_OBJ_ENTITY) {
    vec2 plane = ((struct ngine_entity*)_sc_node->attached_obj)->mesh->plane_size;
    
    if(x >= _sc_node->pos.x && x <= (_sc_node->pos.x+plane.x) &&
       y >= _sc_node->pos.x && y <= (_sc_node->pos.y+plane.y))
    {
      if(bltile->cur_active_node != _sc_node) {
	bltile->cur_active_node = _sc_node;
	if(_sc_node->listener->on_active) { _sc_node->listener->on_active(); }
      }
    } else if(bltile->cur_active_node == _sc_node) {
      if(bltile->cur_active_node && bltile->cur_active_node->listener->on_deactive) {
	bltile->cur_active_node->listener->on_deactive();
	bltile->cur_active_node = 0;
      }
    }
  }
}
void bltile_on_mouse_move(struct ngine_window* _win, struct ngine_gui_bltile* _bltile, double _x, double _y) {
  float x = _x;
  float y = 768 - _y;
  tree_for_each2(_bltile->scene->root_object, check_obj_on_cursor, &(struct obj_on_cursor_arg){_bltile, x, y});
}

void bltile_on_key_pressed(struct ngine_gui_bltile* _bltile, int _key) {
  printf("gui key = %c\n", _key);
  if(_bltile->cur_active_node && _bltile->cur_active_node->listener->on_key_pressed) {
    _bltile->cur_active_node->listener->on_key_pressed(_key);
  }
}
void bltile_on_key_relased(struct ngine_gui_bltile* _bltile, int _key) {
  if(_bltile->cur_active_node && _bltile->cur_active_node->listener->on_key_pressed) {
    _bltile->cur_active_node->listener->on_key_pressed(_key);
  }
}
