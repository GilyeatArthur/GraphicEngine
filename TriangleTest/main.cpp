

#include "crenderutils.h"

#include "GLM\ext.hpp"

void main()
{
	Window context;
	context.init(1280, 720, "bleh");

	Framebuffer screen = { 0,1280,720 };

	Geometry quad = makeGeometry(quad_verts, 4, quad_tris, 6);

	Shader simple = loadShader("../res/shaders/simple.vert", "../res/shaders/simple.frag");

	Texture img = loadTexture("../res/textures/Dr BEES.jpg");

	Geometry spear = loadOBJ("../res/models/soulspear.obj");

	Texture spear_normal = loadTexture("../res/textures/soulspear_normal.tga");
	Texture spear_diffuse = loadTexture("../res/textures/soulspear_diffuse.tga");
	Texture spear_specular = loadTexture("../res/textures/soulspear_specular.tga");

	glm::mat4 model, view, proj;

	model = glm::translate(glm::vec3(0, -1, 0));
	view = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 2, 0), glm::vec3(0, 1, 0));
	proj = glm::perspective(45.f, 1280.f / 720, 1.f, 100.f);

	float time = 0;
	while (context.step())
	{
		time += 0.016f;
		tdraw(simple, spear, screen, model, view, proj, spear_diffuse, spear_normal, spear_specular);
	}

	context.term();
}