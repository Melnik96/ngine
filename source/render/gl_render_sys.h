//OpenGL 3+ render system implementation

#define GL_GLEXT_PROTOTYPES
#include <GL/glext.h>

#include "math.h"

struct gl_state {
  mat4 model_matrix;
  mat4 view_matrix;
  mat4 proj_matrix;
  
  struct shader_prog* shader;
  
  //lights
  //mesh
  //material
};

gl_draw(struct gl_state* _gl_state, struct entity* _ent, mat4* _mvp);

struct gl_render_sys {
};
