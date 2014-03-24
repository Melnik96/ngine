#version 120

varying vec3 fragmentColor;

// out vec4 color;

void main(void) {
  vec3 cld = vec3(1.,0.,0.);
  gl_FragColor/*color*/ = vec4(cld/*fragmentColor*/, 1.0);
}
