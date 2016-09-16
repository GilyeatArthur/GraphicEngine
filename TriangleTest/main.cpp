

#include "crenderutils.h"
#include "window.h"
#include "Input.h"
#include "Vertex.h"
#include "gotTime.h"
#include "Camera.h"


#include "GLM\glm.hpp"
#include "GLM\ext.hpp"



int main()
{
	Window window;
	Input input;
	GotTime time;
	
	window.init(1280, 720, "Bleh");
	input.init(window);
	time.init();

	glm::mat4 view = glm::lookAt(glm::vec3(0.f, 1.5f, 20.f),  // eye
								 glm::vec3(0.f, 1.5f, 0.f),  // center
								 glm::vec3(0.f, 1.f, 0.f)); // up

	glm::mat4 proj = glm::perspective(45.f, 16 / 9.f, 1.f, 100.f);
	glm::mat4 modelC, modelSS;

	Geometry cube = loadOBJ("../res/models/cube.obj");
	Geometry soulS = loadOBJ("../res/models/soulspear.obj");

	Shader   shader = loadShader("../res/shaders/phongVert.glsl",
								 "../res/shaders/phongFrag.glsl");

	Texture tarray[] = { loadTexture("../res/textures/soulspear_diffuse.tga"),
						 loadTexture("../res/textures/soulspear_specular.tga"),
						 loadTexture("../res/textures/soulspear_normal.tga") };

	Framebuffer frame = makeFramebuffer(1280, 720, 1);
	Framebuffer screen = { 0, 1280, 720, 1 };

	Vertex verts[4] = { {{-1,-1,0,1},{},{},{0,0}},
						{{1,-1,0,1},{},{},{1,0}},
						{{1,1,0,1},{},{},{1,1}},
						{{-1,1,0,1},{},{},{0,1}} };

	unsigned tris[] = { 0,1,2,2,3,0 };
	
	Geometry quad = makeGeometry(verts, 4, tris, 6);

	Shader post = loadShader("../res/shaders/postVert.glsl", 
							 "../res/shaders/postFrag.glsl");
	float ct = 0;

	FlyCamera cam;

	while (window.step())
	{
		clearFramebuffer(frame);
		time.step();
		input.step();
		
		ct += time.getDeltaTime();
		view = cam.getView();
		proj = cam.getProjection();
		cam.update(input, time);

		view = glm::lookAt(glm::vec3(4,1,0), glm::vec3(0,1,0), glm::vec3(0,1,0));

		modelC  = glm::rotate(ct, glm::normalize(glm::vec3(0, 1.f, 0)));
		modelSS = glm::rotate(ct, glm::normalize(glm::vec3(0, .5f, 0)));

		//drawFB(post, quad, frame,
		//	glm::value_ptr(modelC),
		//	glm::value_ptr(view),
		//	glm::value_ptr(proj), tarray, 3);

		drawFB(shader, soulS, frame,
			glm::value_ptr(modelSS),
			glm::value_ptr(view),
			glm::value_ptr(proj), tarray, 3);

		drawFB(post, quad, screen, glm::value_ptr(glm::mat4(ct)), 
		glm::value_ptr(glm::mat4()),
			glm::value_ptr(glm::mat4()),
			frame.colors, frame.nColors);

		//drawPhong(shader, soulS, glm::value_ptr(modelSS),
		//	glm::value_ptr(view),
		//	glm::value_ptr(proj), tarray, 3);
	
		
	}
	freeFramebuffer(frame);
	freeShader(shader);
	freeGeometry(soulS);
	for each(auto &t in tarray) freeTexture(t);
	window.term();
	return 0;
}