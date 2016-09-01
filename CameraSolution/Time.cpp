#include "GLFW\glfw3.h"
#include "Time.h"

bool Time::init()
{
	glfwSetTime(0);
	return true;
}

bool Time::step()
{
	previousTime = currentTime;
	currentTime = getRealTime();
	deltaTime = currentTime - previousTime;

	return false;
}

bool Time::term()
{
	return true;
}

float Time::getDeltaTime() const
{
	return deltaTime;
}

float Time::getTotalTime() const
{
	return currentTime;
}

float Time::getRealTime() const
{
	return glfwGetTime();
}
