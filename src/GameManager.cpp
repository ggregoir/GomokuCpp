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

void		GameManager::change_player_turn()
{
	player = !player;
	if (params.mode != PlayerVsPlayer && params.mode != EngineVsEngine)
	{
		player_mode = 1 - player_mode;
	}
}

bool		GameManager::can_place(size_t index, uint8_t player, Parameters params)
{
	if (params.rule == Restricted && board.get(index) == Empty)
	{
		if (board.check_double_freethree(index, player))
			return false;
	}
	return board.get(index) == Empty;

}

void		GameManager::play_move(size_t index, uint8_t player)
{
	if (params.rule == Restricted)
		board.check_capture(index, 1 - player);
	board.add(index, player);
	
	add_in_history(board.get_board(), index);
}

void		GameManager::add_in_history(board_t board, int last_move)
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

void		GameManager::load_history()
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
}

GameStatus	GameManager::is_endgame(uint32_t index, uint8_t player)
{
	if (board.is_draw())
		return Draw;
	else if (board.check_win(index, player))
		return player == 0 ? PlayerOneWin : PlayerTwoWin;
	return Playing;
}

void		GameManager::print_game_status(GameStatus status)
{
	if (status == Draw)
		printf("Draw !\n");
	else
	{
		printf("Player %d won the game !\n", status);
	}
}

void		GameManager::run_loop()
{
	UserInterface	ui(params);
	SDL_Event		event;
	bool			quit = false;
	GameStatus 		game_status = Playing;
	bool			end_turn = false;
	Position		stone(0, 0);

	ui.render();
	while (!quit)
	{
		SDL_WaitEvent(&event);
		while (game_status == 0)
		{
			if (player_mode == Human)
			{
				SDL_WaitEvent(&event);
				if (UNDO_EVENT(event))
				{
					load_history();
					ui.print_board(board.get_board(), get_last_move());
				}
				if (LEFT_CLICK(event))
				{
					stone = ui.get_user_input(Position(event.button.x, event.button.y));
					if (can_place(stone.index(), player, params))
					{
						play_move(stone.index(), player);
						printf("Player %d (human) played at position (%d, %d)\n", player + 1, stone.x, stone.y);
						end_turn = true;
					}
					else
						printf("Warning - cannot add a stone at position (%d, %d)\n", stone.x, stone.y);

					ui.print_board(board.get_board(), get_last_move());
				}
			}
			else
			{
				SDL_PollEvent(&event);
				auto start = chrono::system_clock::now();
				// Run negamax here
				stone = INDEX_TO_POS(dumb_algo(board.get_board()));
				auto end = chrono::system_clock::now();
				auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
				if (can_place(stone.index(), player, params))
				{
					play_move(stone.index(), player);
					printf("Player %d (engine) played at position (%d, %d) in %lld ms\n",
						player + 1, stone.x, stone.y, duration.count());
					end_turn = true;
				}
				else
					printf("Warning - cannot add a stone at position (%d, %d)\n", stone.x, stone.y);

				ui.print_board(board.get_board(), get_last_move());
			}
			
			if (end_turn == true)
			{
				if ((game_status = is_endgame(stone.index(), player)))
					print_game_status(game_status);
				change_player_turn();
				end_turn = false;
			}
			
			if (CLOSE_EVENT(event))
			{
				quit = true;
				break;
			}
		}
		if (CLOSE_EVENT(event))
		{
			quit = true;
			printf("Exit requested by user. Exiting now...\n");
		}
	}
	ui.FreeSDL();
}