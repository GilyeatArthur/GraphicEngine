

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

	gallery.loadObjectOBJ("SPHERE", "../res/models/sphere.obj");
	

	while (window.step())
	{
		draw(gallery.getShader("FUN"),gallery.getObject("SPHERE"));
	}

	gallery.term();
	window.term();
	return 0;
}


