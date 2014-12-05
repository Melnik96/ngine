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

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <malloc.h>

#include "window.h"

void event_window_resized(GLFWwindow* _glfw_win, int _width, int _height);
void event_window_closed(GLFWwindow* _glfw_win);
void event_cursor_pos_changed(GLFWwindow* _glfw_win, double _x, double _y);
void event_key(GLFWwindow* _glfw_win, int _key, int _scancode, int _action, int _mod);

struct ngine_window* ngine_window_create(char* _win_name, char _fullscrean, int _width, int _height) {
  struct ngine_window* new_win = calloc(1, sizeof(struct ngine_window));
  
//   new_win->listener = calloc(1, sizeof(struct window_listener));
  new_win->input_listener = calloc(1, sizeof(struct window_input_listener));
  
//   glfwWindowHint(GLFW_SAMPLES, 4);
//   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
//   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
//   glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

  GLFWmonitor* monitor = 0;
  if(_fullscrean) {
    monitor = glfwGetPrimaryMonitor();
  }
  GLFWwindow* glfw_win = glfwCreateWindow(_width, _height, _win_name, monitor, NULL);
  if(!glfw_win) {
    error("cannot create window '%s'", _win_name);
    return NULL;
  }
  
  glfwSetWindowUserPointer(glfw_win, new_win);
//   glfwSetWindowCloseCallback(glfw_win, event_window_closed);
//   glfwSetWindowSizeCallback(glfw_win, event_window_resized);
//   glfwSetInputMode(glfw_win, GLFW_STICKY_KEYS, GL_TRUE);
  glfwSetKeyCallback(glfw_win, event_key);
//   glfwSetCursorEnterCallback();
//   glfwSetCursorPosCallback(glfw_win, event_cursor_pos_changed);
//   glfwSetMouseButtonCallback();
  
  glfwMakeContextCurrent(glfw_win);
  
  new_win->native_win = glfw_win;
  
  return new_win;
}

int window_delete(struct ngine_window* _self) {
//   _self->listener->on_close();
}

// window events calbacks
// void event_window_resized(GLFWwindow* _glfw_win, int _width, int _height) {
//   struct window* win = glfwGetWindowUserPointer(_glfw_win);
//   win->listener->on_resize();
// }
// void event_window_closed(GLFWwindow* _glfw_win) {
//   struct window* win = glfwGetWindowUserPointer(_glfw_win);
//   win->listener->on_close();
// }
// void event_cursor_pos_changed(GLFWwindow* _glfw_win, double _x, double _y) {
//   struct window* win = glfwGetWindowUserPointer(_glfw_win);
//   if(win->input_listener->on_mouse_move) {
//     win->input_listener->on_mouse_move(_x, _y);
//   }
// }
void event_key(GLFWwindow* _glfw_win, int _key, int _scancode, int _action, int _mod) {
  
  struct ngine_window* win = glfwGetWindowUserPointer(_glfw_win);
  if(_action == GLFW_PRESS) {
    if(win->input_listener->key_cb) {
      win->input_listener->key_cb(win->input_listener->user_data, _key, 1);
    }
  } else if(_action == GLFW_RELEASE) {
    if(win->input_listener->key_cb) {
      win->input_listener->key_cb(win->input_listener->user_data, _key, 0);
    }
  }
}

//TODO use own input system
