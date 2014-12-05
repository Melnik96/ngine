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

#include "glfw_window.h"

struct ngine_window* ngine_window_create(const char* _win_name, uint32_t _width, uint32_t _height) {
  struct ngine_window* new_win = calloc(1, sizeof(struct window));
  
  new_win->listener = calloc(1, sizeof(struct window_listener));
  new_win->input_listener = calloc(1, sizeof(struct window_input_listener));
  
//   glfwWindowHint(GLFW_SAMPLES, 4);
//   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
//   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
//   glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);

  new_win->win = glfwCreateWindow(_width, _height, _win_name, NULL, NULL);
  
  if(!new_win->win) {
    // error
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

  glViewport(0, 0, 640, 480);

//         // параметры OpenGL
        glClearColor(.4f, 0.2f, 0.0f, 1.0f);
        glClearDepth(1.0f);
//         glEnable(GL_DEPTH_TEST);
// 	glDepthFunc(GL_LESS);
//         glEnable(GL_CULL_FACE);

  return new_win;
}
