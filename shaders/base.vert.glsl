#version 330 core

// struct vert_data_t {
//   vec3 vert;
//   vec3 color;
//   vec3 norm;
//   vec3 tangent;
//   vec2 uv;
// };

uniform mat4 u_mvp;

// in vert_data_t vert_data;

in vec3 vert;

out vec3 color;
out vec2 uv;

void main(void) {
  gl_Position   = u_mvp*vec4(vert, 1.0);
  color = vert;
//   uv = vert_data.uv;
}
