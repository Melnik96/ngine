#version 130

uniform sampler2D u_tex;

varying vec2 frag_uv;
// varying vec3 frag_wnorm;
varying vec3 frag_wpos;

void main() {
//   WorldPosOut = frag_wpos;
//   DiffuseOut = texture(gColorMap, TexCoord0).xyz;
//   NormalOut = normalize(frag_wnorm);
//   TexCoordOut = vec3(frag_uv, 0.0);
  
  gl_FragData[0] = texture2D(u_tex, frag_uv).xyzw;
  gl_FragData[1] = vec4(frag_wpos, 0);
}
