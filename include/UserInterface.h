#pragma once

#include <SDL.h>
#include <SDL_image.h>

struct Position
{
	int	x;
	int	y;
};

class UserInterface
{

public:
	UserInterface(void);
	~UserInterface(void);

	void		place_stone(uint8_t color, int x, int y);
	SDL_Rect	pixel_to_index(int mouse_x, int mouse_y);
	void		render();
	void		print_board(uint8_t tab[361], uint32_t lastpiece);
	void		clear();

private:

	SDL_Window*		window;
	SDL_Renderer*	renderer;
	SDL_Texture*	white_text;
	SDL_Texture*	black_text;
	SDL_Texture*	help_text;
	SDL_Texture*	board_text;
	SDL_Texture*	last_played_text;

	const int		index_x[19];
	const int		index_y[19];

};