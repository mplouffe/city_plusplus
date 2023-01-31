#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#include "Globals.h"
#include "LTexture.h"

// Declarations
bool init();									// starts up SDL and creates window
bool loadMedia();								// load media
void close();									// frees media and shuts down SDL
SDL_Texture* loadTexture(std::string path);		// Loads individual image as a texture

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
			// Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				// Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				// Initalize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

bool loadMedia()
{
	// Loading success flag
	bool success = true;

	// Load default surface
	gKeyPressTextures[KEY_PRESS_SURFACE_DEFAULT] = loadTexture("../img/city.png");
	if (gKeyPressTextures[KEY_PRESS_SURFACE_DEFAULT] == NULL)
	{
		printf("Failed to load DEFAULT image.\n");
		success = false;
	}

	// Load Up surface
	gKeyPressTextures[KEY_PRESS_SURFACE_UP] = loadTexture("../img/sky.png");
	if (gKeyPressTextures[KEY_PRESS_SURFACE_UP] == NULL)
	{
		printf("Failed to load UP image.\n");
		success = false;
	}

		// Load DOWN surface
	gKeyPressTextures[KEY_PRESS_SURFACE_DOWN] = loadTexture("../img/infrastructure.png");
	if (gKeyPressTextures[KEY_PRESS_SURFACE_DOWN] == NULL)
	{
		printf("Failed to load DOWN image.\n");
		success = false;
	}

		// Load LEFT surface
	gKeyPressTextures[KEY_PRESS_SURFACE_LEFT] = loadTexture("../img/industrial.png");
	if (gKeyPressTextures[KEY_PRESS_SURFACE_LEFT] == NULL)
	{
		printf("Failed to load LEFT image.\n");
		success = false;
	}

		// Load RIGHT surface
	gKeyPressTextures[KEY_PRESS_SURFACE_RIGHT] = loadTexture("../img/residental.png");
	if (gKeyPressTextures[KEY_PRESS_SURFACE_RIGHT] == NULL)
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
		SDL_DestroyTexture(gKeyPressTextures[i]);
		gKeyPressTextures[i] = NULL;
	}

	// Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture(std::string path)
{
	// the final texture
	SDL_Texture* newTexture = NULL;

	// load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unalbe to creat texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		// free loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
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

	gCurrentTexture = gKeyPressTextures[KEY_PRESS_SURFACE_DEFAULT];
	
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
						gCurrentTexture = gKeyPressTextures[KEY_PRESS_SURFACE_UP];
						break;
					case SDLK_DOWN:
						gCurrentTexture = gKeyPressTextures[KEY_PRESS_SURFACE_DOWN];
						break;
					case SDLK_LEFT:
						gCurrentTexture = gKeyPressTextures[KEY_PRESS_SURFACE_LEFT];
						break;
					case SDLK_RIGHT:
						gCurrentTexture = gKeyPressTextures[KEY_PRESS_SURFACE_RIGHT];
						break;
					case SDLK_HOME:
						gCurrentTexture = gKeyPressTextures[KEY_PRESS_SURFACE_DEFAULT];
						break;
				}
			}
		}

		// Clear Screen
		SDL_RenderClear(gRenderer);
		// Render texture to screen
		SDL_RenderCopy(gRenderer, gCurrentTexture, NULL, NULL);
		// Update Screen
		SDL_RenderPresent(gRenderer);
	}
	
	close();

	return 0;
}
