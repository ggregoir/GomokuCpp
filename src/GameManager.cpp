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
	player = false;
	if (params.priority == true && params.mode != EngineVsEngine)
		player_mode = Human;
	else
		player_mode = Engine;
}

GameManager::~GameManager() {}

size_t		GameManager::get_connect4_index(size_t index)
{
	while (index < BOARD_CAPACITY - BOARD_SIZE && board.get(index + BOARD_SIZE) == Empty)
		index += BOARD_SIZE;
	return index;
}

string		GameManager::current_player_color()
{
	return player ? "white" : "black";
}

void		GameManager::change_player_turn()
{
	player = !player;
	if (params.mode != PlayerVsPlayer && params.mode != EngineVsEngine)
	{
		player_mode = 1 - player_mode;
	}
}

bool		GameManager::can_place(size_t index, uint8_t player)
{
	(void)player;
	return board.get(index) == Empty;
}

void		GameManager::play_move(size_t index, uint8_t player)
{
	board.add(index, player);
	add_in_history(board.get_board(), index);
}

void		GameManager::add_in_history(board_t board, size_t last_move)
{
	history.push_back(History { board, last_move });
}

int			GameManager::get_last_move()
{
	return history.size() ? history.back().last_move : -1;
}

size_t		GameManager::dumb_algo(board_t grid)
{
	for (size_t i = 0; i < BOARD_CAPACITY; i++)
	{
		if (grid[i] == 0)
			return i;
	}
	return 0;
}

void		GameManager::run_loop()
{
	UserInterface	ui(params);
	SDL_Event		event;
	bool			quit = false;

	ui.render();
	while (!quit)
	{
		if (player_mode == Human)
		{
			SDL_WaitEvent(&event);
			if (UNDO_EVENT(event))
			{
				if (history.size() > 0)
					history.pop_back();
				if (history.size() > 0)
					history.pop_back();
				if (history.size() == 0)
				{
					board_t	new_board;
					std::fill(new_board.begin(), new_board.end(), 0);
					board.update(new_board);
				}
				else
					board.update(history.back().board);
				ui.print_board(board.get_board(), get_last_move());
				ui.render();
			}
			if (LEFT_CLICK(event))
			{
				auto stone = ui.get_user_input(Position(event.button.x, event.button.y));
				if (can_place(stone.index(), player))
				{
					play_move(stone.index(), player);
					printf("Player %s (human) played at position (%d, %d)\n",
						current_player_color().c_str(), stone.x, stone.y);
					change_player_turn();
				}
				else
					printf("Warning - cannot add a stone at position (%d, %d)\n", stone.x, stone.y);

				ui.print_board(board.get_board(), get_last_move());
				ui.render();
			}
		}
		else
		{
			SDL_PollEvent(&event);
			auto start = chrono::system_clock::now();
			// Run negamax here
			auto stone = INDEX_TO_POS(dumb_algo(board.get_board()));
			auto end = chrono::system_clock::now();
			auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
			if (can_place(stone.index(), player))
			{
				play_move(stone.index(), player);
				printf("Player %s (engine) played at position (%d, %d) in %lld ms\n",
					current_player_color().c_str(), stone.x, stone.y, duration.count());
				change_player_turn();
			}
			else
				printf("Warning - cannot add a stone at position (%d, %d)\n", stone.x, stone.y);

			ui.print_board(board.get_board(), get_last_move());
			ui.render();
		}
		if (CLOSE_EVENT(event))
		{
			quit = true;
			printf("Exit requested by user. Exiting now...\n");
		}
	}
	ui.FreeSDL();
}