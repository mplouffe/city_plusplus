#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#include "Globals.h"
#include "LTexture.h"
#include "Background.h"

// Declarations
bool init();									// starts up SDL and creates window
void close();									// frees media and shuts down SDL
bool loadMedia();

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

	success = gBackground.init(gRenderer);
	return success;
}

bool loadMedia()
{
	// Loading success flag
	bool success = true;

	if (!gPlaneTexture.loadFromFile("../img/plane.png", gRenderer))
	{
		printf("Failed to load PLANE image.\n");
		success = false;
	}

	if (!gRobotTexture.loadFromFile("../img/robot.png", gRenderer))
	{
		printf("FAiled to load ROBOT image.\n");
		success = false;
	}

	return success;
}

void close()
{
	gBackground.close();
	// Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystems
	IMG_Quit();
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
		printf("Failed to load sprites.\n");
		return 0;
	}

	// Keep window open until quit
	SDL_Event e;
	bool quit = false;
	int planeXPosition = -gPlaneTexture.getWidth();
	int planePositionUpdaterCounter = 0;

	SDL_Rect robotSpriteOffset = {0, 0, 24, 32};
	int robotFrameCounter = 0;
	int robotFrame = 0;

	gBackground.setBackground(KeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT);
	
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
						gBackground.triggerCrossFade(KeyPressSurfaces::KEY_PRESS_SURFACE_UP);
						break;
					case SDLK_DOWN:
						gBackground.triggerCrossFade(KeyPressSurfaces::KEY_PRESS_SURFACE_DOWN);
						break;
					case SDLK_LEFT:
						gBackground.triggerCrossFade(KeyPressSurfaces::KEY_PRESS_SURFACE_LEFT);
						break;
					case SDLK_RIGHT:
						gBackground.triggerCrossFade(KeyPressSurfaces::KEY_PRESS_SURFACE_RIGHT);
						break;
					case SDLK_HOME:
						gBackground.triggerCrossFade(KeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT);
						break;
				}
			}
		}

		// update
		gBackground.update();

		// Clear Screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		// Render texture to screen
		gBackground.render(gRenderer);
		gPlaneTexture.render(planeXPosition, 50);
		gRobotTexture.render(SCREEN_WIDTH - (robotSpriteOffset.w * 2), SCREEN_HEIGHT - (robotSpriteOffset.h * 2), &robotSpriteOffset);

		planePositionUpdaterCounter++;
		if (planePositionUpdaterCounter > 20)
		{
			planeXPosition++;
			if (planeXPosition > SCREEN_WIDTH)
			{
				planeXPosition = -gPlaneTexture.getWidth();
			}
			planePositionUpdaterCounter = 0;
		}

		robotFrameCounter++;
		if (robotFrameCounter > 1000)
		{
			robotFrame++;
			if (robotFrame > 3)
			{
				robotFrame = 0;
			}
			robotSpriteOffset.x = robotFrame * 24;
			robotFrameCounter = 0;
		}

		// Update Screen
		SDL_RenderPresent(gRenderer);
	}
	
	close();

	return 0;
}
