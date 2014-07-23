#version 130 

attribute vec3 a_vert;

uniform mat4 u_mvp;

varying vec3 color;

void main() {
  gl_Position = u_mvp * vec4(a_vert, 1.0);
  color = a_vert;
}