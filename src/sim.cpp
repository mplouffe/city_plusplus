#include <SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

bool init();		// starts up SDL and creates window
bool loadMedia();	// load media
void close();		// frees media and shuts down SDL

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;

bool init()
{
	// Initialzation flag
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("City++: Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if (gWindow == NULL)
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return success;
}

bool loadMedia()
{
	// Loading success flag
	bool success = true;

	gHelloWorld = SDL_LoadBMP("../img/city.bmp");
	if (gHelloWorld == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "../img/city.bmp", SDL_GetError());
		success = false;
	}
	return success;
}

void close()
{
	// Deallocate surface
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

	// Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	// Quit SDL subsystems
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Initialize SDL
	if(!init())
	{
		printf("Failed to initialize.\n");
		return 0;
	}

	if(!loadMedia())
	{
		printf( "Failed to load media.\n");
		return 0;
	}

	SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
	
	// Update the surface
	SDL_UpdateWindowSurface(gWindow);
	
	// Keep window open until quit
	SDL_Event e;
	bool quit = false;
	
	while(quit == false)
	{ 
		while(SDL_PollEvent(&e))
		{ 
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}
		} 
	}
	
	close();

	return 0;
}
