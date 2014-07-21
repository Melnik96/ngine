#version 120

varying vec4 frag_color;
varying vec2 frag_uv;

uniform sampler2D u_tex;

void main() {
  gl_FragColor = frag_color * texture2D(u_tex, frag_uv.st)/* *
   	    	    	 vec4(vec3(0.5,0.2,0), 1.0f) *
   	    	    	 1*/;
}