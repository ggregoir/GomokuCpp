#include "UserInterface.h"
#include "GameManager.h"
#include "Parameters.h"
#include "Menu.h"
#include "macros.h"

#include <tuple>

#include <SDL.h>
#include <iostream>

using namespace std;

int main(int ac, char **av) 
{
	Parameters		params;
	Menu			menu;
	GameManager		manager;
	SDL_Event		event;
	bool			quit = false;

	if (ac == 1 || (strcmp(av[1], "--nomenu") && strcmp(av[1], "-n")))
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
				auto new_stone = ui.pixel_to_pos(Position(event.button.x, event.button.y));
				if (manager.modify_board(new_stone.index(), manager.get_turn_color() + 1))
				{
					auto res = manager.board.search_stone(manager.get_turn_color());
					cout << "Index of first stone found: " << res << endl;
					manager.change_turn();
				}
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
