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
#include <string.h>
#include <string.h>

#include "log.h"

#include "shader_prog.h"

int shader_prog_init(struct shader_prog* _prog, const char* _name, struct shader_source* _sources) {
  uint32_t vert_shad = 0;
  uint32_t geom_shad = 0;
  uint32_t frag_shad = 0;
  uint32_t comp_shad = 0;
  uint32_t tess_ctrl_shad = 0;
  uint32_t tess_eval_shad = 0;

  int compiled;

  int logLength, charsWritten;

  char* log;

//   if(!shaderProgram || !vertexSource || !fragmentSource) {
//     return GLUS_FALSE;
//   }
// 
//   shaderProgram->program = 0;
//   shaderProgram->compute = 0;
//   shaderProgram->vertex = 0;
//   shaderProgram->control = 0;
//   shaderProgram->evaluation = 0;
//   shaderProgram->geometry = 0;
//   shaderProgram->fragment = 0;

  #define GLUS_OK 0
#define GLUS_TRUE   1
#define GLUS_FALSE  0
#define GLUS_BACKWARD_COMPATIBLE_BIT    0x0000
#define GLUS_FORWARD_COMPATIBLE_BIT     0x0002
#define GLUS_VERTEX_SHADER              0x8B31
#define GLUS_FRAGMENT_SHADER            0x8B30
#define GLUS_TESS_EVALUATION_SHADER     0x8E87
#define GLUS_TESS_CONTROL_SHADER        0x8E88
#define GLUS_GEOMETRY_SHADER            0x8DD9
#define GLUS_COMPUTE_SHADER 		0x91B9
  
  strcpy(_prog->name, _name);
  
  vert_shad = glCreateShader(GL_VERTEX_SHADER);

  glShaderSource(vert_shad, 1, (const char**) &_sources->vertex, 0);
//   debug(_sources->vertex);
//   debug(_sources->fragment);

  glCompileShader(vert_shad);

  glGetShaderiv(vert_shad, GL_COMPILE_STATUS, &compiled);

  if(!compiled) {
    glGetShaderiv(vert_shad, GL_INFO_LOG_LENGTH, &logLength);

    log = (char*) malloc((size_t)logLength);

    if(!log) {
      return GLUS_FALSE;
    }

    glGetShaderInfoLog(vert_shad, logLength, &charsWritten, log);

    debug("Vertex shader compile error:");
    debug("%s", log);

    free(log);

    vert_shad = 0;

    return GLUS_FALSE;
  }

//   if(controlSource) {
//     shaderProgram->control = glCreateShader(GLUS_TESS_CONTROL_SHADER);
// 
//     glShaderSource(shaderProgram->control, 1, (const char**) controlSource, 0);
// 
//     glCompileShader(shaderProgram->control);
// 
//     glGetShaderiv(shaderProgram->control, GL_COMPILE_STATUS, &compiled);
// 
//     if(!compiled) {
//       glGetShaderiv(shaderProgram->control, GL_INFO_LOG_LENGTH, &logLength);
// 
//       log = (char*) malloc((size_t)logLength);
// 
//       if(!log) {
//         glusDestroyProgram(shaderProgram);
// 
//         return GLUS_FALSE;
//       }
// 
//       glGetShaderInfoLog(shaderProgram->control, logLength, &charsWritten, log);
// 
//       glusLogPrint(GLUS_LOG_ERROR, "Control shader compile error:");
//       glusLogPrint(GLUS_LOG_ERROR, "%s", log);
// 
//       free(log);
// 
//       shaderProgram->control = 0;
// 
//       glusDestroyProgram(shaderProgram);
// 
//       return GLUS_FALSE;
//     }
//   }
// 
//   if(evaluationSource) {
//     shaderProgram->evaluation = glCreateShader(GLUS_TESS_EVALUATION_SHADER);
// 
//     glShaderSource(shaderProgram->evaluation, 1, (const char**) evaluationSource, 0);
// 
//     glCompileShader(shaderProgram->evaluation);
// 
//     glGetShaderiv(shaderProgram->evaluation, GL_COMPILE_STATUS, &compiled);
// 
//     if(!compiled) {
//       glGetShaderiv(shaderProgram->evaluation, GL_INFO_LOG_LENGTH, &logLength);
// 
//       log = (char*) malloc((size_t)logLength);
// 
//       if(!log) {
//         glusDestroyProgram(shaderProgram);
// 
//         return GLUS_FALSE;
//       }
// 
//       glGetShaderInfoLog(shaderProgram->evaluation, logLength, &charsWritten, log);
// 
//       glusLogPrint(GLUS_LOG_ERROR, "Evaluation shader compile error:");
//       glusLogPrint(GLUS_LOG_ERROR, "%s", log);
// 
//       free(log);
// 
//       shaderProgram->evaluation = 0;
// 
//       glusDestroyProgram(shaderProgram);
// 
//       return GLUS_FALSE;
//     }
//   }
// 
//   if(geometrySource) {
//     shaderProgram->geometry = glCreateShader(GLUS_GEOMETRY_SHADER);
// 
//     glShaderSource(shaderProgram->geometry, 1, (const char**) geometrySource, 0);
// 
//     glCompileShader(shaderProgram->geometry);
// 
//     glGetShaderiv(shaderProgram->geometry, GL_COMPILE_STATUS, &compiled);
// 
//     if(!compiled) {
//       glGetShaderiv(shaderProgram->geometry, GL_INFO_LOG_LENGTH, &logLength);
// 
//       log = (char*) malloc((size_t)logLength);
// 
//       if(!log) {
//         glusDestroyProgram(shaderProgram);
// 
//         return GLUS_FALSE;
//       }
// 
//       glGetShaderInfoLog(shaderProgram->geometry, logLength, &charsWritten, log);
// 
//       glusLogPrint(GLUS_LOG_ERROR, "Geometry shader compile error:");
//       glusLogPrint(GLUS_LOG_ERROR, "%s", log);
// 
//       free(log);
// 
//       shaderProgram->geometry = 0;
// 
//       glusDestroyProgram(shaderProgram);
// 
//       return GLUS_FALSE;
//     }
//   }

  frag_shad = glCreateShader(GLUS_FRAGMENT_SHADER);

  glShaderSource(frag_shad , 1, (const char**) &_sources->fragment, 0);

  glCompileShader(frag_shad);

  glGetShaderiv(frag_shad, GL_COMPILE_STATUS, &compiled);

  if(!compiled) {
    glGetShaderiv(frag_shad, GL_INFO_LOG_LENGTH, &logLength);

    log = (char*) malloc((size_t)logLength);

    if(!log) {
//       glusDestroyProgram(shaderProgram);

      return GLUS_FALSE;
    }

    glGetShaderInfoLog(frag_shad, logLength, &charsWritten, log);

    debug("Fragment shader compile error:");
    debug("%s", log);

    free(log);

    frag_shad = 0;

//     glusDestroyProgram(shaderProgram);

    return GLUS_FALSE;
  }

  _prog->id = glCreateProgram();

  glAttachShader(_prog->id, vert_shad);
  glAttachShader(_prog->id, frag_shad);

//   if(shaderProgram->control) {
//     glAttachShader(shaderProgram->program, shaderProgram->control);
//   }
// 
//   if(shaderProgram->evaluation) {
//     glAttachShader(shaderProgram->program, shaderProgram->evaluation);
//   }
// 
//   if(shaderProgram->geometry) {
//     glAttachShader(shaderProgram->program, shaderProgram->geometry);
//   }
  
  
    int linked;
//     int logLength, charsWritten;
//     char* log;

    if(!_prog->id) {
        return GLUS_FALSE;
    }

    
    
  _prog->attribs = malloc(3*sizeof(struct shader_param));
  
  glBindAttribLocation(_prog->id, GLSA_VERTEX, "vert");
  memcpy(_prog->attribs[GLSA_VERTEX].name, "vert", sizeof "vert");
  _prog->attribs[GLSA_VERTEX].id = GLSA_VERTEX;
  
    glLinkProgram(_prog->id);
    
  _prog->uniforms = malloc(sizeof(struct shader_param));
  memcpy(_prog->uniforms->name, "g_obj_pos", 4);
  _prog->uniforms->id = glGetUniformLocation(_prog->id, "g_obj_pos");
  if(_prog->uniforms->id < 0) {printf("error: int _u_mvp = glGetUniformLocation(cur_scene->cur_shader->id, 'MVP');\n");}

    
    glGetProgramiv(_prog->id, GL_LINK_STATUS, &linked);

    if(!linked) {
        glGetProgramiv(_prog->id, GL_INFO_LOG_LENGTH, &logLength);
        log = (char*) malloc((size_t)logLength);
        if (!log) {
//             glusDestroyProgram(shaderProgram);
            return GLUS_FALSE;
        }

        glGetProgramInfoLog(_prog->id, logLength, &charsWritten, log);

        printf("Shader program link error:");
        printf("%s", log);

        free(log);

//         glusDestroyProgram(shaderProgram);

        return GLUS_FALSE;
    }
    
//   int a_vertex = glGetAttribLocation(_prog->id, "vertex");
//   if(!a_vertex) {printf("error: int _a_vpm = glGetAttribLocation(_prog->id, 'vertex');\n");}
  
//   glBindAttribLocation(_prog->id, GLSA_NORMAL, "normal");
//   glBindAttribLocation(_prog->id, GLSA_UV, "uv");
  
//   int _u_mvp = glGetUniformLocation(_prog->id, "MVP");
//   if(!_u_mvp) {printf("error: int _u_mvp = glGetUniformLocation(cur_scene->cur_shader->id, 'MVP');\n");}
//   _prog->uniforms = malloc(sizeof(struct shader_param));
//   memcpy(_prog->uniforms->name, "MVP", sizeof "MVP");
// //   _prog->uniforms->name = "MVP";
//   _prog->id = _u_mvp;


  return GLUS_TRUE;
}

void printLog(GLuint obj) {
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
GLint ShaderStatus(GLuint shader, GLenum param) {
  GLint status, length;
  GLchar buffer[1024];

  // получим статус шейдера
  glGetShaderiv(shader, param, &status);
  printf("shad id = %i", shader);

//         в случае ошибки запишем ее в лог-файл
  if(status != GL_TRUE) {
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
GLint ShaderProgramStatus(GLuint program, GLenum param) {
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
