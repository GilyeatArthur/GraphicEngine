#pragma once

#include "GLM\glm.hpp"
#include "GLM\ext.hpp"

class FlyCamera
{

	glm::vec3 position;
	glm::vec3 direction;

	//Pitch is along the X
	// Yaw is along the Y
	//Roll is along the Z
	float pitch, yaw, roll;

	// make sure near is > 0
	float aspect, fov, near, far;
	float speed;
public:
	FlyCamera(float a_aspect = 16.f/9.f, float a_fov = 45.f, float a_near = 1, float a_far = 1000)
		: aspect(a_aspect), fov(a_fov), near(a_near), far(a_far), 
		direction(0, 0, 1), speed(20), pitch(0), yaw(0), roll(0)
	{

	}

	void update(const class Input &, const class GotTime &);

	void lookAt(const glm::vec3 target)
	{
		direction = glm::normalize(target - position);
	}

	void jumpTo(const glm::vec3 location)
	{
		position = location;
	}

	glm::mat4 getView() const
	{
		return glm::lookAt(position, position + direction, glm::vec3(0, 1, 0));
	}
		
	glm::mat4 getProjection() const
	{
		return glm::perspective(fov, aspect, near, far);
	}
};