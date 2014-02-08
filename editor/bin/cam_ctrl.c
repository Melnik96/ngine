#include <GLFW/glfw3.h>
#include "engine.h"
#include "viewport.h"
#include "sc_obj.h"

void cam_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  } else if(key == GLFW_KEY_W && action == GLFW_PRESS) {
    ((struct engine*)ngine_intense())->viewport->camera->pos.z -= 0.5f/60.f;
  } else if(key == GLFW_KEY_S && action == GLFW_PRESS) {
    ((struct engine*)ngine_intense())->viewport->camera->pos.z += 0.5f/60.f;
  } else if(key == GLFW_KEY_A && action == GLFW_PRESS) {
    ((struct engine*)ngine_intense())->viewport->camera->pos.x -= 0.5f/60.f;
  } else if(key == GLFW_KEY_D && action == GLFW_PRESS) {
    ((struct engine*)ngine_intense())->viewport->camera->pos.x += 0.5f/60.f;
  }
}
