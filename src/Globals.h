#ifndef GLOBALS_H
#define GLOBALS_H

#include "LTexture.h"
#include "Background.h"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int JOYSTICK_DEAD_ZONE = 8000;

// Globals
// (using globals while learning and doing tutorials)
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Joystick* gGameController = NULL;
TTF_Font* gFont = NULL;
Background gBackground;
LTexture gCurrentTexture;
LTexture gSwappingTexture;
LTexture gPlaneTexture;
LTexture gRobotTexture;
LTexture gTextTexture;
LTexture gTextShadow;


#endif