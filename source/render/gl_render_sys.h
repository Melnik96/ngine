//OpenGL 3+ render system implementation

#define GL_GLEXT_PROTOTYPES
#include <GL/glext.h>

#include "math.h"

struct gl_render_sys {
  matrix4x4 view_matrix;
  matrix4x4 world_matrix;
  matrix4x4 texture_matrix;
};

int some_fun() {
  glBindProgramARB();
}
