#include "ui.h"

sdl_ui::sdl_ui(void)
{

	if((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)==-1)) 
	{
		printf("Could not initialize SDL: %s.\n", SDL_GetError());
		exit(-1);
	}

	this->window = SDL_CreateWindow( "Gomoku", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1200, 1200, SDL_WINDOW_SHOWN );
	printf("La window est laaaa\n");
	if( this->window == NULL )
	{
		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		return;
	}
	this->myrenderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface *board = IMG_Load("img/board.png");
    SDL_Surface *black = IMG_Load("img/black2.png");
    SDL_Surface *white = IMG_Load("img/white.png");
    SDL_Surface *help = IMG_Load("img/help.png");
	if (board == 0 || black == 0 || white == 0 || help == 0)
		return;
	SDL_SetColorKey(board, 0, SDL_MapRGB(board->format, 0, 0, 0));
		this->board_text = SDL_CreateTextureFromSurface(this->myrenderer, board);

	SDL_SetColorKey(black, 0, SDL_MapRGB(black->format, 0, 0, 0));
		this->black_text = SDL_CreateTextureFromSurface(this->myrenderer, black);

	SDL_SetColorKey(white, 0, SDL_MapRGB(white->format, 0, 0, 0));
		this->white_text = SDL_CreateTextureFromSurface(this->myrenderer, white);

	SDL_SetColorKey(help, 0, SDL_MapRGB(help->format, 0, 0, 0));
		this->help_text = SDL_CreateTextureFromSurface(this->myrenderer, help);

	SDL_RenderCopy(this->myrenderer, this->board_text, NULL, NULL);
}

void sdl_ui::place_stone(uint8_t color, int x, int y)
{
	SDL_Rect pos;

	pos.x = x - 20;
	pos.y = y - 20;
	pos.w = 40;
  	pos.h = 40;
	switch(color) 
	{
    	case 1 : SDL_RenderCopy(this->myrenderer, this->black_text, NULL, &pos);
             break;
    	case 2 : SDL_RenderCopy(this->myrenderer, this->white_text, NULL, &pos);
             break;
        case 3 : SDL_RenderCopy(this->myrenderer, this->help_text, NULL, &pos);
             break;
		default : break;
	}
}

void sdl_ui::clear()
{
	SDL_RenderClear(this->myrenderer);
	SDL_RenderCopy(this->myrenderer, this->board_text, NULL, NULL);
}

void sdl_ui::render()
{
	SDL_RenderPresent(this->myrenderer);
	SDL_RenderCopy(this->myrenderer, this->board_text, NULL, NULL);
}


sdl_ui::~sdl_ui(void)
{
	SDL_DestroyTexture(this->black_text);
	SDL_DestroyTexture(this->white_text);
	SDL_DestroyTexture(this->board_text);
	SDL_DestroyTexture(this->help_text);
	SDL_DestroyRenderer(this->myrenderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
	return;
}
	// void put_pixel(SDL_Surface *thescreen, int x, int y, Uint32 pixel) 
	// {
	// 	int byteperpixel = thescreen->format->BytesPerPixel;

	// 	Uint8 *p = (Uint8*)thescreen->pixels + y * thescreen->pitch + x * byteperpixel;

	// 	// Adress to pixel
	// 	*(Uint32 *)p = pixel;
	// }

	// void draw_circle(SDL_Surface *screen, int x0, int y0, int radius, Uint32 color)
	// {
	//     int x = radius;
	//     int y = 0;
	//     int xChange = 1 - (radius << 1);
	//     int yChange = 0;
	//     int radiusError = 0;

	//     while (x >= y)
	//     {
	//         for (int i = x0 - x; i <= x0 + x; i++)
	//         {
	//             put_pixel(screen, i, y0 + y, color);
	//             put_pixel(screen, i, y0 - y, color);
	//         }
	//         for (int i = x0 - y; i <= x0 + y; i++)
	//         {
	//             put_pixel(screen, i, y0 + x, color);
	//             put_pixel(screen, i, y0 - x, color);
	//         }

	//         y++;
	//         radiusError += yChange;
	//         yChange += 2;
	//         if (((radiusError << 1) + xChange) > 0)
	//         {
	//             x--;
	//             radiusError += xChange;
	//             xChange += 2;
	//         }
	//     }
	// }

	// void	draw_white_circle(SDL_Surface *screen, int x0, int y0, int radius)
	// {
	// 	draw_circle(screen, x0 , y0 , radius, 0x000000);
	// 	draw_circle(screen, x0 , y0 , radius - 1, 0xFFFFFF);
	// }

	// void 	draw_line(SDL_Surface *screen, int x0, int y0, int x1, int y1, Uint32 pixel) {

	// 	int i;
	//     double x = x1 - x0; 
	// 	double y = y1 - y0; 
	// 	double length = sqrt( x*x + y*y ); 
	// 	double addx = x / length; 
	// 	double addy = y / length; 
	// 	x = x0; 
	// 	y = y0; 
		
	// 	for ( i = 0; i < length; i += 1) { 
	// 		put_pixel(screen, x, y, pixel ); 
	// 		x += addx; 
	// 		y += addy; 
			
	// 	} 
	// }

	// void	draw_grid(SDL_Surface *screen)
	// {
	// 	Uint32 pixel;
	// 	double i = 100;
	// 	int j = 0;

	// 	SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0xFF, 0xEE, 0xCC ) );
	// 	while (j != 19)
	// 	{
	// 		index[j] = i;
	// 		draw_line(screen, 100, i, 1100, i, pixel);
	// 		draw_line(screen, i, 100, i, 1100, pixel);
	// 		i += (double)1000 / (double)18.0001;
	// 		j++;
	// 	}
	// }

// 	void	loop()
// 	{
// 		//The window we'll be rendering to
// 		SDL_Window* window = NULL;
		
// 		//The surface contained by the window
// 		SDL_Surface* screen = NULL;
// 		const int SCREEN_WIDTH = 1200;
// 		const int SCREEN_HEIGHT = 1200;

// 		if((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)==-1)) 
// 		{
// 			printf("Could not initialize SDL: %s.\n", SDL_GetError());
// 			exit(-1);
// 		}
// 		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
// 		if( window == NULL )
// 		{
// 			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
// 		}
// 		else
// 		{
// 			//Get window surface
// 			screen = SDL_GetWindowSurface( window );
// 		}
// 		Uint32 pixel;
// 		printf("Initializing SDL.\n");
// 		/* Initialize defaults, Video and Audio subsystems */
// 		draw_grid(screen);
// 		draw_circle(screen, (1000/18) * 1 + 100 , (1000/18) * 1 + 100 , 1000/50, 0x000000);
// 		draw_white_circle(screen, (1000/18) * 1 + 100 , (1000/18) * 2 + 100 , 1000/50);

// 		bool is_running = true;
// 		SDL_UpdateWindowSurface( window );
// 		SDL_Event event;
// 		int mouse_x;
// 		int mouse_y;
// 		while (is_running) 
// 		{
// 			while (SDL_PollEvent(&event)) 
// 			{
// 				if (event.type == SDL_MOUSEBUTTONDOWN) 
// 				{
// 					SDL_GetMouseState(&mouse_x, &mouse_y);
// 					printf("mouse_x: %i, mouse_y: %i\n", mouse_x, mouse_y);
// 					draw_white_circle(screen, mouse_x , mouse_y , 1000/50);
// 					SDL_UpdateWindowSurface( window );
// 				}
// 				if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym  == SDLK_ESCAPE)) 
// 				{
// 					printf("%u\n", event.key.keysym.sym);
// 					is_running = false;
// 				}
// 			}
// 		}
// 	}
// }