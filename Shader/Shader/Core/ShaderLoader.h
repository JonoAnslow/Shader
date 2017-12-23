#pragma once

#include "..\..\Dependencies\glew\glew.h"
#include "..\..\Dependencies\freeglut\freeglut.h"
#include <iostream>

namespace Core
{
	class ShaderLoader
	{
	private:
		std::string readShader(char* fileName);
		GLuint createShader(GLenum shaderType,
			std::string source,
			char* shaderName);

	public:
		ShaderLoader();
		~ShaderLoader();
		GLuint createProgram(char* vertexShaderFileName,
			char* fragmentShaderFileName);
	};
}