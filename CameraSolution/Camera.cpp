#include "Input.h"
#include "gotTime.h"
#include "Camera.h"

void FlyCamera::update(const Input &in, const GotTime &t)
{
	// direction represents our forward direction


	glm::vec3 moveDir = glm::vec3(0, 0, 0);
	glm::vec3 right   = glm::cross(direction, glm::vec3(0, 1, 0));
	glm::vec3 up      = glm::cross(right, direction);

	if (in.getKeyState('W') == Input::DOWN)	moveDir += direction;
	if (in.getKeyState('S') == Input::DOWN)	moveDir -= direction;
	if (in.getKeyState('A') == Input::DOWN)	moveDir -= right;
	if (in.getKeyState('D') == Input::DOWN)	moveDir += right;
	if (in.getKeyState('E') == Input::DOWN)	moveDir -= up;
	if (in.getKeyState('Q') == Input::DOWN)	moveDir += up;

	if (glm::length(moveDir) >= .7f)
	{
		moveDir = glm::normalize(moveDir);
		position += moveDir * t.getDeltaTime() * speed;
	}
}
