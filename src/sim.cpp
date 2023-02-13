#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <stdio.h>
#include <string>
#include <sstream>
#include <cmath>

#include "Globals.h"
#include "LTexture.h"
#include "Background.h"
#include "Timer.h"

// Declarations
bool init();									// starts up SDL and creates window
void close();									// frees media and shuts down SDL
bool loadMedia();

// Defintions
bool init()
{
	// Initialzation flag
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
	{
		SDL_Log( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			SDL_Log("Warning: Linear texture filtering not enabled!");
		}

		// check for joysticks
		if(SDL_NumJoysticks() < 1)
		{
			SDL_Log("Warning: No joysticks connected!\n");
		}
		else
		{
			// Load joystick
			gGameController = SDL_JoystickOpen(0);
			if(gGameController == NULL)
			{
				SDL_Log("Unable to open game controller! SDL_Error: %s\n", SDL_GetError());
			}
		}

		gWindow = SDL_CreateWindow("City++: Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if (gWindow == NULL)
		{
			SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

			if (gRenderer == NULL)
			{
				SDL_Log("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
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
					SDL_Log("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				// Initalize SDL_mixer
				if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					SDL_Log("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}

				// Initalize SDL_ttf
				if(TTF_Init() == -1)
				{
					SDL_Log("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
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

	// Load plane sprite
	if (!gPlaneTexture.loadFromFile("../assets/img/plane.png", gRenderer))
	{
		SDL_Log("Failed to load PLANE image.\n");
		success = false;
	}

	// Load robot sprite sheet
	if (!gRobotTexture.loadFromFile("../assets/img/robot.png", gRenderer))
	{
		SDL_Log("Failed to load ROBOT image.\n");
		success = false;
	}

	// Load Title Font
	gTitleFont = TTF_OpenFont("../assets/fonts/computer_pixel-7.ttf", 72);
	if (gTitleFont == NULL)
	{
		SDL_Log("Failed to load FONT. SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		// Render text
		SDL_Color textColor = {0xFF, 0xFF, 0xFF, 0xFF};
		SDL_Color shadowColor = {0x00, 0x00, 0x00, 0xFF};
		if (!gTextTexture.loadFromRenderedText("City++: An Urban Simulator", textColor, gRenderer, gTitleFont))
		{
			SDL_Log("Failed to render text texture!\n");
			success = false;
		}

		if (!gTextShadow.loadFromRenderedText("City++: An Urban Simulator", shadowColor, gRenderer, gTitleFont))
		{
			SDL_Log("Failed to render text texture!\n");
			success = false;
		}
	}

	gTimeFont = TTF_OpenFont("../assets/fonts/computer_pixel-7.ttf", 23);
	if (gTimeFont == NULL)
	{
		SDL_Log("Failed to load FONT. SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}

	// Load Audio
	gSelect = Mix_LoadWAV("../assets/audio/Blip_Select.wav");
	if (gSelect == NULL)
	{
		SDL_Log("Failed to load SELECT audio effect. SDL_mixer error: %s\n", Mix_GetError());
		success = false;
	}

	return success;
}

void close()
{
	// close visual
	gBackground.close();

	gPlaneTexture.free();
	gRobotTexture.free();
	gTextTexture.free();
	
	// free audio
	Mix_FreeChunk(gSelect);
	gSelect = NULL;

	// close text
	TTF_CloseFont(gTitleFont);
	gTitleFont = NULL;

	// close game controller
	SDL_JoystickClose(gGameController);
	gGameController = NULL;

	// Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystems
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Initialize SDL
	if(!init())
	{
		SDL_Log("Failed to initialize.\n");
		return 0;
	}

	if(!loadMedia())
	{
		SDL_Log("Failed to load sprites.\n");
		return 0;
	}

	// Keep window open until quit
	SDL_Event e;
	bool quit = false;

	Timer timer;
	std::stringstream timeText;
	SDL_Color textColor = {255, 255, 255, 255};
	
	int planeXPosition = -gPlaneTexture.getWidth();
	int planeYPositionMin = 0;
	int planeYPositionMax = SCREEN_HEIGHT - gPlaneTexture.getHeight();
	int planeYPosition = 50;
	int planePositionUpdaterCounter = 0;

	// normalized direction
	int xDir = 0;
	int yDir = 0;
		
	int textX = 20;
	int textY = 20;

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
			else if (e.type == SDL_JOYAXISMOTION)
			{
				// motion on controller 0
				if (e.jaxis.which == 0)
				{
					// x axis motion
					if (e.jaxis.axis == 0)
					{
						if (e.jaxis.value < -JOYSTICK_DEAD_ZONE)
						{
							xDir = -1;		// left of dead zone
						}
						else if (e.jaxis.value > JOYSTICK_DEAD_ZONE)
						{
							xDir = 1;		// right of dead zone
						}
						else
						{
							xDir = 0;		// neutral
						}
					}
					else if (e.jaxis.axis == 1)
					{
						if (e.jaxis.value < -JOYSTICK_DEAD_ZONE)
						{
							yDir = -1;		// below dead zone
						}
						else if (e.jaxis.value > JOYSTICK_DEAD_ZONE)
						{
							yDir = 1;		// above dead zone
						}
						else
						{
							yDir = 0;		// neutral
						}
					}
				}
			}
			else if (e.type == SDL_KEYDOWN)
			{
				bool playSound = false;
				switch(e.key.keysym.sym)
				{
					case SDLK_UP:
						gBackground.triggerCrossFade(KeyPressSurfaces::KEY_PRESS_SURFACE_UP);
						playSound = true;
						break;
					case SDLK_DOWN:
						gBackground.triggerCrossFade(KeyPressSurfaces::KEY_PRESS_SURFACE_DOWN);
						playSound = true;
						break;
					case SDLK_LEFT:
						gBackground.triggerCrossFade(KeyPressSurfaces::KEY_PRESS_SURFACE_LEFT);
						playSound = true;
						break;
					case SDLK_RIGHT:
						gBackground.triggerCrossFade(KeyPressSurfaces::KEY_PRESS_SURFACE_RIGHT);
						playSound = true;
						break;
					case SDLK_HOME:
						gBackground.triggerCrossFade(KeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT);
						playSound = true;
						break;
					case SDLK_s:
						if (timer.isStarted())
						{
							timer.stop();
						}
						else
						{
							timer.start();
						}
						break;
					case SDLK_p:
						if (timer.isPaused())
						{
							timer.unpause();
						}
						else
						{
							timer.pause();
						}
				}

				if (playSound)
				{
					Mix_PlayChannel(-1, gSelect, 0);
				}
			}
		}

		// update
		gBackground.update();

		// Clear Screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		// Render texture to screen
		gBackground.render();
		gPlaneTexture.render(planeXPosition, planeYPosition);
		gRobotTexture.render(SCREEN_WIDTH - (robotSpriteOffset.w * 2), SCREEN_HEIGHT - (robotSpriteOffset.h * 2), &robotSpriteOffset);
		gTextShadow.render(textX + 4, textY + 4);
		gTextTexture.render(textX, textY);

		planeYPosition += yDir;
		if (planeYPosition < planeYPositionMin)
		{
			planeYPosition = planeYPositionMin;
		}
		else if (planeYPosition > planeYPositionMax)
		{
			planeYPosition = planeYPositionMax;
		}

		planePositionUpdaterCounter++;
		if (planePositionUpdaterCounter > 2)
		{
			planeXPosition += 2;
			planeXPosition += xDir;
			if (planeXPosition > SCREEN_WIDTH)
			{
				planeXPosition = -gPlaneTexture.getWidth();
			}
			planePositionUpdaterCounter = 0;
		}

		robotFrameCounter++;
		if (robotFrameCounter > 20)
		{
			robotFrame++;
			if (robotFrame > 3)
			{
				robotFrame = 0;
			}
			robotSpriteOffset.x = robotFrame * 24;
			robotFrameCounter = 0;
		}

		// timer dispaly
		timeText.str("");
		timeText << "time: " << (timer.getTicks() / 1000.f);

		if (!gTimeTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor, gRenderer, gTimeFont))
		{
			SDL_Log("Unable to render time texture!\n");
		}

		gTimeTextTexture.render(10, SCREEN_HEIGHT - 30);


		// Update Screen
		SDL_RenderPresent(gRenderer);
	}
	
	close();
	return 0;
}
