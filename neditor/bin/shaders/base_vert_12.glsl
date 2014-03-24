#version 120

uniform mat4 _mvp;

attribute vec3 vert;
// in vec3 color;

varying vec3 fragmentColor;

void main(void) {
  gl_Position   = /*_mvp**/vec4(vert, 1.0);
  fragmentColor = vert;
}