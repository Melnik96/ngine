#version 130

void main() {
//   vec2 TexCoord = CalcTexCoord();
//   vec3 WorldPos = texture(gPositionMap, TexCoord).xyz;
//   vec3 Color = texture(gColorMap, TexCoord).xyz;
//   vec3 Normal = texture(gNormalMap, TexCoord).xyz;
//   Normal = normalize(Normal);

//   gl_FragColor = vec4(Color, 1.0) * CalcPointLight(WorldPos, Normal);
  gl_FragColor = vec4(1.0, 0, 0, 1.0);
}
