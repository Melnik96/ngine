#version 130

in vec3 a_vert;

out vec2 uv;

void main(void) {
  gl_Position = vec4(a_vert, 1);
  gl_Position = sign( gl_Position );
 
  // Texture coordinate for screen aligned (in correct range):
  uv = (vec2(gl_Position.x, gl_Position.y) + vec2(1.0)) * 0.5;
}
