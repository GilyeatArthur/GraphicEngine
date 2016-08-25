#pragma once

//#include "GLFW\glfw3.h"
class Window
{
private:
	int width, height;
	char title[64];
	bool isInitilized = false;
	struct GLFWwindow *winHandle = nullptr; //forward declare

public:
	bool init(int a_width, int a_height, char *a_title);	// Setup, Start, Initialize
	bool step();											// Update, Refresh
	bool term();											// Kill, Terminate

};