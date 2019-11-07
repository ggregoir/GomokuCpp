#include "UserInterface.h"
#include "GameManager.h"
#include "Parameters.h"
#include "Menu.h"

#include <SDL.h>
#include <iostream>

using namespace std;

int main() 
{
	Parameters		params;
	Menu			menu;
	GameManager		manager;
	SDL_Event		event;
	bool			quit = false;

	menu.loop(params);
	UserInterface	ui(params);
	ui.render();
	try
	{
		while (!quit)
		{
			SDL_WaitEvent(&event);

			if (LEFT_CLICK(event))
			{
				auto color_turn = manager.get_turn_color();
				auto new_stone = ui.pixel_to_pos(Position { event.button.x, event.button.y });
				if (manager.modify_board(POS_TO_INDEX(new_stone), color_turn))
					manager.change_turn();
				else
					cout << "Cannot add a stone here" << endl;

				ui.print_board(manager.get_board(), manager.get_last_move());
				ui.render();
			}
			if (CLOSE_EVENT(event))
			{
				cout << "ESCAPE KEY PRESSED" << endl;
				quit = true;
			}
		}
	}
	catch (std::exception &e)
	{
		quit = true;
	}
}
