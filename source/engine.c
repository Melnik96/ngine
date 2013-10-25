/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2013  <copyright holder> <email>
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

#include <stdio.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

#include "engine.h"
int engine_init(struct engine* _self, char* _win_name) {
  //init GL
  // Initialise GLFW
  if(!glfwInit())
    return -1;
  /* Create a windowed mode window and its OpenGL context */
  _self->window = glfwCreateWindow(640, 480, _win_name, NULL, NULL);
  if(!_self->window) {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(_self->window);
  return 1;
}

int engine_frame(struct engine* _self, float _elapsed) {
  if(glfwWindowShouldClose(_self->window)) { engine_shutdown(_self); }
  /* Render here */

  glfwSwapBuffers(_self->window);
  glfwPollEvents();
  return 1;
}

int engine_shutdown(struct engine* _self) {
  glfwTerminate();
}
