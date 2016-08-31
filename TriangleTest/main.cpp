

#include "crenderutils.h"

#include "window.h"
#include "Gallery.h"

//bleh

int main()
{
	Window window;
	Gallery gallery;

	window.init(800, 800, "bleh");
	gallery.init();

	Vertex	 vert[] = { {  1,  1, 0, 1 },
						{  1, -1, 0, 1 },
						{ -1, -1, 0, 1 },
						{ -1,  1, 0, 1 } };
	
	unsigned tris[] = { 0,1,2, 2,3,0 };

	Geometry geometry1 = makeGeometry(vert, 3, tris, 3);

	Shader shader1 = makeShader("../res/shaders/simpleVert.txt",
								"../res/shaders/simpleFrag.txt");

	gallery.loadShader("FUN", "../res/shaders/simpleVert.txt",
							  "../res/shaders/simpleFrag.txt");

	gallery.loadObjectOBJ("SPHERE", "../res/models/sphere.obj");

	gallery.makeObject("quad", vert, 4, tris, 6);


	float time = 0;
	while (window.step())
	{
		time += 0.016667f;
		draw(gallery.getShader("FUN"), gallery.getObject("quad"), time);
	}

	gallery.term();
	window.term();
	return 0;
}


