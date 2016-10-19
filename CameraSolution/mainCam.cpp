#include "crenderutils.h"

#include "window.h"

#include "gotTime.h"
#include "Input.h"
#include "Camera.h"

#include "GLM\glm.hpp"
#include "GLM\ext.hpp"

#include "GridMaker.h"

int main()
{
	Window window;

	GotTime time;
	Input input;

	window.init(1280, 720, "bleh");

	input.init(window);
	time.init();

	unsigned char pixels[] = { 255, 255, 0 };

	unsigned tris[] = { 0,1,2, 2,3,0 };
	
	Shader gGrid = loadShader("TEXTURE", "../res/shaders/textureVert.txt",
		"../res/shaders/textureFrag.txt");

	float IDENTITY[16] = { 1,0,0,0,
						  0,1,0,0,
						  0,0,1,0,
						  0,0,0,1 };

	glm::mat4 model, view, proj, model3;

	Geometry plane = genGrid(512, 2);
	Texture	 noise = genNoise(64, 8);
	
	proj = glm::perspective(45.f, 1.f, 1.f, 50.f);

	float ct = 0;

	FlyCamera cam;

	cam.lookAt(glm::vec3(0, 0, 0));
	cam.jumpTo(glm::vec3(0, 0, -10));

	while (window.step())
	{
		time.step();
		input.step();

	
		ct += time.getDeltaTime();
		view = cam.getView();
		proj = cam.getProjection();
		
		cam.update(input, time);



	}

	input.term();
	time.term();
	window.term();
	return 0;
}
