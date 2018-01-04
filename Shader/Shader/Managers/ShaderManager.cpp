#include "ShaderManager.h" 
#include <iostream>
#include <fstream>
#include <vector>

using namespace Managers;

std::map<std::string, GLuint> ShaderManager::programs;

ShaderManager::ShaderManager() {}
ShaderManager::~ShaderManager() 
{
	std::map<std::string, GLuint>::iterator iter;
	for (iter = programs.begin(); iter != programs.end(); ++iter)
	{
		GLuint program = iter->second;
		glDeleteProgram(program);
	}
	programs.clear();
}

std::string ShaderManager::readShader(const std::string& fileName)
{
	std::string shaderCode;
	std::ifstream file(fileName.c_str(), std::ios::in);

	if (!file.good())
	{
		std::cout << "Can't read file " << fileName.c_str() << std::endl;
		terminate();
	}

	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

GLuint ShaderManager::createShader(GLenum shaderType, const std::string& source, const std::string& shaderName)
{
	int compileResult = 0;

	GLint shader = glCreateShader(shaderType);
	const char* shaderCodePtr = source.c_str();
	const int shaderCodeSize = source.size();

	glShaderSource(shader, 1, &shaderCodePtr, &shaderCodeSize);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

	if (compileResult == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> shaderLog(infoLogLength);
		glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderLog[0]);
		std::cout << "ERROR compiling shader: " << shaderName.c_str() << std::endl << &shaderLog[0] << std::endl;
		return 0;
	}
	return shader;
}

void ShaderManager::createProgram(const std::string& shaderName, const std::string& vertexShaderFileName, const std::string& fragmentShaderFileName)
{
	std::string vertexShaderCode = readShader(vertexShaderFileName);
	std::string fragmentShaderCode = readShader(fragmentShaderFileName);

	GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderCode, (std::string) "vertex shader");
	GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderCode, (std::string) "fragment shader");

	int linkResult = 0;
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);

	if (linkResult == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> programLog(infoLogLength);
		glGetProgramInfoLog(program, infoLogLength, NULL, &programLog[0]);
		std::cout << "Shader Loader : LINK ERROR" << std::endl << &programLog[0] << std::endl;
		return;
	}
	programs.insert(std::make_pair(shaderName, program));
}

const GLuint ShaderManager::getShader(const std::string& shaderName)
{
	std::map<std::string, GLuint>::iterator iter = programs.find(shaderName);
	if (iter != programs.end())
	{
		return programs.at(shaderName);
	}
	else
	{
		std::cout << "ERROR Following Shader Not Found: " << shaderName.c_str() << std::endl;
		std::string errorMessage = "Shader Key Not Found: ";
		errorMessage.append(shaderName.c_str());

		throw std::invalid_argument(errorMessage.c_str());
	}
}