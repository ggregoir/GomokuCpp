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

			if (event.button.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && event.button.windowID == 1)
			{
				auto test = ui.pixel_to_index(Position { event.button.x, event.button.y });
				ui.place_stone(1, Position { test.x, test.y });
				ui.place_stone(1, Position { test.x + 1, test.y + 1 });
				ui.render();
			}
			if (event.key.keysym.sym == SDLK_ESCAPE)
				quit = true;
		}
	}
	catch (std::exception &e)
	{
		quit = true;
	}
}
