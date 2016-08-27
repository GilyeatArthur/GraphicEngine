

#include "crenderutils.h"

#include "window.h"
#include "Gallery.h"

int main()
{
	Window window;
	Gallery gallery;

	window.init(800, 800, "bleh");
	gallery.init();

	gallery.loadShader("FUN", "../res/shaders/simpleVert.txt",
							  "../res/shaders/simpleFrag.txt");

	gallery.loadObjectOBJ("SPHERE", "../res/models/cube.obj");
	
	float time = 0;

	while (window.step())
	{
		time += 0.016667f;
		draw(gallery.getShader("FUN"), gallery.getObject("SPHERE"), time);
	}

	gallery.term();
	window.term();
	return 0;
}


