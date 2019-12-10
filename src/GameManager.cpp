#include "GameManager.h"
#include "Position.h"
#include "UserInterface.h"

#include <SDL.h>
#include <stdio.h>
#include <chrono>

using namespace std;

GameManager::GameManager(Parameters params)
{
	this->params = params;
	turn = false;
	if (params.priority == true)
		player = true;
	else
		player = false;
}

GameManager::~GameManager() {}

bool		GameManager::modify_board(uint32_t new_index, uint8_t stone, bool c4_rule)
{
	if (board[new_index] != 0)
		return false;
	if (c4_rule)
	{
		while (new_index < BOARD_CAPACITY - BOARD_SIZE && board[new_index + 19] == 0)
			new_index += 19;
	}
	board.update(new_index, stone);
	history.push_back(make_tuple(new_index, stone));
	return true;
}

uint32_t	GameManager::get_last_move()
{
	return get<0>(history.back());
}

Board		GameManager::get_board()
{
	return board;
}

bool		GameManager::player_mode()
{
	return player;
}

string		GameManager::player_mode_name()
{
	return player_mode() ? "Human" : "Engine";
}

uint8_t		GameManager::current_color()
{
	return (uint8_t)turn;
}

string		GameManager::current_color_name()
{
	return current_color() ? "white" : "black";
}

void		GameManager::change_player_turn()
{
	turn = !turn;
	if (params.mode != PlayerVsPlayer && params.mode != EngineVsEngine)
		player = !player;
}

void		GameManager::run_loop()
{
	UserInterface	ui(params);
	SDL_Event		event;
	bool			quit = false;

	ui.render();
	while (!quit)
	{
		SDL_WaitEvent(&event);
		if (player_mode() == Human && LEFT_CLICK(event))
		{
			auto input = ui.get_user_input(Position(event.button.x, event.button.y));
			if (modify_board(input.index(), current_color() + 1, params.rule == Connect4))
			{
				printf("Player %s (human) played at position (%d, %d)\n",
					current_color_name().c_str(), input.x, input.y);
				change_player_turn();
			}
			else
				printf("Warning - cannot add a stone at position (%d, %d)\n", input.x, input.y);
			ui.print_board(get_board(), get_last_move());
			ui.render();
		}
		else if (player_mode() == Engine)
		{
			auto beg = std::chrono::system_clock::now();
			// Run negamax here
			auto output = Position(0, 0);
			auto end = std::chrono::system_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - beg);
			printf("Player %s (engine) played at position (%d, %d) in %lld ms\n",
				current_color_name().c_str(), output.x, output.y, duration.count());
			change_player_turn();
		}
		if (CLOSE_EVENT(event))
		{
			quit = true;
			printf("Exit requested by user. Exiting now...\n");
		}
	}
	ui.FreeSDL();
}