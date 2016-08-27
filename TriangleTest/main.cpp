

#include "crenderutils.h"

#include "window.h"
#include "Gallery.h"

int main()
{
	Window window;
	Gallery gallery;

	window.init(800, 800, "bleh");
	gallery.init();

	Vertex	 vert[4] = { { 1, 1, 1, 1, 1,0,0,1 },
						 { 1, 1, 0, 1, 1,0,0,1 },
						 { 1, 0, 1, 1, 1,0,0,1 },
						 { 0, 1, 1, 1, 1,0,0,1 } };
	
	unsigned tris[6] = { 0, 1, 2, 0, 1, 3 };

	Geometry geometry1 = makeGeometry(vert, 4, tris, 4);

	Shader shader1 = makeShader("../res/shaders/simpleVert.txt",
								"../res/shaders/simpleFrag.txt");

	gallery.loadShader("FUN", "../res/shaders/simpleVert.txt",
							  "../res/shaders/simpleFrag.txt");

	gallery.loadObjectOBJ("SPHERE", "../res/models/cube.obj");
	
	float time = 0;

	while (window.step())
	{
		time += 0.016667f;
		//draw(gallery.getShader("FUN"), gallery.getObject("SPHERE"), time);
	}

	while (window.step())
	{
		//time += 0.016667f;
		draw(shader1, geometry1, 1);
	}

	freeGeometry(geometry1);
	freeShader(shader1);

	gallery.term();
	window.term();
	return 0;
}


