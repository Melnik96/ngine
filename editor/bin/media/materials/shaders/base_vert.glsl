#version 330 core

uniform vec3 g_obj_pos;
uniform vec4 g_obj_orient;
uniform vec3 g_obj_scale;

in vec3 vert;
// in vec3 color;

out vec3 fragmentColor;

void main(void) {
  gl_Position   = vec4(vert, 1.)*g_obj_pos*g_obj_scale*g_obj_orient;
  fragmentColor = vert;
}
