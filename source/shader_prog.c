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

#include <string.h>
#include <pthread.h>

#include <GL/glew.h>
#include <GL/gl.h>

#include "shader_prog.h"

int shader_prog_init(struct shader_prog* _prog, const char* _name, struct shader_source* _sources) {
  uint32_t vert_shad;
  uint32_t frag_shad;
  
  printf("compiling shader program '%s'", _name);
  printf("  thread %u", pthread_self());
  
    if(_sources->vertex) {
      printf("step\n");
      vert_shad = glCreateShader(GL_VERTEX_SHADER);
      printf("step 1\n");
      glShaderSource(vert_shad, 1, (const GLchar**)&_sources->vertex, NULL);
      printf("step 2\n");
      glCompileShader(vert_shad);
      printf("step 3\n");

      printLog(vert_shad);
      if(ShaderStatus(vert_shad, GL_COMPILE_STATUS) != GL_TRUE)
        return 0;
    }
    if(_sources->fragment) {
      printf("step 4\n");
      frag_shad = glCreateShader(GL_FRAGMENT_SHADER);
      printf("step 5\n");
      glShaderSource(frag_shad, 1, (const GLchar**)&_sources->fragment, NULL);
      printf("step 6\n");
      glCompileShader(frag_shad);
      printf("step 7\n");

      printLog(frag_shad);
      if(ShaderStatus(frag_shad, GL_COMPILE_STATUS) != GL_TRUE)
        return 0;
    }
    printf("step 8\n");
    _prog->id = glCreateProgram();
    printf("step 9\n");
    glAttachShader(_prog->id, vert_shad);
    printf("step 10\n");
    glAttachShader(_prog->id, frag_shad);
    printf("step 11\n");
    glLinkProgram(_prog->id);
    printf("step 12\n");

    if(ShaderProgramStatus(_prog->id, GL_LINK_STATUS) != GL_TRUE) {
      return 0;
      printf("step error 13\n");
    }
    printf("step 13\n");
    
    printf("    compiled id = %s\n", _prog->id);
    
//   } else {
//     printf("error: create program\n");
//     return 0;
//   }
  
  return 1;
}

void printLog(GLuint obj)
{
    int infologLength = 0;
    char infoLog[1024];
 
// 	if (glIsShader(obj))
		glGetShaderInfoLog(obj, 1024, &infologLength, infoLog);
// 	else
// 		glGetProgramInfoLog(obj, 1024, &infologLength, infoLog);
 
//     if (infologLength > 0)
		printf("%s\n", infoLog);
}

// проверка статуса param шейдера shader
GLint ShaderStatus(GLuint shader, GLenum param)
{
        GLint status, length;
        GLchar buffer[1024];

        // получим статус шейдера
        glGetShaderiv(shader, param, &status);
	printf("shad id = %i", shader);

//         в случае ошибки запишем ее в лог-файл
        if (status != GL_TRUE)
        {
                glGetShaderInfoLog(shader, 1024, &length, buffer);
                printf("Shader: %s\n", (const char*)buffer);
        }

        // проверим не было ли ошибок OpenGL
//         OPENGL_CHECK_FOR_ERRORS();
	printf("gl error: %i", glGetError());

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
