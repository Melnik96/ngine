#version 440

in vec4 frag_color;
in vec2 frag_uv;

uniform sampler2D u_tex;

void main() {
  gl_FragColor = frag_color * texture2D(u_tex, frag_uv.st);
}