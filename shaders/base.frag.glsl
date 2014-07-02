#version 330 core

// uniform sampler2D u_texture;

in vec3 color;

void main(void) {
  gl_FragColor = color;
}
