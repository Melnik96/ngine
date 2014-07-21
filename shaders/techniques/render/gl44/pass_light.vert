#version 440 

uniform mat4 u_mvp;

in vec3 a_vert;

out vec4 frag_color;

void main() {
  gl_Position = u_mvp * vec4(a_vert, 1.0);
  frag_color = clamp(vec4(a_vert, 1), 0, 1);
}