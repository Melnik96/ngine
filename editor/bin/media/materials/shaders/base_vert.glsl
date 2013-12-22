#version 330 core

uniform mat4 MVP;

in vec3 vert;
// in vec3 color;

out vec3 fragmentColor;

void main(void)
{
	gl_Position   = /*MVP * */vec4(vert, 1.);
	fragmentColor = vert;
}
