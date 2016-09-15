

#include "crenderutils.h"
#include "window.h"
#include "Input.h"

#include "GLM\glm.hpp"
#include "GLM\ext.hpp"

int main()
{
	Window window;
	//Input input;
	window.init(1280, 720, "Bleh");
	//input.init(window);

	glm::mat4 view = glm::lookAt(glm::vec3(10.f, 10.f, 10.f),  // eye
								 glm::vec3(0.f, 1.2f, 0.f),  // center
								 glm::vec3(0.f, 1.f, 0.f)); // up

	glm::mat4 proj = glm::perspective(45.f, 16 / 9.f, 1.f, 50.f);
	glm::mat4 modelC, modelS, modelB, modelO, modelSS;

	Geometry cube = loadOBJ("../res/models/cube.obj");
	Geometry sphere = loadOBJ("../res/models/sphere.obj");
	//Geometry bunny = loadOBJ("../res/models/Bunny.obj");
	//Geometry city = loadOBJ("../res/models/Organodron_City.obj");
	Geometry soulS = loadOBJ("../res/models/soulspear.obj");
	Shader   shader = loadShader("../res/shaders/phongVert.glsl",
								 "../res/shaders/phongFrag.glsl");

	Texture tarray[] = { loadTexture("../res/textures/soulspear_diffuse.tga"),
						 loadTexture("../res/textures/soulspear_specular.tga"),
						 loadTexture("../res/textures/soulspear_normal.tga") };

	float time = 0;
	while (window.step())
	{
		//input.step();

		time += 0.016f;
		modelSS = glm::rotate(time, glm::normalize(glm::vec3(0, .5f, 0)));


		drawPhong(shader, soulS, glm::value_ptr(modelSS),
			glm::value_ptr(view),
			glm::value_ptr(proj), tarray, 3);
	
		
	}

	window.term();
	return 0;
}