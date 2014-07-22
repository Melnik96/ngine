#version 130 

attribute vec3 a_vert;

uniform mat4 u_mvp;

varying vec3 frag_color;

void main() {
  gl_Position = u_mvp * vec4(a_vert, 1.0);
  frag_color = a_vert;
}