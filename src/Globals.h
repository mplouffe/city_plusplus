#ifndef GLOBALS_H
#define GLOBALS_H

#include "LTexture.h"
#include "Background.h"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int JOYSTICK_DEAD_ZONE = 8000;

// Globals
// (using globals while learning and doing tutorials)

// Visual
// - Rendering
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
// - Text
TTF_Font* gTitleFont = NULL;
TTF_Font* gTimeFont = NULL;
LTexture gTextTexture;
LTexture gTextShadow;
LTexture gTimeTextTexture;
// - Sprites
LTexture gPlaneTexture;
LTexture gRobotTexture;
// - Background
Background gBackground;

// Audio
// - Music
// Mix_Music *gMusic;
// - SFX
Mix_Chunk *gSelect;

// Input
SDL_Joystick* gGameController = NULL;


#endif