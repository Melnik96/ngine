#version 330 core

// in vec3 fragmentColor;

out vec4 color;

void main(void)
{
	vec3 cld = vec3(1.,0.,0.);
	color = vec4(cld, 1.0);
}
