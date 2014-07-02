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
  void(*on_key_pressed)(int _key);
  void(*on_key_relased)();
  void(*on_mouse_move)(double x, double y);
};

struct window {
  struct GLFWwindow* win;
  struct viewport*   viewport;
  
  struct window_listener* listener;
  struct window_input_listener* input_listener;
};

struct window*  window_create(char* _win_name, int _width, int _height);
int 		window_destroy(struct window* _win);

#endif // WINDOW_H
