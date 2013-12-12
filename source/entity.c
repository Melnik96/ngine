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
#include <malloc.h>
#include <string.h>

#include "render/hw_buffers.h"
#include "mesh.h"
#include "engine.h"
#include "scene.h"
#include "shader_prog.h"

#include "entity.h"

//cool gameplay http://www.youtube.com/watch?v=4gte8ket3jk
int entity_init(struct engine* _eng, struct entity* _ent, char* _name, struct mesh* _mesh, struct material* _material) {
//   _ent->name = NULL;
//   _ent->mesh = NULL;
//   _ent->material = NULL;
  strcpy(_ent->name, _name);
//   _ent->name = _name;
  _ent->mesh = _mesh;
  _ent->material = _material;
  _ent->hw = malloc(sizeof(struct hw_buffers));

  glGenVertexArrays(1, &_ent->hw->vao);
  glBindVertexArray(_ent->hw->vao);

  // Create the buffers for the vertices attributes
  glGenBuffers(4, &_ent->hw->index);

  // Generate and populate the buffers with vertex attributes and the indices
  glBindBuffer(GL_ARRAY_BUFFER, _ent->hw->vertex);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * _ent->mesh->num_vertices, _ent->mesh->vertices, GL_STATIC_DRAW);
  glEnableVertexAttribArray(GLSA_VERTEX);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  if(_mesh->uv) {
    glBindBuffer(GL_ARRAY_BUFFER, _ent->hw->uv);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * _ent->mesh->num_vertices, _ent->mesh->uv, GL_STATIC_DRAW);
    glEnableVertexAttribArray(GLSA_UV);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
  }

  if(_mesh->normals) {
    glBindBuffer(GL_ARRAY_BUFFER, _ent->hw->normal);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * _ent->mesh->num_indices/3, _ent->mesh->normals, GL_STATIC_DRAW);
    glEnableVertexAttribArray(GLSA_NORMAL);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
  }

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ent->hw->index);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * _ent->mesh->num_indices, _ent->mesh->indices, GL_STATIC_DRAW);
  
  glBindVertexArray(0);
#if DEBUG
  gl_get_error();
#endif
}
int entity_update_hw(struct entity* _ent) {
  //redata hw_buffers
  // Generate and populate the buffers with vertex attributes and the indices
  glBindBuffer(GL_ARRAY_BUFFER, _ent->hw->vertex);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * _ent->mesh->num_vertices, _ent->mesh->vertices, GL_STATIC_DRAW);
  glEnableVertexAttribArray(GLSA_VERTEX);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

//   if(_mesh->uv) {
//     glBindBuffer(GL_ARRAY_BUFFER, _ent->hw->uv);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * _ent->mesh->num_vertices, _ent->mesh->uv, GL_STATIC_DRAW);
//     glEnableVertexAttribArray(GLSA_UV);
//     glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
//   }
// 
//   if(_mesh->normals) {
//     glBindBuffer(GL_ARRAY_BUFFER, _ent->hw->normal);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * _ent->mesh->num_indices/3, _ent->mesh->normals, GL_STATIC_DRAW);
//     glEnableVertexAttribArray(GLSA_NORMAL);
//     glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
//   }

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ent->hw->index);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * _ent->mesh->num_indices, _ent->mesh->indices, GL_STATIC_DRAW);
}

// glBindVertexArray(cubeVAO);
// 
// // создадим 3 VBO для данных куба - координаты вершин, текстурные координат и индексный буфер
// glGenBuffers(3, cubeVBO);
// 
// // получим индекс вершинного атрибута 'position' из шейдерной программы
// positionLocation = glGetAttribLocation(shaderProgram, "position");
// if (positionLocation != -1)
// {
//         // начинаем работу с буфером для координат вершин куба
//         glBindBuffer(GL_ARRAY_BUFFER, cubeVBO[0]);
//         // поместим в буфер координаты вершин куба
//         glBufferData(GL_ARRAY_BUFFER, cubeVerticesCount * (3 * sizeof(float)),
//                 cubePositions, GL_STATIC_DRAW);
// 
//         // укажем параметры вершинного атрибута для текущего активного VBO
//         glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
//         // разрешим использование вершинного атрибута
//         glEnableVertexAttribArray(positionLocation);
// }
// 
// // получим индекс вершинного атрибута 'texcoord' из шейдерной программы
// texcoordLocation = glGetAttribLocation(shaderProgram, "texcoord");
// if (texcoordLocation != -1)
// {
//         // начинаем работу с буфером для текстурных координат куба
//         glBindBuffer(GL_ARRAY_BUFFER, cubeVBO[1]);
//         // поместим в буфер текстурные координаты куба
//         glBufferData(GL_ARRAY_BUFFER, cubeVerticesCount * (2 * sizeof(float)),
//                 cubeTexcoords, GL_STATIC_DRAW);
// 
//         // укажем параметры вершинного атрибута для текущего активного VBO
//         glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
//         // разрешим использование вершинного атрибута
//         glEnableVertexAttribArray(texcoordLocation);
// }
// 
// // начинаем работу с индексным буфером
// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeVBO[2]);
// // поместим в буфер индексы вершин куба
// glBufferData(GL_ELEMENT_ARRAY_BUFFER, cubeIndicesCount * sizeof(uint32_t),
//         cubeIndices, GL_STATIC_DRAW);
