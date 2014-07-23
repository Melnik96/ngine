#version 130

uniform sampler2D u_tex;

varying vec2 frag_uv;
varying vec3 frag_wnorm;
varying vec3 frag_wpos;

out vec3 g_difuse_map;
out vec3 g_wpos_map;
out vec3 g_norm_map;

void main() {
//   TexCoordOut = vec3(frag_uv, 0.0);
  
//   gl_FragData[0] = texture2D(u_tex, frag_uv).xyz;
//   gl_FragData[1] = frag_wpos;
  g_norm_map = normalize(frag_wnorm);
  g_difuse_map = texture2D(u_tex, frag_uv).xyz;
  g_wpos_map = frag_wpos;
}
