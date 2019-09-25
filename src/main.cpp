#include <iostream>
#include "SDL2/SDL.h"

using namespace std;

int main(int argc, char **argv)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		cout << "SDL_Init Error: " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}	
	cout << "Welcome to Gomoku" << endl;
	SDL_Quit();
	return 0;
}