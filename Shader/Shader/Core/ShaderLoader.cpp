#include "ShaderLoader.h" 
#include <iostream>
#include <fstream>
#include <vector>

using namespace Core;
using namespace std;

ShaderLoader::ShaderLoader() {}
ShaderLoader::~ShaderLoader() {}

std::string ShaderLoader::readShader(char* fileName)
{
	string shaderCode;
	ifstream file(fileName, ios::in);

	if (!file.good())
	{
		cout << "Can't read file " << fileName << endl;
		terminate();
	}

	file.seekg(0, ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	file.seekg(0, ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

GLuint ShaderLoader::createShader(GLenum shaderType, string source, char* shaderName)
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
		vector<char> shaderLog(infoLogLength);
		glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderLog[0]);
		cout << "ERROR compiling shader: " << shaderName << endl << &shaderLog[0] << endl;
		return 0;
	}
	return shader;
}

GLuint ShaderLoader::createProgram(char* vertexShaderFileName, char* fragmentShaderFileName)
{
	string vertexShaderCode = readShader(vertexShaderFileName);
	string fragmentShaderCode = readShader(fragmentShaderFileName);

	GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderCode, "vertex shader");
	GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderCode, "fragment shader");

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
		vector<char> programLog(infoLogLength);
		glGetProgramInfoLog(program, infoLogLength, NULL, &programLog[0]);
		cout << "Shader Loader : LINK ERROR" << endl << &programLog[0] << endl;
		return 0;
	}
	return program;
}