#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include "..\..\Dependencies\glew\glew.h"
#include "..\..\Dependencies\freeglut\freeglut.h"

namespace Managers
{
	class ShaderManager
	{
	public:
		ShaderManager();
		~ShaderManager();
		void createProgram(const std::string& shaderName,
			const std::string& vertexShaderFileName,
			const std::string& fragmentShaderFileName);
		static const GLuint getShader(const std::string& shaderName);
	private:
		std::string readShader(const std::string& fileName);
		GLuint createShader(GLenum shaderType,
			const std::string& source,
			const std::string& shaderName);
		static std::map<std::string, GLuint> programs;
	};
}