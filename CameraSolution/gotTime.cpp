#include "GLFW\glfw3.h"
#include "gotTime.h"

bool GotTime::init()
{
	glfwSetTime(0);
	previousTime = 0;
	currentTime = 0;
	deltaTime = 0;
	return true;
}

bool GotTime::step()
{
	previousTime = currentTime;
	currentTime = getRealTime();
	deltaTime = currentTime - previousTime;

	return false;
}

bool GotTime::term()
{
	return true;
}

float GotTime::getDeltaTime() const
{
	return deltaTime;
}

float GotTime::getTotalTime() const
{
	return currentTime;
}

float GotTime::getRealTime() const
{
	return glfwGetTime();
}
