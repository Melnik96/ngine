#version 130

uniform sampler2D u_tex;

in vec2 frag_uv;
// varying vec3 frag_wnorm;
in vec3 frag_wpos;

layout(location = 0)out vec3 g_difuse;
layout(location = 1)out vec3 g_wpos;

void main() {
//   WorldPosOut = frag_wpos;
//   DiffuseOut = texture(gColorMap, TexCoord0).xyz;
//   NormalOut = normalize(frag_wnorm);
//   TexCoordOut = vec3(frag_uv, 0.0);
  
//   g_difuse = texture(u_tex, frag_uv).xyz;
//   g_wpos = frag_wpos;
} 
