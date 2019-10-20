#include "UserInterface.h"

#include <iostream>

using namespace std;

UserInterface::UserInterface() :
index_x { 116, 169, 222, 276, 329, 383, 436, 490, 544, 598, 652, 705, 759, 813, 867, 921, 975, 1029, 1083 },
index_y { 104, 160, 216, 272, 328, 385, 441, 497, 553, 610, 666, 723, 779, 835, 892, 948, 1005, 1062, 1118 }
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1) 
	{
		cout << "Could not initialize SDL: " << SDL_GetError() << endl;
		exit(EXIT_FAILURE);
	}

	window = SDL_CreateWindow("Gomoku", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1200, 1200, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
		return ;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface *board = IMG_Load("img/board.png");
    SDL_Surface *black = IMG_Load("img/black2.png");
    SDL_Surface *white = IMG_Load("img/white.png");
    SDL_Surface *help = IMG_Load("img/help.png");
    SDL_Surface *last_played = IMG_Load("img/last_played.png");

	if (board == 0 || black == 0 || white == 0 || help == 0 || lastplayed == 0)
		return;
	SDL_SetColorKey(board, 0, SDL_MapRGB(board->format, 0, 0, 0));
	board_text = SDL_CreateTextureFromSurface(renderer, board);

	SDL_SetColorKey(black, 0, SDL_MapRGB(black->format, 0, 0, 0));
	black_text = SDL_CreateTextureFromSurface(renderer, black);

	SDL_SetColorKey(white, 0, SDL_MapRGB(white->format, 0, 0, 0));
	white_text = SDL_CreateTextureFromSurface(renderer, white);

	SDL_SetColorKey(help, 0, SDL_MapRGB(help->format, 0, 0, 0));
	help_text = SDL_CreateTextureFromSurface(renderer, help);

	SDL_SetColorKey(lastplayed, 0, SDL_MapRGB(last_played->format, 0, 0, 0));
	lastplayed_text = SDL_CreateTextureFromSurface(renderer, lastplayed);

	SDL_RenderCopy(renderer, board_text, NULL, NULL);

}

SDL_Rect UserInterface::pixel_to_index(int mouse_x, int mouse_y)
{
	SDL_Rect pos; //temporaire trouver une alternative car c'est sale
	int close_x;
	int close_y;
	int closest_x = 2000;
	int closest_y = 2000;

	for (int i = 0; i < 19; i++)
	{
		if (abs(mouse_x - index_x[i]) < abs(closest_x))
		{
			closest_x = mouse_x - index_x[i];
			close_x = i;
		}
		if (abs(mouse_y - index_y[i]) < abs(closest_y))
		{
			closest_y = mouse_y - index_y[i];
			close_y = i;
		}
	}
	pos.x = close_x;
	pos.y = close_y;
	return (pos);
}

void UserInterface::print_board(int tab[361], int lastpiece)
{
	for (int i = 0; i < 361; ++i)
	{
		if (tab[i] == 1)
			place_stone(1, i % 19, i / 19);
		else if (tab[i] == 2)
			place_stone(2, i % 19, i / 19);
	}
	place_stone(4, lastpiece % 19, lastpiece / 19);
}

void UserInterface::place_stone(uint8_t color, int x, int y)
{
	SDL_Rect pos;

	pos.x = index_x[x] - 20;
	pos.y = index_y[y] - 20;
	pos.w = 40;
  	pos.h = 40;

	switch(color) 
	{
		case 1 : SDL_RenderCopy(renderer, black_text, NULL, &pos);
			break;
		case 2 : SDL_RenderCopy(renderer, white_text, NULL, &pos);
			break;
		case 3 : SDL_RenderCopy(renderer, help_text, NULL, &pos);
			break;
		case 4 : SDL_RenderCopy(renderer, lastplayed_text, NULL, &pos);
			break;
		default : break;
	}
}

void UserInterface::clear()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, board_text, NULL, NULL);
}

void UserInterface::render()
{
	SDL_RenderPresent(renderer);
	SDL_RenderCopy(renderer, board_text, NULL, NULL);
}


UserInterface::~UserInterface()
{
	SDL_DestroyTexture(black_text);
	SDL_DestroyTexture(white_text);
	SDL_DestroyTexture(board_text);
	SDL_DestroyTexture(help_text);
	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}