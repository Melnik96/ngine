#version 120

varying vec4 frag_color;
// varying frag_uv;

// uniform sampler2D u_tex;

void main() {
  gl_FragColor = vec4(1.0, 0.0, 0.0, 0.5)/*frag_color*//* * texture2D(u_tex, frag_uv.st)*/;
}