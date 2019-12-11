#include "UserInterface.h"
#include "Position.h"
#include "Parameters.h"
#include "Board.h"

#include <string>
#include <iostream>

using namespace std;

UserInterface::UserInterface(Parameters params) : theme { "", "_space", "_dark" }
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1) 
	{
		cout << "Could not initialize SDL: " << SDL_GetError() << endl;
		exit(EXIT_FAILURE);
	}

	window = SDL_CreateWindow("Gomoku", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1470 * RATIO, 1470 * RATIO, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
		return ;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface *board = IMG_Load(("img/board" + theme[params.theme] + ".png").c_str());
    SDL_Surface *black = IMG_Load(("img/black" + theme[params.theme] + ".png").c_str());
    SDL_Surface *white = IMG_Load(("img/white" + theme[params.theme] + ".png").c_str());
    SDL_Surface *help = IMG_Load("img/help.png");
    SDL_Surface *last_played = IMG_Load("img/last_played.png");

	if (board == 0 || black == 0 || white == 0 || help == 0 || last_played == 0)
		return;
	SDL_SetColorKey(board, 0, SDL_MapRGB(board->format, 0, 0, 0));
	board_text = SDL_CreateTextureFromSurface(renderer, board);

	SDL_SetColorKey(black, 0, SDL_MapRGB(black->format, 0, 0, 0));
	black_text = SDL_CreateTextureFromSurface(renderer, black);

	SDL_SetColorKey(white, 0, SDL_MapRGB(white->format, 0, 0, 0));
	white_text = SDL_CreateTextureFromSurface(renderer, white);

	SDL_SetColorKey(help, 0, SDL_MapRGB(help->format, 0, 0, 0));
	help_text = SDL_CreateTextureFromSurface(renderer, help);

	SDL_SetColorKey(last_played, 0, SDL_MapRGB(last_played->format, 0, 0, 0));
	last_played_text = SDL_CreateTextureFromSurface(renderer, last_played);

	SDL_RenderCopy(renderer, board_text, NULL, NULL);

}

void	UserInterface::FreeSDL()
{
	SDL_DestroyTexture(black_text);
	SDL_DestroyTexture(white_text);
	SDL_DestroyTexture(board_text);
	SDL_DestroyTexture(help_text);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

Position	UserInterface::get_user_input(Position mouse)
{
	auto	pos = Position();
	pos.x = nearbyint((float)(mouse.x - 35 * RATIO) / (float)(70 * RATIO)) - 1;
	pos.y = nearbyint((float)(mouse.y - 35 * RATIO) / (float)(70 * RATIO)) - 1;

	if (pos.x == 19)
		pos.x = 18;
	if (pos.y == 19)
		pos.y = 18;
	if (pos.x == -1)
		pos.x = 0;
	if (pos.y == -1)
		pos.y = 0;
	return (pos);
}

void		UserInterface::print_board(board_t board, int last_move)
{
	for (int i = 0; i < BOARD_CAPACITY; ++i)
	{
		if (board[i] == 1)
			place_stone(1, Position(i % BOARD_SIZE, i / BOARD_SIZE));
		else if (board[i] == 2)
			place_stone(2, Position(i % BOARD_SIZE, i / BOARD_SIZE));
	}
	if (last_move >= 0)
	{
		printf("%d\n", last_move);
		place_stone(4, INDEX_TO_POS(last_move));
	}
}

void		UserInterface::place_stone(uint8_t color, Position stone)
{
	static SDL_Texture	*text_type[4] = {black_text, white_text, help_text, last_played_text};
	SDL_Rect	pos;

	pos.x = (stone.x + 1) * (70 * RATIO) + (10 * RATIO);
	pos.y = (stone.y + 1) * (70 * RATIO) + (10 * RATIO);
	pos.w = 50 * RATIO;
  	pos.h = 50 * RATIO;
	SDL_RenderCopy(renderer, text_type[color - 1], nullptr, &pos);
}


void		UserInterface::clear()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, board_text, NULL, NULL);
}

void	UserInterface::render()
{
	SDL_RenderPresent(renderer);
	SDL_RenderCopy(renderer, board_text, NULL, NULL);
}