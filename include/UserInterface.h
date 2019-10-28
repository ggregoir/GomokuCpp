#pragma once

#include <SDL.h>
#include <SDL_image.h>

#define BOARD_SIZE		19
#define BOARD_CAPACITY	(BOARD_SIZE * BOARD_SIZE)

class Position
{

public:
	int	x, y;

};

class UserInterface
{

public:
	UserInterface(void);
	~UserInterface(void);

	SDL_Rect		pixel_to_index(Position mouse);
	void			place_stone(uint8_t color, Position stone);
	void			print_board(uint8_t tab[BOARD_CAPACITY], uint32_t lastpiece);
	void			render();
	void			clear();

private:

	SDL_Window*		window;
	SDL_Renderer*	renderer;
	SDL_Texture*	white_text;
	SDL_Texture*	black_text;
	SDL_Texture*	help_text;
	SDL_Texture*	board_text;
	SDL_Texture*	last_played_text;

	const int		board_x[BOARD_SIZE];
	const int		board_y[BOARD_SIZE];

};