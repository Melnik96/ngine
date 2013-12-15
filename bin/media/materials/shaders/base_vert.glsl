in vec3 vertex_pos;
uniform mat4 MVP;
 
void main() {
  // Output position of the vertex, in clip space : MVP * position
  vec4 v = vec4(vertex_pos,1); // Transform an homogeneous 4D vector, remember ?
  gl_Position = MVP * v;
}