#include "UserInterface.h"
#include "GameManager.h"
#include "Parameters.h"
#include "Menu.h"
#include "macros.h"

#include <tuple>

#include <SDL.h>
#include <iostream>

using namespace std;

static void	run_ui(Parameters params)
{
	GameManager		manager(params);
	UserInterface	ui(params);
	SDL_Event		event;
	bool			quit = false;

	ui.render();
	while (!quit)
	{
		SDL_WaitEvent(&event);
		if (LEFT_CLICK(event))
		{
			auto new_stone = ui.pixel_to_pos(Position(event.button.x, event.button.y));
			if (manager.modify_board(new_stone.index(), manager.get_turn_color() + 1, params.rule == Connect4))
			{
				manager.change_player(params);
				if (manager.get_player())
					cout << "ia to play" << endl;
				else
					cout << "human to play" << endl;
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
	ui.FreeSDL();
}

int main(int ac, char **av) 
{
	Parameters		params;
	Menu			menu;

	if (ac == 1 || (strcmp(av[1], "--nomenu") && strcmp(av[1], "-n")))
		menu.loop(params);
	run_ui(params);
}
