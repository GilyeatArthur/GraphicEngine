#include "gldecs.h"

#include "window.h"

#include <cstring>
#include <cstdio>
#include <cstdlib>

#ifdef _DEBUG

void APIENTRY GL_errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
	//std::cerr << message << std::endl;


	if (severity == GL_DEBUG_SEVERITY_HIGH)
	{
	fprintf(stderr, "%s\n", message);
	}
}

#endif

bool Window::init(int a_width, int a_height, char *a_title)
{
	width = a_width;
	height = a_height;
	strcpy_s(title, 64, a_title);

	glfwInit();

	winHandle = glfwCreateWindow(width, height, title, nullptr, nullptr);
	
	glfwMakeContextCurrent(winHandle);
	isInitilized = true;

	glewExperimental = true;
	glewInit();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

#ifdef _DEBUG

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

	glDebugMessageCallback(GL_errorCallback, 0);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, true);

#endif


	return true;
}


bool Window::step()
{
	if (!isInitilized) return false;
	glfwPollEvents();
	glfwSwapBuffers(winHandle);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return !glfwWindowShouldClose(winHandle);
}

bool Window::term()
{
	glfwDestroyWindow(winHandle);
	glfwTerminate(); //redunant, but for the sake of being thorough
	winHandle = nullptr;
	isInitilized = false;
	return false;
}