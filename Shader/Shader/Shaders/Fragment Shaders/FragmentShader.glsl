#version 430 core
layout(location = 0) out vec4 outColor;

in vec4 color;

void main(void)
{
	outColor = color;
}