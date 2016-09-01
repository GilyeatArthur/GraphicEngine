#include "crenderutils.h"

#include "window.h"
#include "Gallery.h"

#include "GLM\glm.hpp"
#include "GLM\ext.hpp"

int main()
{
	Window window;
	Gallery gallery;

	window.init(800, 800, "bleh");
	gallery.init();

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

	float IDENTITY[16] = { 1,0,0,0,
						  0,1,0,0,
						  0,0,1,0,
						  0,0,0,1 };

	glm::mat4 model, view, proj, model2, model3, model4;


	proj = glm::ortho<float>(-10, 10, -10, 10, -10, 10);

	proj = glm::perspective(45.f, 1.f, .001f, 100.f);

	


	model = glm::scale(glm::vec3(1.5f, 1.5f, 1.5f));


	float time = 0;
	while (window.step())
	{
		time += 0.01666f;

		view = glm::lookAt(glm::vec3(5.f, 5.f, 5.f),
						   glm::vec3(0.f, 0.f, 0.f),
						   glm::vec3(0.f, 1.f, 0.f));

		model  = glm::rotate(time, glm::vec3(0, -1, 0));
		model2 = glm::rotate(time, glm::vec3(-1, 1, 0));
		model3 = glm::rotate(time, glm::vec3(-1, 1, -1));
		model4 = glm::rotate(time, glm::vec3(-1, 1, 1));

		drawCam(gallery.getShader("CAMERA"), 
			gallery.getObject("SPHERE"), 
			glm::value_ptr(model * glm::translate(glm::vec3(1.5, 1.5, 1.5))),
			glm::value_ptr(view), 
			glm::value_ptr(proj));

		drawCam(gallery.getShader("CAMERA"),
			gallery.getObject("CUBE"),
			glm::value_ptr(model2 * glm::translate(glm::vec3(1.5,1.5,1.5))),
			glm::value_ptr(view),
			glm::value_ptr(proj));

		drawCam(gallery.getShader("CAMERA"),
			gallery.getObject("CUBE"),
			glm::value_ptr(model3 * glm::translate(glm::vec3(1.5, 1.5, 1.5))),
			glm::value_ptr(view),
			glm::value_ptr(proj));

		drawCam(gallery.getShader("CAMERA"),
			gallery.getObject("CUBE"),
			glm::value_ptr(model4 * glm::translate(glm::vec3(1.5, 1.5, 1.5))),
			glm::value_ptr(view),
			glm::value_ptr(proj));
	}

	gallery.term();
	window.term();
	return 0;
}
