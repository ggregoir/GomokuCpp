
#include <SDL.h>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 1200;
//Screen dimension constants

void put_pixel(SDL_Surface *theScreen, int x, int y, Uint32 pixel) {
	int byteperpixel = theScreen->format->BytesPerPixel;

	Uint8 *p = (Uint8*)theScreen->pixels + y * theScreen->pitch + x * byteperpixel;

	// Adress to pixel
	*(Uint32 *)p = pixel;
}

void draw_circle(SDL_Surface *Screen, int x0, int y0, int radius, Uint32 color)
{
    int x = radius;
    int y = 0;
    int xChange = 1 - (radius << 1);
    int yChange = 0;
    int radiusError = 0;

    while (x >= y)
    {
        for (int i = x0 - x; i <= x0 + x; i++)
        {
            put_pixel(Screen, i, y0 + y, color);
            put_pixel(Screen, i, y0 - y, color);
        }
        for (int i = x0 - y; i <= x0 + y; i++)
        {
            put_pixel(Screen, i, y0 + x, color);
            put_pixel(Screen, i, y0 - x, color);
        }

        y++;
        radiusError += yChange;
        yChange += 2;
        if (((radiusError << 1) + xChange) > 0)
        {
            x--;
            radiusError += xChange;
            xChange += 2;
        }
    }
}

void	draw_white_circle(SDL_Surface *Screen, int x0, int y0, int radius)
{
	draw_circle(Screen, x0 , y0 , radius, 0x000000);
	draw_circle(Screen, x0 , y0 , radius - 1, 0xFFFFFF);
}

void draw_line(SDL_Surface *Screen, int x0, int y0, int x1, int y1, Uint32 pixel) {

	int i;
    double x = x1 - x0; 
	double y = y1 - y0; 
	double length = sqrt( x*x + y*y ); 
	double addx = x / length; 
	double addy = y / length; 
	x = x0; 
	y = y0; 
	
	for ( i = 0; i < length; i += 1) { 
		put_pixel(Screen, x, y, pixel ); 
		x += addx; 
		y += addy; 
		
	} 
}

int main(int argc, char** argv) 
{
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	
	//The surface contained by the window
	SDL_Surface* screen = NULL;

	Uint32 pixel;
	printf("Initializing SDL.\n");
	/* Initialize defaults, Video and Audio subsystems */
	if((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)==-1)) 
	{
		printf("Could not initialize SDL: %s.\n", SDL_GetError());
		exit(-1);
	}

		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( window == NULL )
	{
		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Get window surface
		screen = SDL_GetWindowSurface( window );
	}

	double i = 100;
	int j = 0;
	SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0xFF, 0xEE, 0xCC ) );
	while (j != 19)
	{
		printf("i: %f\n", i);
		draw_line(screen, 100, i, 1100, i, pixel);
		draw_line(screen, i, 100, i, 1100, pixel);
		i += (double)1000 / (double)18.0001;
		j++;
	}
	draw_circle(screen, (1000/18) * 1 + 100 , (1000/18) * 1 + 100 , 1000/50, 0x000000);
	draw_white_circle(screen, (1000/18) * 1 + 100 , (1000/18) * 2 + 100 , 1000/50);

	bool is_running = true;
	SDL_UpdateWindowSurface( window );
	SDL_Event event;
	int mouse_x;
	int mouse_y;
	while (is_running) 
	{
		while (SDL_PollEvent(&event)) 
		{
			if (event.type == SDL_MOUSEBUTTONDOWN) 
			{
				SDL_GetMouseState(&mouse_x, &mouse_y);
				printf("mouse_x: %i, mouse_y: %i\n", mouse_x, mouse_y);
				draw_white_circle(screen, mouse_x , mouse_y , 1000/50);
				SDL_UpdateWindowSurface( window );
			}
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym  == SDLK_ESCAPE)) 
			{
				printf("%u\n", event.key.keysym.sym);
				is_running = false;
			}
		}
	}



	printf("Quitting SDL.\n");
	/* Shutdown all subsystems */
	SDL_Quit();
	printf("Quitting...\n");

	exit(0);
}
