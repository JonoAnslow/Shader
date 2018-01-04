#version 430 core
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;

out vec4 color;

void main(void)
{
	color = inColor;
	gl_Position = vec4(inPosition, 1);
}