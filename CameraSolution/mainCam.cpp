#include "crenderutils.h"

#include "window.h"
#include "Gallery.h"
#include "gotTime.h"
#include "Input.h"
#include "Camera.h"

#include "GLM\glm.hpp"
#include "GLM\ext.hpp"

int main()
{
	Window window;
	Gallery gallery;
	Input input;
	GotTime time;

	window.init(1280, 720, "bleh");
	gallery.init();
	input.init(window);
	time.init();


	Vertex	 vert[] = { { 1, 1, 0, 1 },
						{ 1, -1, 0, 1 },
						{ -1, -1, 0, 1 },
						{ -1,  1, 0, 1 } };

	unsigned tris[] = { 0,1,2, 2,3,0 };

	gallery.loadShader("CAMERA", "../res/shaders/cameraVert.txt",
		"../res/shaders/cameraFrag.txt");
	gallery.makeObject("quad", vert, 4, tris, 6);
	gallery.loadObjectOBJ("SPHERE", "../res/models/sphere.obj");
	gallery.loadObjectOBJ("CUBE", "../res/models/cube.obj");
	//gallery.loadObjectOBJ("CITY", "../res/models/Organodron_City.obj");


	float IDENTITY[16] = { 1,0,0,0,
						  0,1,0,0,
						  0,0,1,0,
						  0,0,0,1 };

	glm::mat4 model, view, proj, model3;


	proj = glm::ortho<float>(-10, 10, -10, 10, -10, 10);

	proj = glm::perspective(45.f, 1.f, .001f, 100.f);

	
	model = glm::scale(glm::vec3(1.5f, 1.5f, 1.5f));

	model3 = glm::translate(glm::vec3(-10, 0, 0))  * glm::rotate(180.f, glm::vec3(0, 1, 0)) * glm::scale(glm::vec3(5, 5, 5));

	float ct = 0;

	FlyCamera cam;
	cam.jumpTo(glm::vec3(10, 0, 0));
	cam.lookAt(glm::vec3(0, 0, 0));

	while (window.step())
	{
		time.step();
		input.step();

	
		cam.update(input, time);
		view = cam.getView();
		proj = cam.getProjection();
		
		cam.update(input, time);

		ct += time.getDeltaTime();



		model = glm::translate(glm::vec3(0, ct, 0)) *
				glm::rotate(ct, glm::vec3(0, 1, 0));



		drawCam(gallery.getShader("CAMERA"),
			gallery.getObject("CUBE"),
			glm::value_ptr(model3),
			glm::value_ptr(view),
			glm::value_ptr(proj), ct);


	}

	gallery.term();
	window.term();
	return 0;
}
