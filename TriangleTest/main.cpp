
#include "crenderutils.h"
#include "window.h"
#include "Vertex.h"

int main()
{
	Window window;
	window.init(800, 600, "bleh");

	Vertex	 vert[3] = { {   0,  .5f, 0, 1, 0,0,0,0},
						 { .5f, -.5f, 0, 1, 0,0,0,0},
						 {-.5f, -.5f, 0, 1, 0,0,0,0} };
	unsigned tris[3] = {0, 1, 2};

	Geometry geometry = makeGeometry(vert, 3, tris, 9);

	Shader shader = loadShader("../res/shaders/simpleVert.txt",
							   "../res/shaders/simpleFrag.txt");

	while (window.step())
	{
		draw(shader, geometry);
	}

	freeGeometry(geometry);
	freeShader(shader);
	window.term();
	return 0;
}


