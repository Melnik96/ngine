#version 130

uniform sampler2D g_difuse_map;
uniform sampler2D g_wpos_map;

void main() {
//   vec2 TexCoord = CalcTexCoord();
//   vec3 WorldPos = texture(gPositionMap, TexCoord).xyz;
//   vec3 Color = texture(gColorMap, TexCoord).xyz;
//   vec3 Normal = texture(gNormalMap, TexCoord).xyz;
//   Normal = normalize(Normal);

//   gl_FragColor = vec4(Color, 1.0) * CalcPointLight(WorldPos, Normal);
  vec2 screen_size = vec2(1024, 600);
  vec2 uv_cord = gl_FragCoord.xy / screen_size;

  vec3 color = texture(g_difuse_map, uv_cord).xyz;
  vec3 wpos = texture(g_wpos_map, uv_cord).xyz;

  gl_FragColor = vec4(color*wpos, 1.0)/*vec4(1.0, 0, 0, 1.0)*/;
}
