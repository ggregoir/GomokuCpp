#include "UserInterface.h"

#include <SDL.h>
#include <iostream>

int main(int argc, char** argv) 
{
	UserInterface	ui;
	SDL_Event		event;
	bool			quit = false;

	ui.render();
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
