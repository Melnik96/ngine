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

struct window* window_create(char* _win_name, int _width, int _height) {
  struct window* new_win = calloc(1, sizeof(struct window));
  
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
//   glewExperimental = GL_TRUE;
//   GLenum glew_err = glewInit();
//   if (glew_err != GLEW_OK) {
// 	// a problem occured when trying to init glew, report it:
// 	printf("GLEW Error occured, Description: %s\n", glewGetErrorString(glew_err));
// 	glfwDestroyWindow(newWindow->m_pWindow);
// 	delete newWindow;
// 	return NULL;
//   }
  // устанавливаем вьюпорт на все окно
  glViewport(0, 0, 640, 480);

//         // параметры OpenGL
        glClearColor(.4f, 0.2f, 0.0f, 1.0f);
        glClearDepth(1.0f);
//         glEnable(GL_DEPTH_TEST);
// 	glDepthFunc(GL_LESS); 
//         glEnable(GL_CULL_FACE);

  return new_win;
}

int window_destroy(struct window* _win) {
  _win->listener->on_close();
}

// window events calbacks
void event_window_resized(GLFWwindow* _glfw_win, int _width, int _height) {
  struct window* win = glfwGetWindowUserPointer(_glfw_win);
  win->listener->on_resize();
}
void event_window_closed(GLFWwindow* _glfw_win) {
  struct window* win = glfwGetWindowUserPointer(_glfw_win);
  win->listener->on_close();
}
void event_cursor_pos_changed(GLFWwindow* _glfw_win, double _x, double _y) {
  struct window* win = glfwGetWindowUserPointer(_glfw_win);
  if(win->input_listener->on_mouse_move) {
    win->input_listener->on_mouse_move(_x, _y);
  }
}
void event_key(GLFWwindow* _glfw_win, int _key, int _scancode, int _action, int _mod) {
  struct window* win = glfwGetWindowUserPointer(_glfw_win);
  if(_action == GLFW_PRESS) {
    if(win->input_listener->on_key_pressed) {
      win->input_listener->on_key_pressed(_key);
    }
  } else {
    if(win->input_listener->on_key_relased) {
      win->input_listener->on_key_relased(_key);
    }
  }
}

//TODO use own input system
