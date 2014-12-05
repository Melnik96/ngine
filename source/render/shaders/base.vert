#version 440

attribute vec3 a_vert;
// attribute vec2 a_uv;

uniform mat4 u_mvp;

out vec4 frag_color;
// out vec2 frag_uv;

void main() {
  gl_Position = u_mvp * vec4(a_vert, 1.0);
  
  frag_color = clamp(vec4(a_vert, 1), 0, 1);
//   frag_color.w = 0;
//   frag_uv = a_uv;
}