#include "Input.h"
#include "gotTime.h"
#include "Camera.h"

void FlyCamera::update(const Input &in, const GotTime &t)
{

	/*glm::vec3 right   = glm::cross(direction, glm::vec3(0, 1, 0));
	glm::vec3 up      = glm::cross(right, direction);*/

	yaw -= in.getMouseAxisHorizontal() * t.getDeltaTime() * .1;
	pitch += in.getMouseAxisVertical() * t.getDeltaTime() * .1;

	// pitch should only be valid between 90 and -90 degrees

	pitch = glm::clamp(pitch, -glm::pi<float>() / 2 + 0.001f,
							   glm::pi<float>() / 2 - 0.001f);

	glm::mat4 tbn = glm::eulerAngleYXZ(yaw, pitch, roll);

	glm::vec3 right = glm::vec3(tbn[0]);
	glm::vec3 up = glm::vec3(tbn[1]);
	direction = glm::vec3(tbn[2]);

	//direction = glm::vec3(glm::rotate(yaw, glm::vec3(0, 1, 0))[2]);
	//right = glm::cross(direction, glm::vec3(0, 1, 0));
	
	//direction = glm::mat3(glm::rotate(pitch, right)) * direction;

	glm::vec3 moveDir = glm::vec3(0, 0, 0);

	if (in.getKeyState('W') == Input::DOWN)	moveDir += direction;
	if (in.getKeyState('S') == Input::DOWN)	moveDir -= direction;
	if (in.getKeyState('A') == Input::DOWN)	moveDir += right;
	if (in.getKeyState('D') == Input::DOWN)	moveDir -= right;
	if (in.getKeyState('E') == Input::DOWN)	moveDir -= up;
	if (in.getKeyState('Q') == Input::DOWN)	moveDir += up;


	if (glm::length(moveDir) >= .7f)
	{
		moveDir = glm::normalize(moveDir);
		position += moveDir * t.getDeltaTime() * speed;
	}
}
