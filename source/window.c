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

#include "log.h"
#include "render_target.h"
#include "render/framebuffer.h"

#include "window.h"

void event_window_resized(GLFWwindow* _glfw_win, int _width, int _height);
void event_window_closed(GLFWwindow* _glfw_win);
void event_cursor_pos_changed(GLFWwindow* _glfw_win, double _x, double _y);
void event_key(GLFWwindow* _glfw_win, int _key, int _scancode, int _action, int _mod);

struct ngine_window* ngine_window_create(char* _win_name, char _fullscrean, int _width, int _height) {
  struct ngine_window* new_win = calloc(1, sizeof(struct ngine_window));
  
  new_win->render_target = ngine_render_target_create(0, 0, 0);
  new_win->render_target->fbuf = calloc(1, sizeof(struct ngine_framebuffer));
  new_win->render_target->fbuf->id = 0;
  new_win->render_target->fbuf->width = _width;
  new_win->render_target->fbuf->height = _height;
  
  new_win->listener = calloc(1, sizeof(struct window_listener));
  new_win->input_listener = calloc(1, sizeof(struct window_input_listener));
  
//   glfwWindowHint(GLFW_SAMPLES, 4);
//   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
//   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
//   glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);

  GLFWmonitor* monitor = 0;
  if(_fullscrean) {
    monitor = glfwGetPrimaryMonitor();
  }
  new_win->win = glfwCreateWindow(_width, _height, _win_name, monitor, NULL);
  if(!new_win->win) {
    error("cannot create window '%s'", _win_name);
    return NULL;
  }
  
  glfwSetWindowUserPointer(new_win->win, new_win);
  glfwSetWindowCloseCallback(new_win->win, event_window_closed);
  glfwSetWindowSizeCallback(new_win->win, event_window_resized);
  glfwSetKeyCallback(new_win->win, event_key);
//   glfwSetCursorEnterCallback();
  glfwSetCursorPosCallback(new_win->win, event_cursor_pos_changed);
//   glfwSetMouseButtonCallback();
  
  glfwMakeContextCurrent(new_win->win);
  
  return new_win;
}

int ngine_window_destroy(struct ngine_window* _win) {
  _win->listener->on_close();
}

// window events calbacks
void event_window_resized(GLFWwindow* _glfw_win, int _width, int _height) {
  struct ngine_window* win = glfwGetWindowUserPointer(_glfw_win);
//   win->listener->on_resize(win->input_listener->user_data);
}
void event_window_closed(GLFWwindow* _glfw_win) {
  struct ngine_window* win = glfwGetWindowUserPointer(_glfw_win);
  win->listener->on_close(win->input_listener->user_data);
}
void event_cursor_pos_changed(GLFWwindow* _glfw_win, double _x, double _y) {
  struct ngine_window* win = glfwGetWindowUserPointer(_glfw_win);
  if(win->input_listener->on_mouse_move) {
    win->input_listener->on_mouse_move(win->input_listener->user_data, win, _x, _y);
  }
}
void event_key(GLFWwindow* _glfw_win, int _key, int _scancode, int _action, int _mod) {
  struct ngine_window* win = glfwGetWindowUserPointer(_glfw_win);
  if(_action == GLFW_PRESS) {
    if(win->input_listener->on_key_pressed) {
      win->input_listener->on_key_pressed(win->input_listener->user_data, _key);
    }
  } else if(_action == GLFW_RELEASE) {
    if(win->input_listener->on_key_relased) {
      win->input_listener->on_key_relased(win->input_listener->user_data, _key);
    }
  }
}

//TODO use own input system
