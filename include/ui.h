#pragma once

#include <SDL.h>

class sdl_ui
{

public:
	SDLinit(void);
	virtual SDLinit(void);

	void place_stone(uint8_t x, uint8_t y, uint8_t color);

private:
	
	int[19] index;

	SDL_Window* window;
	SDL_Renderer* myrenderer;
	SDL_Texture* white_text;
	SDL_Texture* black_text;
	SDL_Texture* help_text;
	SDL_Texture* board_text;
};