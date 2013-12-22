in vec3 vert;
uniform mat4 MVP;
 
void main() {
  // Output position of the vertex, in clip space : MVP * position
  vec4 v = vec4(vert,1); // Transform an homogeneous 4D vector, remember ?
  gl_Position = MVP * v;
} 
