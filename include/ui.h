#pragma once

#include <SDL.h>
#include <SDL_image.h>

class sdl_ui
{

public:
	sdl_ui(void);
	virtual ~sdl_ui(void);

	void place_stone(uint8_t x, uint8_t y, uint8_t color);
	void render();
	void clear();

private:
	
	int index[19];

	SDL_Window* window;
	SDL_Renderer* myrenderer;
	SDL_Texture* white_text;
	SDL_Texture* black_text;
	SDL_Texture* help_text;
	SDL_Texture* board_text;
};