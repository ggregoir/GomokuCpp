#include "UserInterface.h"

#include <SDL.h>
#include <iostream>

int main(int argc, char** argv) 
{
	sdl_ui visu;
	SDL_Event event;
	bool quit(false);

	visu.render();
	try
	{
		while (!quit)
		{
			SDL_WaitEvent(&event);
			if (event.key.keysym.sym == SDLK_ESCAPE)
			quit = true;
		}
	}
	catch (std::exception &e)
	{
		quit = true;
	}
}
