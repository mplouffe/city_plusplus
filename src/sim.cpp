#include <SDL.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

// Globals
// (using globals while learning and doing tutorials)
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* gCurrentSurface = NULL;

// Declarations
bool init();									// starts up SDL and creates window
bool loadMedia();								// load media
void close();									// frees media and shuts down SDL
SDL_Surface* loadSurface(std::string path);		// Loads individual image

// Defintions
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
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
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

	// Load default surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("../img/city.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
	{
		printf("Failed to load DEFAULT image.\n");
		success = false;
	}

	// Load Up surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("../img/sky.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
	{
		printf("Failed to load UP image.\n");
		success = false;
	}

		// Load DOWN surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("../img/infrastructure.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
	{
		printf("Failed to load DOWN image.\n");
		success = false;
	}

		// Load LEFT surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("../img/industrial.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
	{
		printf("Failed to load LEFT image.\n");
		success = false;
	}

		// Load RIGHT surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("../img/residental.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
	{
		printf("Failed to load RIGHT image.\n");
		success = false;
	}

	return success;
}

void close()
{
	// Deallocate surface
	for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++)
	{
		SDL_FreeSurface(gKeyPressSurfaces[i]);
		gKeyPressSurfaces[i] = NULL;
	}

	// Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	// Quit SDL subsystems
	SDL_Quit();
}

SDL_Surface* loadSurface(std::string path)
{
	// Load image at the specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}

	return loadedSurface;
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

	// Keep window open until quit
	SDL_Event e;
	bool quit = false;

	gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
	
	while(!quit)
	{ 
		while(SDL_PollEvent(&e))
		{ 
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				switch(e.key.keysym.sym)
				{
					case SDLK_UP:
						gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
						break;
					case SDLK_DOWN:
						gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
						break;
					case SDLK_LEFT:
						gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
						break;
					case SDLK_RIGHT:
						gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
						break;
					case SDLK_HOME:
						gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
						break;
				}
			}
		}

		SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
	
		// Update the surface
		SDL_UpdateWindowSurface(gWindow); 
	}
	
	close();

	return 0;
}
