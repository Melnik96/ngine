#version 130

uniform sampler2D g_difuse_map;
uniform sampler2D g_wpos_map;
uniform sampler2D g_norm_map;

// uniform vec2 gScreenSize;

out vec4 frag_color;



// struct base_light {
//     vec3  color;
//     float ambient_intensity;
//     float diffuse_intensity;
// };
// 
// struct attenuation {
//     float constant;
//     float linear;
//     float exp;
// };
// 
// struct point_light {
//     base_light base;
//     vec3 pos;
//     attenuation atten;
// };
// 
// uniform point_light 	u_point_light;
// uniform vec3 		u_eye_wpos;
// uniform float 		u_mtl_specular_intensity;
// uniform float 		u_secular_power;
// 
// vec4 calc_light_intern(base_light light, vec3 light_dir, vec3 wpos, vec3 wnorm) {
//     vec4 ambient_color = vec4(light.color, 1.0) * light.ambient_intensity;
//     float diffuse_factor = dot(wnorm, -light_dir);
// 
//     vec4 diffuse_color  = vec4(0, 0, 0, 0);
//     vec4 specular_color = vec4(0, 0, 0, 0);
// 
//     if (diffuse_factor > 0.0) {
//         diffuse_color = vec4(light.color, 1.0) * light.diffuse_intensity * diffuse_factor;
// 
//         vec3 vert_to_eye = normalize(u_eye_wpos - wpos);
//         vec3 light_reflect = normalize(reflect(light_dir, wnorm));
//         float specular_factor = dot(vert_to_eye, light_reflect);
//         specular_factor = pow(specular_factor, u_secular_power);
//         if (specular_factor > 0.0) {
//             specular_color = vec4(light.color, 1.0) * u_mtl_specular_intensity * specular_factor;
//         }
//     }
// 
//     return (ambient_color + diffuse_color + specular_color);
// }
// 
// vec4 calc_point_light(vec3 wpos, vec3 wnorm) {
//     vec3 light_dir = wpos - u_point_light.pos;
//     float distance = length(light_dir);
//     light_dir = normalize(light_dir);
// 
//     vec4 color = calc_light_intern(u_point_light.base, light_dir, wpos, wnorm);
// 
//     float atten =  u_point_light.atten.constant +
//                          u_point_light.atten.linear * distance +
//                          u_point_light.atten.exp * distance * distance;
// 
//     atten = max(1.0, atten);
// 
//     return color / atten;
// }

void main() {
  vec2 screen_size = vec2(1024, 600);
  vec2 uv_cord = gl_FragCoord.xy / screen_size.xy;

  vec3 color = texture2D(g_difuse_map, uv_cord).xyz;
  vec3 wpos = texture2D(g_wpos_map, uv_cord).xyz;
  vec3 wnorm = texture2D(g_norm_map, uv_cord).xyz;
  wnorm = normalize(wnorm);

  frag_color = vec4(color*wpos/*+wnorm*/, 1.0);
//   frag_color = vec4(color, 1.0) * calc_point_light(wpos, wnorm);
}
