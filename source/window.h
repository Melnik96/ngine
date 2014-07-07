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

#ifndef WINDOW_H
#define WINDOW_H

struct monitor {
  
};

struct window_listener {
  void(*on_resize)();
  void(*on_close)();
  void(*on_change_pos)();
};

struct window_input_listener {
  void(*on_key_pressed)(void* _user, int _key);
  void(*on_key_relased)(void* _user, int _key);
  void(*on_mouse_move)(void* _user, double x, double y);
  void* user_data;
};

struct ngine_window {
  struct GLFWwindow* win;
  struct viewport*   viewport;
  
  struct window_listener* listener;
  struct window_input_listener* input_listener;
};

struct ngine_window* 	ngine_window_create(char* _win_name, int _width, int _height);
int 			ngine_window_destroy(struct ngine_window* _win);

#endif // WINDOW_H
