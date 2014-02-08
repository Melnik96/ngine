#version 330 core

uniform vec4 _mvp;

in vec3 vert;
// in vec3 color;

out vec3 fragmentColor;

void main(void) {
  gl_Position   = _mvp*vec4(vert, 1.0);
  fragmentColor = vert;
}