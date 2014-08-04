#version 130

uniform sampler2D g_difuse_map;
uniform sampler2D g_wpos_map;
uniform sampler2D g_norm_map;
uniform sampler2D g_ssao_map;

// uniform vec2 gScreenSize;

uniform vec3 u_light_pos;
uniform vec3 u_light_dcolor;

out vec4 frag_color;

void main() {
  vec2 screen_size = vec2(1024, 600);
  vec2 uv_cord = gl_FragCoord.xy / screen_size.xy;

  vec3 color = texture2D(g_difuse_map, uv_cord).xyz;
  vec3 wpos = texture2D(g_wpos_map, uv_cord).xyz;
  vec3 wnorm = texture2D(g_norm_map, uv_cord).xyz;
  wnorm = normalize(wnorm);
  float ssao = texture2D(g_ssao_map, uv_cord).r;
  
  vec3 surfaceToLight = u_light_pos - wpos;
  surfaceToLight = normalize(surfaceToLight);

  float brightness = dot(wnorm, surfaceToLight) / (length(surfaceToLight) * length(wnorm));
  brightness = clamp(brightness, 0, 1);
  
  frag_color = (brightness * vec4(u_light_dcolor, 1) * vec4(color, 1.0)) * ssao;
}
