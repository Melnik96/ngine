#version 120

varying vec4 frag_color;
// varying frag_uv;

// uniform sampler2D u_tex;

void main() {
  gl_FragColor = frag_color/* * texture2D(u_tex, frag_uv.st)*/;
}