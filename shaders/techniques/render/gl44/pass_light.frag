#version 440

in vec4 frag_color;

void main() {
//   vec2 TexCoord = CalcTexCoord();
//   vec3 WorldPos = texture(gPositionMap, TexCoord).xyz;
//   vec3 Color = texture(gColorMap, TexCoord).xyz;
//   vec3 Normal = texture(gNormalMap, TexCoord).xyz;
//   Normal = normalize(Normal);

//   gl_FragColor = vec4(Color, 1.0) * CalcPointLight(WorldPos, Normal);
  gl_FragColor = frag_color;
}
