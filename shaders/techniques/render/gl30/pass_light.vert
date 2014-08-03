#version 130 

in vec3 a_vert;

uniform mat4 u_mvp;

void main() {
  gl_Position = u_mvp * vec4(a_vert, 1.0);
}