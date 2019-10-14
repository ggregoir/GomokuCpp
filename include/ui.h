#pragma once

#include <SDL.h>
#include <SDL_image.h>

class sdl_ui
{

public:
	sdl_ui(void);
	virtual ~sdl_ui(void);

	void place_stone(uint8_t color, int x, int y);
	SDL_Rect pixel_to_index(int mouse_x, int mouse_y);
	void render();
	void print_board(int tab[361]);
	void clear();

private:

	SDL_Window* window;
	SDL_Renderer* myrenderer;
	SDL_Texture* white_text;
	SDL_Texture* black_text;
	SDL_Texture* help_text;
	SDL_Texture* board_text;
	SDL_Texture* lastplayed_text;
};