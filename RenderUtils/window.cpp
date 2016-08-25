#define GLEW_STATIC
#include "GLEW\GL\glew.h"
#include "GLFW\glfw3.h"
#include <cstring>
#include "window.h"

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
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	return true;
}

bool Window::step()
{
	if (!isInitilized) return false;

	glClear(GL_COLOR_BUFFER_BIT);

	glfwPollEvents();
	glfwSwapBuffers(winHandle);
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