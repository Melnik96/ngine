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

#ifndef WIDGET_H
#define WIDGET_H

#include "math/vector.h"

typedef void(*ngine_gui_activate_cb_t)(struct ngine_gui_widget* _widget);
typedef void(*ngine_gui_deactivate_cb_t)(struct ngine_gui_widget* _widget);
typedef void(*ngine_gui_pointer_move_cb_t)(struct ngine_gui_widget* _widget, struct ngine_gui_pointer _pointer, float _x, float _y);
typedef void(*ngine_gui_btn_press_cb_t)(struct ngine_gui_widget* _widget);
typedef void(*ngine_gui_btn_relase_cb_t)(struct ngine_gui_widget* _widget);
typedef void(*ngine_gui_key_press_cb_t)(struct ngine_gui_widget* _widget);
typedef void(*ngine_gui_key_relase_cb_t)(struct ngine_gui_widget* _widget);

struct ngine_gui_widget;

struct ngine_gui_widget* 	ngine_gui_widget_create();
void 				ngine_gui_widget_delete(struct ngine_gui_widget* _self);

void 				ngine_gui_widget_update(struct ngine_gui_widget* _self); // rebuild mesh by width and height

void 				ngine_gui_widget_add_child(struct ngine_gui_widget* _self, struct ngine_gui_widget* _child);
void 				ngine_gui_widget_remove_child(struct ngine_gui_widget* _self, struct ngine_gui_widget* _child);

struct ngine_sc_node* 		ngine_gui_widget_get_sc_node(struct ngine_gui_widget* _self);

void 				ngine_gui_widget_set_layer(struct ngine_gui_widget* _self, uint8_t _layer);
uint8_t 			ngine_gui_widget_get_layer(struct ngine_gui_widget* _self);

void 				ngine_gui_widget_set_pos(struct ngine_gui_widget* _self, float _x, float _y);
void 				ngine_gui_widget_set_size(struct ngine_gui_widget* _self, float _width, float _height);
vec2 				ngine_gui_widget_get_pos(struct ngine_gui_widget* _self);
vec2 				ngine_gui_widget_get_size(struct ngine_gui_widget* _self);

void 				ngine_gui_widget_set_width(struct ngine_gui_widget* _self, float _width);
void 				ngine_gui_widget_set_height(struct ngine_gui_widget* _self, float _height);
float 				ngine_gui_widget_get_width(struct ngine_gui_widget* _self);
float 				ngine_gui_widget_get_height(struct ngine_gui_widget* _self);

void 				ngine_gui_widget_add_activate_cb(struct ngine_gui_widget* _self, ngine_gui_activate_cb_t _cb);
void 				ngine_gui_widget_add_deactivate_cb(struct ngine_gui_widget* _self, ngine_gui_deactivate_cb_t _cb);
void 				ngine_gui_widget_add_pointer_move_cb(struct ngine_gui_widget* _self, ngine_gui_pointer_move_cb_t _cb);
void 				ngine_gui_widget_add_btn_press_cb(struct ngine_gui_widget* _self, ngine_gui_btn_press_cb_t _cb);
void 				ngine_gui_widget_add_btn_release_cb(struct ngine_gui_widget* _self, ngine_gui_btn_relase_cb_t _cb);
void 				ngine_gui_widget_add_key_press_cb(struct ngine_gui_widget* _self, ngine_gui_key_press_cb_t _cb);
void 				ngine_gui_widget_add_key_release_cb(struct ngine_gui_widget* _self, ngine_gui_key_relase_cb_t _cb);

void 				ngine_gui_widget_remove_activate_cb(struct ngine_gui_widget* _self, ngine_gui_activate_cb_t _cb);
void 				ngine_gui_widget_remove_deactivate_cb(struct ngine_gui_widget* _self, ngine_gui_deactivate_cb_t _cb);
void 				ngine_gui_widget_remove_pointer_move_cb(struct ngine_gui_widget* _self, ngine_gui_pointer_move_cb_t _cb);
void 				ngine_gui_widget_remove_btn_press_cb(struct ngine_gui_widget* _self, ngine_gui_btn_press_cb_t _cb);
void 				ngine_gui_widget_remove_btn_release_cb(struct ngine_gui_widget* _self, ngine_gui_btn_relase_cb_t _cb);
void 				ngine_gui_widget_remove_key_press_cb(struct ngine_gui_widget* _self, ngine_gui_key_press_cb_t _cb);
void 				ngine_gui_widget_remove_key_release_cb(struct ngine_gui_widget* _self, ngine_gui_key_relase_cb_t _cb);

#endif // WIDGET_H
