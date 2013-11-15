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

#include <GL/glew.h>
#include <GL/gl.h>

#include "shader_prog.h"

int shader_prog_init(struct shader_prog* _prog, const char* _name, char** _shaders) {
  _prog->prog  = glCreateProgram();
  if(_shaders[GLST_VERTEX]) {
    uint32_t vert_shad = glCreateShader(GL_VERTEX_SHADER);
//     glShaderSource(vert_shad, 1, (const GLchar**)&_shaders[GLST_VERTEX], (const GLint*)&sizeof(_shaders[GLST_VERTEX]));
    glCompileShader(vert_shad);
    
    if (ShaderStatus(vert_shad, GL_COMPILE_STATUS) != GL_TRUE)
        return 0;
    
    glAttachShader(_prog->prog, vert_shad);
    glLinkProgram(_prog->prog);
    
    if (ShaderProgramStatus(_prog->prog, GL_LINK_STATUS) != GL_TRUE)
        return 0;
  }
  else if(_shaders[GLST_FRAGMENT]) {
    _shaders[GLST_FRAGMENT] = glCreateShader(GL_FRAGMENT_SHADER);
  }
}

// проверка статуса param шейдера shader
GLint ShaderStatus(GLuint shader, GLenum param)
{
        GLint status, length;
        GLchar buffer[1024];

        // получим статус шейдера
        glGetShaderiv(shader, param, &status);

        // в случае ошибки запишем ее в лог-файл
//         if (status != GL_TRUE)
//         {
//                 glGetShaderInfoLog(shader, 1024, &length, buffer);
//                 LOG_ERROR("Shader: %s\n", (const char*)buffer);
//         }

        // проверим не было ли ошибок OpenGL
//         OPENGL_CHECK_FOR_ERRORS();

        // вернем статус
        return status;
}

// проверка статуса param шейдерной программы program
GLint ShaderProgramStatus(GLuint program, GLenum param)
{
        GLint status, length;
        GLchar buffer[1024];

        // получим статус шейдерной программы
        glGetProgramiv(program, param, &status);

        // в случае ошибки запишем ее в лог-файл
//         if (status != GL_TRUE)
//         {
//                 glGetProgramInfoLog(program, 1024, &length, buffer);
//                 LOG_ERROR("Shader program: %s\n", (const char*)buffer);
//         }
// 
//         // проверим не было ли ошибок OpenGL
//         OPENGL_CHECK_FOR_ERRORS();

        // вернем статус
        return status;
}
