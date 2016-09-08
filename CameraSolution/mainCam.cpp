#include "crenderutils.h"

#include "window.h"
#include "Gallery.h"
#include "gotTime.h"
#include "Input.h"
#include "Camera.h"

#include "GLM\glm.hpp"
#include "GLM\ext.hpp"

#include "GridMaker.h"

int main()
{
	Window window;
	Gallery gallery;
	GotTime time;
	Input input;

	window.init(1280, 720, "bleh");
	gallery.init();
	input.init(window);
	time.init();

	unsigned char pixels[] = { 255, 255, 0 };

	Texture tex = loadTexture("../res/textures/crate.jpg");

	unsigned tris[] = { 0,1,2, 2,3,0 };
	
	gallery.loadShader("TEXTURE", "../res/shaders/textureVert.txt",
								  "../res/shaders/textureFrag.txt");

	gallery.loadObjectOBJ("SPHERE", "../res/models/sphere.obj");
	gallery.loadObjectOBJ("CUBE", "../res/models/cube.obj");

	gallery.loadTexture("BOX", "../res/textures/PrizeBox.png");

	float IDENTITY[16] = { 1,0,0,0,
						  0,1,0,0,
						  0,0,1,0,
						  0,0,0,1 };

	glm::mat4 model, view, proj, model3;

	Geometry plane = genGrid(512, 2);
	Texture	 noise = genNoise(64, 8);
	
	proj = glm::perspective(45.f, 1.f, 1.f, 50.f);
	//view = glm::lookAt(glm::vec3(4, 4, 4), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

	//model = glm::scale(glm::vec3(1.5f, 1.5f, 1.5f));

	//model3 = glm::translate(glm::vec3(0, 0, 1))  * glm::rotate(0.f, glm::vec3(1, 1, 1)) * glm::scale(glm::vec3(5, 5, 5));

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

		model = glm::translate(glm::vec3(0, 0, 1)) *
				glm::rotate(ct, glm::vec3(0, 0, 0));

		/*drawTex(gallery.getShader("TEXTURE"),
			gallery.getObject("CUBE"), 
			gallery.getTexture("BOX"),
			glm::value_ptr(model3),
			glm::value_ptr(view),
			glm::value_ptr(proj), ct);*/

		model3 = glm::translate(glm::vec3(0, 0, 0))  * 
				 glm::rotate(180.f, glm::vec3(0, 1, 0)) * 
				 glm::scale(glm::vec3(5, 5, 5));


		drawTex(gallery.getShader("TEXTURE"),
			plane,
			noise,
			glm::value_ptr(model3),
			glm::value_ptr(view),
			glm::value_ptr(proj), ct);


	}

	freeTexture(tex);

	input.term();
	time.term();
	gallery.term();
	window.term();
	return 0;
}
