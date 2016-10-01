

#include "crenderutils.h"

#include "GLM\ext.hpp"

struct RenderComponent
{
	//This will modify the model's matrix to fit with the rest of the objects

	glm::mat4 model;
	Geometry mesh;

	Texture norm, diff, spec;

	static Shader shader;
	static Framebuffer fb;

	//gpass shader for this object.
	//draw(Shader, Target, Transform)
		//tdraw(...);
};

struct DirectionalLight
{
	glm::vec3 dir, color;
	float size;
	glm::mat4 getMatrix()
	{
		return glm::ortho<float>(-size, size, -size, size, -size, size) 
			* glm::lookAt(-dir, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	}
};

void main()
{
	Window context;
	context.init(1280, 720, "bleh");

		
	Geometry quad = makeGeometry(quad_verts, 4, quad_tris, 6);
	Geometry spear = loadOBJ("../res/models/soulspear.obj");
	Geometry sphere = loadOBJ("../res/models/sphere.obj");
	
	Geometry gaige[25];
	int gaige_count = loadAllOBJ("../res/models/Gaige.obj", gaige, 25);

	//Soul Spear
	Texture spear_diffuse = loadTexture("../res/textures/soulspear_diffuse.tga");
	Texture spear_normal = loadTexture("../res/textures/soulspear_normal.tga");
	Texture spear_specular = loadTexture("../res/textures/soulspear_specular.tga");

	Texture spear_Textures[3] = { spear_diffuse, spear_normal, spear_specular };
	
	//Gaige
	Texture gaige_arms  = loadTexture("../res/textures/arms.tga");
	Texture gaige_body  = loadTexture("../res/textures/body.tga");
	Texture gaige_face  = loadTexture("../res/textures/face.tga");
	Texture gaige_iris  = loadTexture("../res/textures/iris.tga");
	Texture gaige_mouth = loadTexture("../res/textures/mouth.tga");

	Texture gaige_Textures[5] = { gaige_arms, gaige_body, gaige_face, gaige_iris, gaige_mouth };

	const unsigned char norm_pixels[4] = { 127,127,255,255 };
	Texture vertex_normals = makeTexture(1, 1, 4, norm_pixels);

	const unsigned char white_pixels[4] = { 255,255,255,255 };
	Texture white = makeTexture(1, 1, 4, white_pixels);

	Shader qdraw = loadShader("../res/shaders/quad.vert", "../res/shaders/quad.frag", false);
	Shader gpass = loadShader("../res/shaders/gpass.vert", "../res/shaders/gpass.frag");
	Shader gGirl = loadShader("../res/shaders/gaige.vert", "../res/shaders/gaige.frag");

	// Light shader pass
	Shader spass = loadShader("../res/shaders/spass.vert", "../res/shaders/spass.frag", true, false, false);
	Shader lpass = loadShader("../res/shaders/lpass.vert", "../res/shaders/lpass.frag", false, true);

	Framebuffer screen = { 0, 1280, 720 };

	// colors don't need floats, but position/normal should use it.
	bool isFtex[] = { false, true, false, true };
	Framebuffer gframe = makeFramebuffer(1280, 720, 4, isFtex);
	Framebuffer lframe = makeFramebuffer(1280, 720, 3);

	//resolution quality
	Framebuffer sframe = makeFramebuffer(4096, 4096, 0);

	//Camera
	glm::mat4 camView = glm::lookAt(glm::vec3(0, 0, 4), glm::vec3(0, 0, 0), glm::vec3(0, 2, 0));
	glm::mat4 camProj = glm::perspective(45.f, 1280.f / 720, 1.f, 200.f);

	// model matricies
	glm::mat4 spearModel;
	glm::mat4 sphereModel = glm::translate(glm::vec3(0.3f, -1, -0.2));
	glm::mat4 wallModel = glm::rotate(45.f, glm::vec3(0, -1, 0))*glm::translate(glm::vec3(0, 0, -2))*glm::scale(glm::vec3(2, 2, 1));
	glm::mat4 gaigeModel = glm::translate(glm::vec3(0, -2.f, 0))*glm::scale(glm::vec3(.05f, .05f, .05f))*glm::rotate(90.f, -glm::vec3(1, 0, 0));

	//light matrices and data
	glm::mat4 lightProj = glm::ortho<float>(-10, 10, -10, 10, -10, 10);

	glm::mat4 redView = glm::lookAt(glm::normalize(-glm::vec3(1, -1, -1)), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::vec4 redColor = glm::vec4(1, 0, 0, 1);

	glm::mat4 greenView = glm::lookAt(glm::normalize(-glm::vec3(1, 1, -1)), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::vec4 greenColor = glm::vec4(0, 1, 0, 1);

	float time = 0;

	while (context.step())
	{
		time += 0.016f;
		spearModel = glm::rotate(time, glm::vec3(0, 1, 0)) * glm::translate(glm::vec3(0, -1, 0));
		//gaigeModel = glm::rotate(time, glm::vec3(0, 1, 0)) * glm::translate(glm::vec3(0, -1, 0));



		//Geometry pass
		clearFramebuffer(gframe);
		tdraw(gpass, spear, gframe, spearModel, camView, camProj, spear_diffuse, spear_normal, spear_specular);
		tdraw(gpass, sphere, gframe, sphereModel, camView, camProj, white, vertex_normals, white);
		tdraw(gpass, quad, gframe, wallModel, camView, camProj, white, vertex_normals, white);
	
		for (int i = 0; i < gaige_count; ++i)
		{
			tdraw(gpass, gaige[i], gframe, gaigeModel, camView, camProj, white, vertex_normals, white);
		}

		//lighting pass
		clearFramebuffer(lframe);

		//Red light
		clearFramebuffer(sframe);
		tdraw(spass, spear,  sframe, spearModel,  redView, lightProj);
		tdraw(spass, sphere, sframe, sphereModel, redView, lightProj);
		tdraw(spass, quad,   sframe, wallModel,   redView, lightProj);

		for (int i = 0; i < gaige_count;++i)
		{
			tdraw(spass, gaige[i], sframe, gaigeModel, redView, lightProj);
		}

		//light aggregation
		tdraw(lpass, quad, lframe, camView,
			gframe.colors[0], gframe.colors[1], gframe.colors[2], gframe.colors[3],
			sframe.depth, redColor, redView, lightProj);

		//Green light
		clearFramebuffer(sframe);
		tdraw(spass, spear,  sframe, spearModel,  greenView, lightProj);
		tdraw(spass, sphere, sframe, sphereModel, greenView, lightProj);
		tdraw(spass, quad,   sframe, wallModel,   greenView, lightProj);

		for (int i = 0; i < gaige_count; ++i)
		{
			tdraw(spass, gaige[i], sframe, gaigeModel, greenView, lightProj);
		}

		//light aggregation
		tdraw(lpass, quad, lframe, camView,
			gframe.colors[0], gframe.colors[1], gframe.colors[2], gframe.colors[3],
			sframe.depth, greenColor, greenView, lightProj);

		//debug rendering stuff
		Texture debug_list[] = { gframe.colors[0], gframe.colors[1], gframe.colors[2], gframe.colors[3],
			gframe.depth, lframe.colors[1], lframe.colors[2], sframe.depth };

		for (int i = 0; i < sizeof(debug_list) / sizeof(Texture); ++i)
		{
			glm::mat4 mod = glm::translate(glm::vec3(-.75f + .5f*(i % 4), 0.75f - .5f*(i / 4), 0))
				* glm::scale(glm::vec3(0.25f, 0.25f, 1.f));
			tdraw(qdraw, quad, screen, debug_list[i], mod);
		}

		glm::mat4 mod =
			glm::translate(glm::vec3(-.5f, -0.5f, 0)) *
			glm::scale(glm::vec3(0.5f, 0.5f, 1.f));
	
		tdraw(qdraw, quad, screen, lframe.colors[0], mod);

		//tdraw(qdraw, quad, screen, glm::mat4(), lframe.colors[0]);
	}

	context.term();
}