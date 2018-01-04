#include "InitGLUT.h"

using namespace Core::Init;

void InitGLUT::init(const Core::WindowInfo& window, const Core::ContextInfo& contextInfo, const Core::FrameBufferInfo& frameBufferInfo)
{
	// making fake arguments
	int fakeargc = 1;
	char* fakeargv[] = { "fake", NULL };
	glutInit(&fakeargc, fakeargv);

	if (contextInfo.core)
	{
		glutInitContextVersion(contextInfo.majorVersion, contextInfo.minorVersion);
		glutInitContextProfile(GLUT_CORE_PROFILE);
	}
	else
	{
		glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	}

	glutInitDisplayMode(frameBufferInfo.flags);
	glutInitWindowPosition(window.positionX, window.positionY);
	glutInitWindowSize(window.width, window.height);

	glutCreateWindow(window.name.c_str());

	std::cout << "GLUT:initialized" << std::endl;

	glutIdleFunc(idleCallback);
	glutCloseFunc(closeCallback);
	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshapeCallback);

	InitGLEW::Init();

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	printOpenGLInfo(window, contextInfo);
}

void InitGLUT::run()
{
	std::cout << "GLUT:\t Start Running" << std::endl;
	glutMainLoop();
}

void InitGLUT::close()
{
	std::cout << "GLUT:\t Finished" << std::endl;
	glutLeaveMainLoop();
}

void InitGLUT::idleCallback(void)
{
	glutPostRedisplay();
}

void InitGLUT::displayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutSwapBuffers();
}

void InitGLUT::reshapeCallback(int width, int height)
{

}

void InitGLUT::closeCallback()
{
	close();
}

void InitGLUT::enterFullscreen()
{
	glutFullScreen();
}

void InitGLUT::exitFullscreen()
{
	glutLeaveFullScreen();
}

void InitGLUT::printOpenGLInfo(const Core::WindowInfo& window, const Core::ContextInfo& contextInfo)
{
	const unsigned char* renderer = glGetString(GL_RENDERER);
	const unsigned char* vendor = glGetString(GL_VENDOR);
	const unsigned char* version = glGetString(GL_VERSION);

	std::cout << "**********************************************" << std::endl;
	std::cout << "GLUT:Initialise" << std::endl;
	std::cout << "GLUT:\tVendor : " << vendor << std::endl;
	std::cout << "GLUT:\tRenderer : " << renderer << std::endl;
	std::cout << "GLUT:\tOpenGL version: " << version << std::endl;
}