
//#include "crenderutils.h"
#include "window.h"
//Context-Feature branch note
int main()
{
	Window window;
	window.init(800, 600, "bleh");

	while (window.step());

	window.term();
	
	return 0;
}


