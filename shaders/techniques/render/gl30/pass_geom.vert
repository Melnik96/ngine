#version 130

attribute vec3 a_vert;
attribute vec2 a_uv;
// attribute vec3 a_norm;

uniform mat4 u_mvp;
uniform mat4 u_model;

varying vec2 frag_uv;
// varying vec3 frag_wnorm;
varying vec3 frag_wpos;

void main() { 
  gl_Position = u_mvp * vec4(a_vert, 1.0);
  frag_uv = a_uv;
//   frag_wnorm = (gWorld * vec4(Normal, 0.0)).xyz;
  frag_wpos = (u_model * vec4(a_vert, 1.0)).xyz;
}
