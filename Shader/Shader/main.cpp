/**#include "..\Dependencies\glew\glew.h"
#include "..\Dependencies\freeglut\freeglut.h"
#include <iostream>
#include <fstream>
#include <vector>

#include "Managers\ShaderManager.h"
#include "Core\GameModel.h"

using namespace Managers;

Model::GameModel* gameModels;
ShaderManager* shaderManager;
GLuint program;

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0);//clear red

	glBindVertexArray(gameModels->getModel("triangle1"));
	glUseProgram(program);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glutSwapBuffers();
}

void closeCallback()
{
	std::cout << "GLUT:\t Finished" << std::endl;
	glutLeaveMainLoop();
}

void init()
{
	glEnable(GL_DEPTH_TEST);

	gameModels = new Model::GameModel();
	gameModels->createTriangleModel("triangle1");

	shaderManager = new ShaderManager();
	shaderManager->createProgram("Basic Shader", "Shaders\\Vertex Shaders\\VertexShader.glsl",
		"Shaders\\Fragment Shaders\\FragmentShader.glsl");
	program = ShaderManager::getShader("Basic Shader");
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}**/
#include "Core\Init\InitGLUT.h"
using namespace Core;
using namespace Init;

int main(int argc, char** argv)
{
	WindowInfo window(std::string("Basic"), 400, 200, 800, 600, true);

	ContextInfo context(4, 5, true);
	FrameBufferInfo frameBufferInfo(true, true, true, true);
	InitGLUT::init(window, context, frameBufferInfo);

	InitGLUT::run();

	return 0;
}