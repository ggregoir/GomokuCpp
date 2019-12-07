#pragma once

#include "macros.h"
#include "Position.h"

#include <array>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

#define LEFT_CLICK(event) (event.button.type == SDL_MOUSEBUTTONDOWN && \
							event.button.button == SDL_BUTTON_LEFT && \
							event.button.windowID == 1)

#define CLOSE_EVENT(event) ((event.key.keysym.sym == SDLK_ESCAPE && event.type == SDL_KEYDOWN) || event.type == SDL_QUIT)
#define RATIO 0.4

class Parameters;
class Board;

class UserInterface
{

public:

	UserInterface(Parameters params);
	~UserInterface(void);

	Position	pixel_to_pos(Position mouse);
	void		place_stone(uint8_t color, Position stone);
	void		print_board(Board board, uint32_t last_move);
	void		render();
	void		clear();

private:

	SDL_Window*		window;
	SDL_Renderer*	renderer;
	SDL_Texture*	white_text;
	SDL_Texture*	black_text;
	SDL_Texture*	help_text;
	SDL_Texture*	board_text;
	SDL_Texture*	last_played_text;

	std::string		theme[3];

};