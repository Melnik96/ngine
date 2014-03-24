#include "shader_prog.h"
#include "entity.h"
#include "mesh.h"
#include "hw_buffers.h"
#include "log.h"

#include "GL/glew.h"

#include "gl_render_sys.h"

void gl_draw(struct gl_state* _gl_state, struct entity* _entity, mat4* _mvp) {
  glUseProgram(_gl_state->shader->id);
  glUniformMatrix4fv(_gl_state->shader->uniforms[GLSU_MVP].id, 1, GL_TRUE, _mvp);
  // lights
  //glUniformMatrix4fv(shader_prog_get_param_id(_gl_state->shader, "_light"), 1, GL_TRUE, _mvp);
  // animation
  // teselation
  // physics
  
  glEnable(GL_DEPTH_TEST);
  glBindVertexArray(_entity->hw->vao);
//   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _entity->hw->index);
  glDrawElements(GL_TRIANGLES, 
                 _entity->mesh->num_indices, 
                 GL_UNSIGNED_INT,
                 (void*)(0));

#ifndef NDEBUG
  if(glGetError() != GL_NO_ERROR) {
    error("OpenGL error: %s", glewGetErrorString(glGetError()));
  }
#endif

  glBindVertexArray(NULL);
}
