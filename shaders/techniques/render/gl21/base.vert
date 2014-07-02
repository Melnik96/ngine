#version 120

attribute vec3 a_vert;
// attribute vec2 a_uv;

uniform mat4 u_mvp;

varying vec4 frag_color;
// varying frag_uv;

void main() {
  gl_Position = u_mvp * vec4(a_vert, 1.0);
  
  frag_color = vec4(1.0, 0.0, 0.0, 0.5);
//   frag_color.w = 0;
//   frag_uv = a_uv;
}